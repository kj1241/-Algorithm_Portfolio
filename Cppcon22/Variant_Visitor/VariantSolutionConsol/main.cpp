
#include <iostream>
#include <vector>
#include <memory>
#include <variant> 
#include <ctime>
#include <windows.h>
#include <psapi.h>


struct Vector2
{
	double x;
	double y;
	Vector2(double x, double y) :x(x), y(y) {};
};

class Circle
{
public:
	explicit Circle(double rad) : radius(rad)
	{
	}
	double GetRadius() const noexcept
	{
		return radius;
	}
private:
	double radius;
};

//void Translate(Circle&, Vector2 const&);
//void Rotate(Circle&, double const&);



class Square
{
public:
	explicit Square(double side) :side(side)
	{
	}
	double GetSide() const noexcept
	{
		return side;
	}

private:
	double side;
};

//void Translate(Circle&, Vector2 const&);
//void Rotate(Square&, double const&);


class _Ellipse
{
public:
	explicit _Ellipse(double r1, double r2) :radius(r1, r2)
	{
	}
	Vector2 GetRadius() const noexcept
	{
		return radius;
	}

private:
	Vector2 radius;
};

//void Translate(Circle&, Vector2 const&);
//void Rotate(_Ellipse&, double const&);

class _Rectangle
{
public:
	explicit _Rectangle(double s1, double s2) : side(s1, s2)
	{
	}
	Vector2 GetSide() const noexcept
	{
		return side;
	}

private:
	Vector2 side;
};

//void Translate(Circle&, Vector2 const&);
//void Rotate(_Rectangle&, double const&);


class Draw
{
public:
	void operator()(Circle const& c) const
	{
		std::cout << c.GetRadius() << "\n";
	}
	void operator()(Square const& s) const
	{
		std::cout << s.GetSide() << "\n";
	}
	void operator()(_Ellipse const& c) const
	{
		std::cout << c.GetRadius().x << c.GetRadius().y << "\n";
	}
	void operator()(_Rectangle const& s) const
	{
		std::cout << s.GetSide().x << s.GetSide().y << "\n";
	}
};

using Shape = std::variant<Circle, Square, _Ellipse, _Rectangle>;


void DrawAllShapes(std::vector<Shape>const& shapes)
{
	for (auto const& s : shapes)
	{
		std::visit(Draw{}, s);
	}
}

int main()
{
	PROCESS_MEMORY_COUNTERS_EX pmc;
	memset(&pmc, 0, sizeof(PROCESS_MEMORY_COUNTERS_EX));
	pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS_EX);

	clock_t start, end;
	double duration;

	using Shapes = std::vector<Shape>;

	Shapes shapes;
	for (int i = 0; i < 10000; ++i)
	{
		switch (rand() % 4)
		{
		case 0:
			shapes.emplace_back(Circle(rand()));
			break;
		case 1:
			shapes.emplace_back(Square(rand()));
			break;
		case 2:
			shapes.emplace_back(_Ellipse(rand(), rand()));
			break;
		case 3:
			shapes.emplace_back(_Rectangle(rand(), rand()));
			break;
		}
	}

	start = std::clock();
	{
		DrawAllShapes(shapes);
	}
	end = std::clock();
	GetProcessMemoryInfo(GetCurrentProcess(), reinterpret_cast<PROCESS_MEMORY_COUNTERS*>(&pmc), sizeof(pmc));

	std::cout << "\n";
	std::cout << "로직 실행 시간: " << end - start << "\n";
	std::cout << "가상 메모리 사용량: " << pmc.PrivateUsage << "\n";
	std::cout << "물리 메모리 사용량: " << pmc.WorkingSetSize << "\n";
}
