#include <iostream>
#include <thread>
#include <optional>
#include <Windows.h>


template<typename T> class concurrent_stack
{
	struct Node
	{
		T t;
		std::shared_ptr<Node> next;
	};
	std::atomic<std::shared_ptr<Node>> head;

	concurrent_stack(concurrent_stack&) = delete;
	void operator=(concurrent_stack&) = delete;

public:
	concurrent_stack() = default;
	~concurrent_stack()
	{
		if (head.load()!=nullptr)
			while (head.load()!=nullptr)
				pop_front();
	}
	class reference {
		std::shared_ptr<Node> p;
	public:
		reference(std::shared_ptr<Node> p_) : p{ p_ } { }
		T& operator* ()
		{
			return p->t;
		}
		T* operator->()
		{
			return &p->t;
		}
	};

	auto find(T t) const {
		auto p = head.load();  // in C++11: atomic_load(&head)
		while (p && p->t != t)
			p = p->next;
		return reference(move(p));
	}
	auto front() const {
		return reference(head); // in C++11: atomic_load(&head)
	}
	void push_front(T t) noexcept
	{
		//auto p = std::make_shared<Node>();
		//p->t = t;
		//p->next = head;         // in C++11: atomic_load(&head)
		auto p = std::make_shared<Node>(std::move(t), head.load());
		while (!head.compare_exchange_weak(p->next, p)) {}
		// in C++11: atomic_compare_exchange_weak(&head, &p->next, p);     

	}
	T pop_front() noexcept
	{
		std::shared_ptr<Node> p = head.load();

		//빼는거임
		while (p && !head.compare_exchange_weak(p, p->next)){}
		if (p != nullptr)
			return p->t;
		else
			return{};
		// in C++11: atomic_compare_exchange_weak(&head, &p, p->next);
	}

	void print_all() noexcept
	{
		std::shared_ptr<Node> p = head.load();
		while (p != nullptr)
		{
			std::cout << p->t << "\n";
			p = p->next;
		}
	}
	int stack_size() noexcept
	{
		int size = 0;
		std::shared_ptr<Node> p = head.load();
		while (p != nullptr)
		{
			size++;
			p = p->next;
		}
		return size;
	}
};


concurrent_stack<int> stack;
int count = 100000;

//std::atomic<std::shared_ptr<int>> ptr
//{
//    std::make_shared<int>(0)
//};

int main()
{
	unsigned int maxThread
	{ 
	    std::thread::hardware_concurrency() 
	};

	std::cout << "코어 개수: " << maxThread << std::endl;

	for (int i = 0; i < maxThread; ++i)
	{
		std::thread([i](int max) {
			for (int j = 0; j < count; ++j) {
				//ptr[(j * 5) + (i + 1)] = std::make_shared<int>((j * 5) + (i + 1));
				stack.push_front((j * max) + (i + 1));
			}
			}, maxThread).join();
	}

	std::cout << "스택 총 사이즈(시작) : " << stack.stack_size() << "\n";
	Sleep(5000);
	std::thread([] { stack.print_all(); }).join();

	for (int i = 0; i < 4; ++i)
	{
		std::thread([i] {
			for (int j = 0; j < count * 2; ++j)
			{
				stack.pop_front();
			}
		}).join();
	}
	std::cout << "스택 총 사이즈(끝) : " << stack.stack_size() << "\n";
}