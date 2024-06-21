
#include <iostream>
#include <coroutine>
#include <exception>
#include <iostream>
#include <variant>
#include <stdexcept>
#include <cassert>
#include <vector>
#include <string>

template<typename T>
struct Generator {  // 컴파일러는 'co_yield' 키워드의 존재로 코루틴을 인식합니다.
public:
	struct	promise_type
	{
		auto get_return_object() noexcept
		{
			return Generator{ *this };
		}
		std::suspend_always initial_suspend() const noexcept
		{
			return {};
		}
		std::suspend_always final_suspend() const noexcept
		{
			return {};
		}
		void unhandled_exception()noexcept(std::is_nothrow_copy_constructible_v<std::exception_ptr>)
		{
			result = std::current_exception();
		}
		std::suspend_always yield_value(const T& value) noexcept(std::is_nothrow_copy_constructible_v<T>)
		{
			result = value;
			return{};
		}
		std::suspend_always yield_value(T&& value) noexcept
		{
			result = std::addressof(value);
			return{};
		}
		void return_void() noexcept
		{
			//plugAlive=false;
		}
		bool hasException() //예외가 있는지 확인
		{
			return std::holds_alternative<std::exception_ptr>(result);
		}
		bool isValueInitalized() const noexcept  //데이터 팩토링 값 초기화
		{
			return !std::holds_alternative<std::monostate>(result);  //모노상태가 아닌지 확인하고 비어있지 않음을 시사
		}
		T& getValue()
		{
			return (std::holds_alternative<T>(result) /* && plugAlive*/) ? std::get<T>(result) : *std::get<T*>(result);
		}
		void throwIfException()
		{
			if (hasException())
				std::rethrow_exception(std::get<std::exception_ptr>(result));
		}

	private:
		//bool plugAlive = true;
		std::variant<std::monostate, T, T*, std::exception_ptr> result;
	};

	struct LazyIterator
	{
		using iterator_catgory = std::input_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = T;
		using reference = T&;
		using pointer = T*;

		LazyIterator() noexcept = default;
		explicit LazyIterator(const std::coroutine_handle<promise_type>& coro) noexcept :coro(&coro) {} //핵심루틴을 위한 반복자
		friend bool operator==(const LazyIterator&, const LazyIterator&) noexcept = default;
		friend bool operator!= (const LazyIterator&, const LazyIterator&) noexcept = default;//c++20 이후로는 안해도됨
		LazyIterator& operator++() noexcept
		{
			assert(coro != nullptr);
			assert(!coro->done());
			coro->resume();
			if (coro->done() && !coro->promise().hasException())
			{
				coro = nullptr;
			}
			return *this;
		}
		auto& operator*() const
		{
			assert(coro != nullptr);
			coro->promise().throwIfException();
			return coro->promise().getValue();
		}
		friend bool hasException(const LazyIterator& i) noexcept
		{
			return i.coro && i.coro->promise().hasException();
		}

	private:
		const std::coroutine_handle<promise_type>* coro = nullptr;
	};

	using handle_type = std::coroutine_handle<promise_type>;

	Generator(handle_type&& other) noexcept : coro(std::exchange(other.coro, nullptr)) {};
	Generator& operator=(Generator&& other) noexcept
	{
		if (coro)
			coro.destroy();
		coro = std::exchange(other.coro, nullptr);
	}
	~Generator()
	{
		if (coro)
			coro.destroy();
	}

	bool Advence()const noexcept
	{
		coro();
		return !coro.done() || coro.promise().hasException();
	}

	T& GetValue() const
	{
		coro.promise().throwIfException();
		return coro.promise().getValue();
	}

	bool hasException() const noexcept
	{
		return coro.promise().hasException();
	}

	T operator()()const
	{
		coro(); //coro.resume() 이랑 같음
		coro.promise().throwIfException();
		return coro.promise().getValue();
	}

	LazyIterator begin() const
	{
		if (coro.done())
			return end();

		auto i = LazyIterator(coro);
		if (!coro.promise().isValueInitalized())
			++i; //*this == end()
		return i;
	}
	LazyIterator end() const noexcept
	{
		return{};
	}

private:
	explicit Generator(promise_type& promise) noexcept : coro(std::coroutine_handle<promise_type>::from_promise(promise)) {};
	handle_type coro;
};

Generator<std::string> foo(std::string greeting)
{
	co_yield greeting;
	const auto s = std::string{ "world" };
	co_yield s;
}

int main()
{
	Generator<std::string> const f = foo("hello");

	//for (auto& i : f)
	//{
	//	std::cout << i << "\n";
	//}

	for (auto it = f.begin(); it != f.end(); ++it)
	{
		std::cout << (*it) << "\n";
	}

	//auto i = f.begin();
	//while (i != f.end())
	//{
	//	std::cout<<(*i)<<"\n";
	//	++i;
	//}
}
