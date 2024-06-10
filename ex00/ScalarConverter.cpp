#include "ScalarConverter.hpp"
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits.h>

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

// @audit type conversion must be solved using one specific type of casting.
static void from_char(std::string const& literal) {
	const char input = static_cast<char>(literal[0]);

	if (std::isprint(input)) {
		std::cout << "char: '" << input << "' (source)\n";
	} else {
		std::cout << "char: Non displayable\n";
	}

	std::cout << "int: " << static_cast<int>(input) << "\n";
	std::cout << "float: " << static_cast<float>(input)
			  << ".0f\n";
	std::cout << "double: " << static_cast<double>(input)
			  << ".0\n";
}

static void from_int(std::string const& literal) {
	const long wrap_input
		= static_cast<long>(std::atol(literal.c_str()));

	if (wrap_input < INT_MAX && wrap_input > INT_MIN) {
		const int input = static_cast<int>(wrap_input);
		if (std::isprint(input)) {
			std::cout << "char: '" << static_cast<char>(input)
					  << "'\n";
		} else {
			std::cout << "char: Non displayable\n";
		}
		std::cout << "int: " << input << " (source)\n";
		std::cout << "float: " << std::fixed
				  << std::setprecision(1)
				  << static_cast<float>(input) << ".0f\n";
		std::cout << "double: " << std::fixed
				  << std::setprecision(1)
				  << static_cast<double>(input) << ".0\n";
	} else {
		std::cout << "char: impossible\n";
		std::cout << "int: impossible\n";
		std::cout << "float: " << std::fixed
				  << std::setprecision(1)
				  << static_cast<float>(wrap_input) << "f\n";
		std::cout << "double: " << std::fixed
				  << std::setprecision(1)
				  << static_cast<double>(wrap_input) << "\n";
	}
}

static void from_float(std::string const& literal) {
	const float input
		= static_cast<float>(std::atof(literal.c_str()));

	if (is_pseudo_float(literal)) {
		std::cout << "char: impossible\n";
		std::cout << "int: impossible\n";
		std::cout << "float: " << std::fixed
				  << std::setprecision(1) << input
				  << "f (source)\n";
		std::cout << "double: " << static_cast<double>(input)
				  << "\n";
	} else {
		const int scalar_int
			= static_cast<int>(std::atoi(literal.c_str()));
		const char scalar_char = static_cast<char>(input);
		if (std::isprint(scalar_char) != 0) {
			std::cout << "char: '" << scalar_char << "'\n";
		} else {
			std::cout << "char: Non displayable\n";
		}

		std::cout << "int: " << scalar_int << std::endl;
		if (static_cast<float>(scalar_int) == input) {
			std::cout << "float: " << std::fixed
					  << std::setprecision(1) << input
					  << ".0f (source)\n";
			std::cout << "double: " << static_cast<double>(input)
					  << ".0\n";
		} else {
			std::cout << "float: " << std::fixed
					  << std::setprecision(1) << input
					  << "f (source)\n";
			std::cout << "double: " << static_cast<double>(input)
					  << "\n";
		}
	}
}

static void from_double(std::string const& literal) {
	const double input
		= static_cast<double>(std::atof(literal.c_str()));

	if (is_pseudo_double(literal)) {
		std::cout << "char: impossible\n";
		std::cout << "int: impossible\n";
		std::cout << "float: " << std::fixed
				  << std::setprecision(1)
				  << static_cast<float>(input) << "f \n";
		std::cout << "double: " << std::fixed
				  << std::setprecision(1) << input
				  << " (source)\n";
	} else {
		const int scalar_int
			= static_cast<int>(std::atoi(literal.c_str()));
		const char scalar_char = static_cast<char>(input);
		if (std::isprint(scalar_char)) {
			std::cout << "char: '" << scalar_char << " '\n";
		} else {
			std::cout << "char: Non displayable\n";
		}

		std::cout << "int: " << scalar_int << "\n";
		if (static_cast<double>(scalar_int) == input) {
			std::cout << "float: " << std::fixed
					  << std::setprecision(1)
					  << static_cast<float>(input) << ".0f\n";
			std::cout << "double: " << std::fixed
					  << std::setprecision(1) << input
					  << ".0 (source)\n";
		} else {
			std::cout << "float: " << std::fixed
					  << std::setprecision(1)
					  << static_cast<float>(input) << "f\n";
			std::cout << "double: " << std::fixed
					  << std::setprecision(1) << input
					  << " (source)\n";
		}
	}
}

typedef void (*FuncPtr)(std::string const&);

void from_invalid(std::string const& literal) {
	std::cerr << "Invalid input: " << literal << " !\n";
}

// @follow-up needs additional checks
static FuncPtr from_type(std::string const& literal) {
	const size_t idx_dot      = literal.find(".", 1);
	const bool   is_pseudo_db = is_pseudo_double(literal);
	const bool   is_pseudo_f  = is_pseudo_float(literal);
	if (idx_dot != std::string::npos
		&& static_cast<std::string>(&literal.at(idx_dot))
				   .find(".", 1)
			   != std::string::npos) {
		return (&from_invalid);
	}
	if ((is_pseudo_db || is_pseudo_f)
		|| idx_dot != std::string::npos) {
		if ((literal.end()[-1] == 'f'
			 && std::isdigit(literal.end()[-2]))
			|| is_pseudo_f) {
			return (&from_float);
		}
		if (std::isdigit(literal.end()[-1]) || is_pseudo_db) {
			return (&from_double);
		}
	} else if (idx_dot == std::string::npos) {
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