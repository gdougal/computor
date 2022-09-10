#pragma once
#include <limits>

enum class FACTOR: int
{
	LEFT = 1,
	RIGHT = -1
};


struct sto
{
	const std::string& x;
	template <typename T>
	operator T () { return 0; }
};
template <> sto::operator int() { return std::stoi(x); }
template <> sto::operator double() { return stod(x); }

template<typename T>
T pow_(T num, int p)
{
	// p < 0
	// p < 1?
	while (--p > 0)
		num *= num;
	return p < 0 ? 1 : num;
}

template <typename T>
T mod_(T value)
{
	return value > 0 ? value : -1*value;
}


auto root_table(double a) -> double {
	if ( a >= 1 && a <= 2.5)
		return 1;
	else if ( a <= 6.5)
		return 2;
	else if ( a <= 12.5)
		return 3;
	else if (a <= 20.5)
		return 4;
	else if (a <= 30.5)
		return 5;
	else if (a <= 42.5)
		return 6;
	else if (a <= 56.5)
		return 7;
	else if (a <= 72.5)
		return 8;
	else if (a <= 90.5)
		return 9;
	else return 10;
}

double sqrt_(double value) // вавилонский метод?
{
//	if (a < 0)
//	if (a == 0)
	double a = value;
	auto n = -1;
	while (a >= 100 && ++n)
		a = value / pow_(10.0, 2 * n);
	while (a < 1 && ++n)
		a = value * pow_(10.0, 2 * n);
	auto k = root_table(a);
	double root_next_door = k * pow_(10.0, n);
	double root;
	for (int iter = 20; iter != 0; --iter)
	{
		double k1 = (value - pow_(root_next_door, 2))/(2*root_next_door);
		double k2 = root_next_door + k1;
		root = k2 - (pow_(k1, 2))/(2*k2);
		if (mod_(root - root_next_door) <= std::numeric_limits<double>::epsilon())
			break;
		root_next_door = root;
	}
	return root;
}

double sqrt_(double value, int base)
{
	double a = value;
	auto n = -1;
	while (a >= 100 && ++n)
		a = value / pow_(10.0, base * n);
	while (a < 1 && ++n)
		a = value * pow_(10.0, base * n);
	int k_0 = 0;
	{
		double real_num = pow_(a, base);
		for (; real_num > pow_(k_0 + 1, base);
			   ++k_0);
	}
	double root_next_door = k_0 * pow_(10.0, n);
	double root;
	while (true /*можно ограничить число итераций*/)
	{
		root = 1.0/base *((base - 1)*root_next_door + value/(pow_(root_next_door, base - 1) ) ) ;
		if (mod_(root - root_next_door) <= std::numeric_limits<double>::epsilon())
			break;
		root_next_door = root;
	}
	return root;
}