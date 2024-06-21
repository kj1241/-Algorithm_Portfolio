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

class Shape
{
public:
	Shape() = default;
	virtual ~Shape() = default;

	virtual void Draw() const = 0;
private:

};
class Circle : public Shape
{
public:
	explicit Circle(double rad) : radius(rad)
	{
	}
	double GetRadius() const noexcept
	{
		return radius;
	}
	void Draw() const override
	{
		std::cout << radius << "\n";
	}

private:
	double radius;
};

//void Translate(Circle&, Vector2 const&);
//void Rotate(Circle&, double const&);



class Square : public Shape
{
public:
	explicit Square(double side) :side(side)
	{
	}
	double GetSide() const noexcept
	{
		return side;
	}
	void Draw() const override
	{
		std::cout << side << "\n";
	}

private:
	double side;
};

//void Translate(Circle&, Vector2 const&);
//void Rotate(Square&, double const&);


class _Ellipse : public Shape
{
public:
	explicit _Ellipse(double r1, double r2) :radius(r1, r2)
	{
	}
	Vector2 GetRadius() const noexcept
	{
		return radius;
	}
	void Draw() const override
	{
		std::cout << radius.x << " " << radius.y << "\n";
	}


private:
	Vector2 radius;
};

//void Translate(Circle&, Vector2 const&);
//void Rotate(_Ellipse&, double const&);

class _Rectangle : public Shape
{
public:
	explicit _Rectangle(double s1, double s2) : side(s1, s2)
	{
	}
	Vector2 GetSide() const noexcept
	{
		return side;
	}
	void Draw() const override
	{
		std::cout << side.x << " " << side.y << "\n";
	}

private:
	Vector2 side;
};

//void Translate(Circle&, Vector2 const&);
//void Rotate(_Rectangle&, double const&);



void DrawAllShapes(std::vector<std::unique_ptr<Shape>>const& shapes)
{
	for (auto const& s : shapes)
	{
		s->Draw();
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
	std::cout << "���� ���� �ð�: " << end - start << "\n";
	std::cout << "���� �޸� ��뷮: " << pmc.PrivateUsage << "\n";
	std::cout << "���� �޸� ��뷮: " << pmc.WorkingSetSize << "\n";
}