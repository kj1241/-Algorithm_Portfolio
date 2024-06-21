#include <iostream>
#include <coroutine>
#include <exception>
#include <iostream>
#include <variant>
#include <stdexcept>

template<typename T>
struct Generator {  // 컴파일러는 'co_yield' 키워드의 존재로 코루틴을 인식합니다.
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
		void return_void() const noexcept
		{
		}
		bool hasException()
		{
			return std::holds_alternative<std::exception_ptr>(result);
		}
		T& getValue()
		{
			if (hasException())
				std::rethrow_exception(std::get<std::exception_ptr>(result));

			return std::holds_alternative<T>(result) ? std::get<T>(result) : *std::get<T*>(result);
		}
	private:
		std::variant<std::monostate, T, T*, std::exception_ptr> result;
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
		return coro.promise().getValue();
	}
	bool hasException() const noexcept
	{
		return coro.promise().hasException();
	}
	T operator()()const
	{
		coro(); //coro.resume() 이랑 같음
		return coro.promise().getValue();
	}

private:
	explicit Generator(promise_type& promise) noexcept : coro(std::coroutine_handle<promise_type>::from_promise(promise)) {};
	handle_type coro;
};

Generator<std::string> foo(/*std::string greeting*/)
{
	co_yield "hello";

	const auto s = std::string{ "world" };
	co_yield s;
}

int main()
{
	auto const f = foo();
	/*std::cout << f() << " ";
	std::cout << f() << "\n";
	std::cout << f();*/
	try {
		while (f.Advence())
		{
			if (f.hasException())
			{

			}
			std::cout << f.GetValue() << "\n";
		}
	}
	catch (const std::exception e)
	{
		std::cout << "exception: " << e.what() << "\n";
	}
}