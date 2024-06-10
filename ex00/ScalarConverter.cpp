#include "ScalarConverter.hpp"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits.h>
#include <limits>

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& src) {
	(void)src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

ScalarConverter::~ScalarConverter() {}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

ScalarConverter&
ScalarConverter::operator=(ScalarConverter const& rhs) {
	if (this != &rhs) {
	}
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

static bool is_pseudo_double(std::string const& literal) {
	return literal == "nan" || literal == "-inf"
		|| literal == "+inf";
}
static bool is_pseudo_float(std::string const& literal) {
	return literal == "nanf" || literal == "-inff"
		|| literal == "+inff";
}

// @follow-up make sure no bugs present
static bool contains_chars(std::string const& literal) {
	if (is_pseudo_double(literal) || is_pseudo_float(literal)) {
		return false;
	}
	for (size_t i = 0; i < literal.length(); i++) {
		if (!std::isdigit(literal[i]) && literal[i] != '.'
			&& literal[i] != '-' && literal[i] != 'f') {
			return true;
		}
	}
	return false;
}

static void print_table(long int_val, float float_val,
						double double_val,
						bool   is_pseudo = false) {
	if (is_pseudo) {
		std::cout << " pseudo literal\n";
		std::cout << "char: impossible\nint: impossible\n";
	} else {
		if (int_val >= std::numeric_limits<char>::min()
			&& int_val <= std::numeric_limits<char>::max()) {
			std::cout << "char: '" << static_cast<char>(int_val)
					  << "'\n";
		} else {
			std::cout << "char: Non displayable\n";
		}
		if (int_val <= INT_MAX && int_val >= INT_MIN) {
			std::cout << "int: " << static_cast<int>(int_val)
					  << "\n";
		} else {
			std::cout << "int: impossible\n";
		}
	}
	std::cout << "float:  " << std::fixed << std::setprecision(1)
			  << float_val << "f\n";
	std::cout << "double: " << std::fixed << std::setprecision(1)
			  << double_val << "\n";
}

// @audit type conversion must be solved using one specific type of casting.
static void from_char(std::string const& literal) {
	const char input = static_cast<char>(literal[0]);

	print_table(static_cast<int>(input),
				static_cast<float>(input),
				static_cast<double>(input));
}

static void from_int(std::string const& literal) {
	const long wrap_input
		= static_cast<long>(std::atol(literal.c_str()));

	print_table(wrap_input, static_cast<float>(wrap_input),
				static_cast<double>(wrap_input));
}

static void from_float(std::string const& literal) {
	const float input
		= static_cast<float>(std::atof(literal.c_str()));

	print_table(
		static_cast<long>(input), static_cast<float>(input),
		static_cast<double>(input), is_pseudo_float(literal));
}

static void from_double(std::string const& literal) {
	const double input = static_cast<double>(
		std::strtod(literal.c_str(), NULL));

	print_table(static_cast<long>(input),
				static_cast<float>(input), input,
				is_pseudo_double(literal));
}

typedef void (*FuncPtr)(std::string const&);

void from_invalid(std::string const& literal) {
	std::cerr << "Invalid input: " << literal << " !\n";
}

// void from_invalid_early(std::string const& literal) {
// 	std::cerr << "early input: " << literal << " !\n";
// }

// @follow-up needs additional checks
static FuncPtr from_type(std::string const& literal) {
	const size_t idx_dot = literal.find(".", 1);
	const size_t idx_f   = literal.find("f");
	if ((idx_dot != std::string::npos
		 && static_cast<std::string>(&literal.at(idx_dot))
					.find(".", 1)
				!= std::string::npos)
		|| (idx_f != std::string::npos
			&& idx_f != literal.length() - 1
			&& static_cast<std::string>(&literal.at(idx_f))
					   .find("f")
				   != std::string::npos
			&& literal != "+inff" && literal != "-inff")) {
		return (&from_invalid);
	}
	if (is_pseudo_float(literal)
		|| (idx_dot != std::string::npos
			&& literal.end()[-1] == 'f'
			&& std::isdigit(literal.end()[-2]))) {
		return (&from_float);
	}
	if (is_pseudo_double(literal)
		|| (idx_dot != std::string::npos
			&& std::isdigit(literal.end()[-1])
			&& std::isdigit(literal.end()[-1]))) {
		return (&from_double);
	}
	if (idx_dot == std::string::npos) {
		if (literal.length() == 1 && std::iswalpha(literal[0])) {
			return (&from_char);
		}
		if (literal.find_first_of(".f") == std::string::npos) {
			return (&from_int);
		}
	}
	return (&from_invalid);
}

void ScalarConverter::convert(std::string const& literal) {
	if ((literal.length() == 1
		 || (literal.length() > 1 && !contains_chars(literal)))
		&& from_type(literal) != &from_invalid) {
		from_type(literal)(literal);
	} else {
		std::cerr << "Error: invalid literal\n";
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */