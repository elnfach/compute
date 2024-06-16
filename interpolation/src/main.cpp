#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <glm/glm.hpp>

struct position
{
	double x;
	double y;
	double z;
};

struct value
{
	double first;
	double second;
	double third;
};

#define print(Y, CORRECT) std::cout << "y1 = " << Y \
	<< " | погрешность составляет " << abs(CORRECT) << std::endl \

static void linear		(const std::vector<position>& points);
static void quadratic	(const std::vector<position>& points);
static void lagrange	(const std::vector<position>& points);
static void newton		();

int main()
{
	setlocale(LC_ALL, "Ru");
	std::cout.setf(std::ios_base::fixed);

	std::vector<position> points = {
	//	  X		Y
		{ 1,	-2 },
		{ 4,	9 },
		{ 9,	3 },
		{ 11,	-7 }
	};

	std::string c;
	int choice;
	bool is_running = true;
	while (is_running)
	{
		std::cout << std::endl;
		std::cout << "Выберите метод решения:" << std::endl << "1. Линейная интерполяция" << std::endl;
		std::cout << "2. Квадратичная интерполяция" << std::endl << "3. Глобальная интерполяция. Многочлен Лагранжа" << std::endl;
		std::cout << "4. Глобальная интерполяция. Многочлен Ньютона" << std::endl << "5. Выход" << std::endl;
		std::cin >> choice;
		std::cout << std::endl;
		switch (choice)
		{
		case 1:
			linear(points);
			break;
		case 2:
			quadratic(points);
			break;
		case 3:
			lagrange(points);
			break;
		case 4:
			newton();
			break;
		case 5:
			is_running = false;
		default:
			std::cout << "Ошибка\n";
			break;
		}
		std::cout << "\nЗавершить? y/n\n";
		std::cin >> c;
		if (c == "y") is_running = false;
	}
}

void linear(const std::vector<position>& points)
{
	value correct = {
		-2, 9, 5.333333333333333f
	};

	double ai;
	double bi;
	ai = (points[1].y - points[0].y) / (points[1].x - points[0].x);
	bi = points[0].y - ai * points[0].x;
	value answer = {
		ai * points[0].x + bi,
		ai * points[1].x + bi,
		ai * 3 + bi
	};
	std::cout << "================" << std::endl;
	print(answer.first, correct.first - answer.first);
	print(answer.second, correct.second - answer.second);
	std::cout << "Произвольная точка x = 3: " << std::endl;
	print(answer.third, correct.third - answer.third);
	std::cout << "================";
}

namespace glm {
	template<typename T, qualifier Q>
	GLM_FUNC_QUALIFIER GLM_CONSTEXPR typename mat<3, 3, T, Q>::col_type operator*(mat<3, 3, T, Q> const& m, position const& v)
	{
		return typename mat<3, 3, T, Q>::col_type(
			m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z,
			m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z,
			m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z
		);
	}
}

void quadratic(const std::vector<position>& points)
{
	glm::mat3 matrix = {
		{ 1, 1, 1, },
		{ 16, 4, 1 },
		{ 81, 9, 1 }
	};

	position b = { -2, 9, 3 };
	glm::vec3 vector = glm::inverse(matrix) * b;

	value correct = {
		-2, 9, 6.5502f
	};

	value answer = {
		vector.x * pow(points[0].x, 2)	+ vector.y * points[0].x	+ vector.z,
		vector.x * pow(points[1].x, 2)	+ vector.y * points[1].x	+ vector.z,
		vector.x * pow(3, 2)			+ vector.y * 3				+ vector.z
	};

	std::cout << "================" << std::endl;
	print(answer.first, correct.first - answer.first);
	print(answer.second, correct.second - answer.second);
	std::cout << "Произвольная точка x = 3: " << std::endl;
	print(answer.third, correct.third - answer.third);
	std::cout << "================";
}

void lagrange(const std::vector<position>& points)
{
	int x;
	std::cout << "Введите точку x в диапозоне [" << static_cast<int>(points[0].x) << ";" << static_cast<int>(points[points.size() - 1].x) << "]" << std::endl;
	std::cin >> x;
	double L = 0;
	for (size_t i = 0; i < points.size(); i++)
	{
		double l = 1;
		for (size_t j = 0; j < points.size(); j++)
		{
			if (i != j)
			{
				l *= (x - points[j].x) / (points[i].x - points[j].x);
			}
		}
		L += points[i].y * l;
	}
	std::cout << "L = " << L << "\n";
}

void newton()
{
	double nas[10]{ 0, -1,1,-3,2,-7,3,-4.2,4,2 };
	double mas[6][6]{ 0 };
	double h = 1, t1, t2, x, s, N1, N2;
	int k = 0;
	char c;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			mas[i][j] = nas[k];
			k++;
		}
		s = mas[i][0] / 2;
	}
	for (int i = 0; i < 4; i++)
		for (int j = 2; j < 3; j++)
			mas[i][j] = mas[i + 1][j - 1] - mas[i][j - 1];
	for (int i = 0; i < 3; i++)
		for (int j = 3; j < 4; j++)
			mas[i][j] = mas[i + 1][j - 1] - mas[i][j - 1];
	for (int i = 0; i < 2; i++)
		for (int j = 4; j < 5; j++)
			mas[i][j] = mas[i + 1][j - 1] - mas[i][j - 1];
	for (int i = 0; i < 1; i++)
		for (int j = 5; j < 6; j++)
			mas[i][j] = mas[i + 1][j - 1] - mas[i][j - 1];
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			std::cout << mas[i][j] << " ";
		}
		std::cout << std::endl;
	}
	while (true)
	{
		std::cout << "Введите точку x " << std::endl;
		std::cin >> x;
		if (x < s)
		{
			t1 = (x - mas[0][0]) / h;
			N1 = mas[0][1] * t1 + mas[0][2] + (t1 * (t1 - 1) / 1 * 2) * mas[0][3] + (t1 * (t1 - 1) * (t1 - 2) / (1 * 2 * 3)) * mas[0][4] + (t1 * (t1 - 1) * (t1 - 2) * (t1 - 3) / (1 * 2 * 3 * 4)) * mas[0][5];
			std::cout << "Приближенное значение = " << N1 << std::endl;
		}
		else
		{
			t2 = (3.2 - mas[4][0]) / h;
			N2 = mas[4][1] * t2 + mas[3][2] + (t2 * (t2 + 1) / 1 * 2) * mas[2][3] + (t2 * (t2 + 1) * (t2 + 2) / (1 * 2 * 3)) * mas[1][4] + (t2 * (t2 + 1) * (t2 + 2) * (t2 + 3) / (1 * 2 * 3 * 4)) * mas[0][5];
			std::cout << "Приближенное значение = " << N2 << std::endl;
		}
		std::cout << "Завершить? y/n" << std::endl;
		std::cin >> c;
		if (c == 'y')
			break;
	}
}