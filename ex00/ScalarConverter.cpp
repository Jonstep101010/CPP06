#include "ScalarConverter.hpp"

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

void ScalarConverter::convert(std::string const& literal) {
	char   scalar_char   = 0;
	int    scalar_int    = 0;
	float  scalar_float  = 0;
	double scalar_double = 0;

	// @follow-up put in trash bin
	// @todo build a type resolver
	if (literal.length() == 1) {
		scalar_char   = static_cast<char>(literal[0]);
		scalar_int    = static_cast<int>(literal[0]);
		scalar_float  = static_cast<float>(literal[0]);
		scalar_double = static_cast<double>(literal[0]);

		if (std::isprint(literal[0])) {
			std::cout << "char: '" << scalar_char << "'\n";
		} else {
			std::cout << "char: Non displayable\n";
		}
		std::cout << "int: " << scalar_int << std::endl;
		std::cout << "float: " << scalar_float << std::endl;
		std::cout << "double: " << scalar_double << std::endl;
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */