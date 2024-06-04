#include "ScalarConverter.hpp"
#include <iostream>

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

enum Type {
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
};

struct Converter {
	Type type;
	// void (*convert)(std::string const& literal);
};

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

// static void from_char(std::string const& literal);
// static void from_int(std::string const& literal);
// static void from_float(std::string const& literal);
// static void from_double(std::string const& literal);

// @follow-up use function pointers like so:
// typedef bool (*FuncPtr)(std::string const&);
// FuncPtr from_type(...)
static Type
get_type(std::string const&
			 literal) { // @follow-up needs additional checks
	if (is_pseudo_double(literal)
		|| is_pseudo_float(literal)) { // remove
		std::cout << "pseudo literal\n";
	}
	if (literal.end()[-1] == 'f'
		|| is_pseudo_float(literal)) { // @todo deeper checks
		std::cout << "float\n";
		return (FLOAT);
	}
	if (literal.end()[-2] == '.' || is_pseudo_double(literal)) {
		std::cout << "double\n";
		return (DOUBLE);
	}
	if (literal.length() == 1 && std::iswalpha(literal[0])) {
		std::cout << "char\n";
		return (CHAR);
	}
	std::cout << "int\n";
	return (INT);
}

static void converter(std::string const& literal) {
	Converter self = {.type = get_type(literal)};

	// @follow-up dispatch using function pointers
	switch (self.type) {
	case CHAR:
		// from_char(literal);
		break;
	case INT:
		// from_int(literal);
		break;
	case FLOAT:
		// from_float(literal);
		break;
	case DOUBLE:
		// from_double(literal);
		break;
	}

	// @follow-up handle non print characters
	// @follow-up handle precision
	// @follow-up handle int (0, -42, 42)
	// @follow-up handle char ('a', 'b', 'c')
	// @follow-up handle double (0.0, -4.2, 4.2)
	// @follow-up handle float (0.0f, -4.2f, 4.2f)
	// @follow-up handle pseudo literals -inff, +inff, +inf, nanf, -inf, nan
}

// @follow-up handle non print characters
void ScalarConverter::convert(std::string const& literal) {
	// @follow-up put in trash bin
	// @todo build a type resolver
	if (literal.length() == 1
		|| (literal.length() > 1 && !contains_chars(literal))) {
		converter(literal);
	} else {
		std::cerr << "Error: invalid literal\n";
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */