
#include <iostream>
#include <vector>
#include <memory>
#include <variant> 
#include <ctime>
#include <windows.h>
#include <psapi.h>

enum ShapeType
{
	circle,
	square,
	ellipse,
	rectangle
};
struct Vector2
{
	double x;
	double y;
	Vector2(double x, double y) :x(x), y(y) {};
};

class Shape
{
public:
	explicit Shape(ShapeType t) :type(t)
	{
	}
	virtual ~Shape() = default;
	ShapeType GetType() const noexcept
	{
		return type;
	}
private:
	ShapeType type;
};
class Circle : public Shape
{
public:
	explicit Circle(double rad) :Shape(circle), radius(rad)
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
void Rotate(Circle&, double const&);
void Draw(Circle const& c)
{
	std::cout << c.GetRadius() << "\n";
}


class Square : public Shape
{
public:
	explicit Square(double side) :Shape(square), side(side)
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
void Rotate(Square&, double const&);
void Draw(Square const& s)
{
	std::cout << s.GetSide() << "\n";
}

class _Ellipse : public Shape
{
public:
	explicit _Ellipse(double r1, double r2) :Shape(ellipse), radius(r1, r2)
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
void Rotate(_Ellipse&, double const&);
void Draw(_Ellipse const& c)
{
	std::cout << c.GetRadius().x << " " << c.GetRadius().y << "\n";
}

class _Rectangle : public Shape
{
public:
	explicit _Rectangle(double s1, double s2) :Shape(rectangle), side(s1, s2)
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
void Rotate(_Rectangle&, double const&);
void Draw(_Rectangle const& s)
{
	std::cout << s.GetSide().x << " " << s.GetSide().y << "\n";
}


void DrawAllShapes(std::vector<std::unique_ptr<Shape>>const& shapes)
{
	for (auto const& s : shapes)
	{
		switch ((s->GetType()))
		{
		case circle:
			Draw(*static_cast<Circle const*>(s.get()));
			break;
		case square:
			Draw(*static_cast<Square const*>(s.get()));
			break;
		case ellipse:
			Draw(*static_cast<_Ellipse const*>(s.get()));
			break;
		case rectangle:
			Draw(*static_cast<_Rectangle const*>(s.get()));
			break;
		}
	}
}

int main()
{
	PROCESS_MEMORY_COUNTERS_EX pmc;
	memset(&pmc, 0, sizeof(PROCESS_MEMORY_COUNTERS_EX));
	pmc.cb = sizeof(PROCESS_MEMORY_COUNTERS_EX);

	clock_t start, end;
	double duration;

	using Shapes = std::vector<std::unique_ptr<Shape>>;

	Shapes shapes;
	for (int i = 0; i < 10000; ++i)
	{
		switch (rand() % 4)
		{
		case 0:
			shapes.emplace_back(std::make_unique<Circle>(rand()));
			break;
		case 1:
			shapes.emplace_back(std::make_unique<Square>(rand()));
			break;
		case 2:
			shapes.emplace_back(std::make_unique<_Ellipse>(rand(), rand()));
			break;
		case 3:
			shapes.emplace_back(std::make_unique<_Rectangle>(rand(), rand()));
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