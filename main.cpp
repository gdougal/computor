#include <regex>
#include <map>
#include "types.hpp"
#include "complex.hpp"

template<typename T>
std::map<int, double> parse( std::string&& input, std::regex&& format, T preformat_)
{
	preformat_(input);
	std::sregex_iterator sliced{ input.begin(), input.end(), format };
	FACTOR factor = FACTOR::LEFT;
	// key - degree
	// value - coefficent
	std::map<int, double> parted;
	for (std::sregex_iterator i = sliced; i != std::sregex_iterator(); ++i)
	{
		try
		{
			auto part = *i;
			if ( i->str() != "=" )
			{
				int degree = sto({part[4].str()});
				double coeff = sto({part[3].str()});
				auto find_res = parted.find(degree);
				if (find_res == parted.end())
					parted[degree] = coeff * static_cast<int>(factor);
				else
					parted[degree] += coeff * static_cast<int>(factor);
			}
			else
				factor = FACTOR::RIGHT;
		}
		catch (...)
		{
			std::cerr << "ooops!" << std::endl;
			continue;
		}
	}
	return parted;
}

int main(const int argv, const char** args)
{
	std::stringstream stream;
	if (argv != 2)
		return 1;
	stream << args[1] << std::endl;
	auto parsed = parse( &(args[1][0]),  std::regex(R"((=)|(([0-9+\-\.,\*]+)X\^(\d+)))"),
	[](std::string& inp)->void
	{
		inp.erase(
		std::remove_if( inp.begin(), inp.end(), [](char c) { return std::isspace(c); } ),
		inp.end() );
	} );
	for (auto l:parsed)
	{
		stream << l.second << "*X^" << l.first << " ";
	}
	auto p_degree = (--parsed.end())->first;
	stream << " = 0" << std::endl << "Polynomial degree: " << p_degree << std::endl;

	std::pair<std::optional<complex_number<double>>, std::optional<complex_number<double>>> roots;
	if (p_degree == 0)
		stream << "Бабушку свою так обманывай хитрец!" << std::endl;
	else if (p_degree == 1)
	{
		stream << "The solutions is:" << std::endl;
		roots = {{(parsed[0] * -1)/parsed[1]}, {}};
	}
	else if (p_degree == 2)
	{
		double D = (parsed[1] * parsed[1]) - (4*parsed[0]*parsed[2]);
		stream << "Discriminant is : " << D << std::endl;
		if (D < 0)
		{
			stream << "Discriminant is strictly negative, the two complex solutions are:" << std::endl;
			roots = {{((parsed[1] * -1) - complex_number(0., sqrt_(mod_(D), 2))) / (2 * parsed[2])},
					 {(parsed[1] * -1 + complex_number(0., sqrt_(mod_(D), 2))) / (2 * parsed[2])}};
		} else if (mod_(D) - mod_(D) < std::numeric_limits<double>::epsilon())
		{
			stream << "Discriminant is strictly positive, the two solutions are:" << std::endl;
			roots = {{(parsed[1] * -1 - sqrt_(D, 2)) / (2 * parsed[2])},
					 {(parsed[1] * -1 + sqrt_(D, 2)) / (2 * parsed[2])}};
		} else
		{
			stream << "Discriminant is equal zero, the solutions is:" << std::endl;
			roots = {{(parsed[1] * -1) / (2 * parsed[2])},
					 {}};
		}
	}
	else
		stream <<  "The polynomial degree is strictly greater than 2, I can't solve." << std::endl;
	if (roots.first)
		stream << roots.first.value() << std::endl;
	if ( roots.second )
		stream << roots.second.value() << std::endl;
	std::cout << stream.str();
	return 0;
}