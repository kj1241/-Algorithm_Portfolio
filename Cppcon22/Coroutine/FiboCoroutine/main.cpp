#include <iostream>
#include <coroutine>
#include <exception>
#include <iostream>
#include <variant>
#include <stdexcept>
#include <cassert>
#include <vector>
#include <string>
#include <windows.h>
#include <psapi.h>
#include <conio.h>
#include <ctime>

template<typename T>
struct Generator {  // �����Ϸ��� 'co_yield' Ű������ ����� �ڷ�ƾ�� �ν��մϴ�.
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
		bool hasException() //���ܰ� �ִ��� Ȯ��
		{
			return std::holds_alternative<std::exception_ptr>(result);
		}
		bool isValueInitalized() const noexcept  //������ ���丵 �� �ʱ�ȭ
		{
			return !std::holds_alternative<std::monostate>(result);  //�����°� �ƴ��� Ȯ���ϰ� ������� ������ �û�
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
		explicit LazyIterator(const std::coroutine_handle<promise_type>& coro) noexcept :coro(&coro) {} //�ٽɷ�ƾ�� ���� �ݺ���
		friend bool operator==(const LazyIterator&, const LazyIterator&) noexcept = default;
		friend bool operator!= (const LazyIterator&, const LazyIterator&) noexcept = default;//c++20 ���ķδ� ���ص���
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
		coro(); //coro.resume() �̶� ����
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


unsigned long long int Fibonacci(int num)
{
	long long int answer = 0;
	bool flag = false;
	long long int a = 0, b = 1;

	if (num < 1)
		return 0;
	if (num == 1)
		return 1;

	for (int i = 0; i < num - 1; ++i)
	{
		if (!flag)
		{
			(a += b) %= 18446744073709551615;
			flag = true;
		}
		else
		{
			(b += a) %= 18446744073709551615;
			flag = false;
		}
	}
	return (a > b) ? answer = a : answer = b;
}

int main()
{
	PROCESS_MEMORY_COUNTERS_EX pmc;
	memset(&pmc, 0, sizeof(PROCESS_MEMORY_COUNTERS_EX));
	pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS_EX);

	clock_t start, end;
	double duration;

	start = std::clock();
	{
		for (int i = 0; i < 100001; ++i)
			std::cout << "�Ǻ���ġ ����" << i << " ���: " << Fibonacci(i) << "\n";
	}
	end = std::clock();
	GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc), sizeof(pmc));

	std::cout << "���� ���� ���� �ð�: " << end - start << "\n";
	std::cout << "���� ���� �޸�: " << pmc.PrivateUsage << "\n";
	std::cout << "���� ���� �޸�: " << pmc.WorkingSetSize << "\n";
}