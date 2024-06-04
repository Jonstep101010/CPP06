#include "ScalarConverter.hpp"
#include <cstdlib>
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
	ERR,
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
	const int input = std::atoi(literal.c_str());

	if (std::isprint(input)) {
		std::cout << "char: '" << static_cast<char>(input)
				  << "'\n";
	} else {
		std::cout << "char: Non displayable\n";
	}

	std::cout << "int: " << input << " (source)\n";
	std::cout << "float: " << static_cast<float>(input)
			  << ".0f\n";
	std::cout << "double: " << static_cast<double>(input)
			  << ".0\n";
}

static void from_float(std::string const& literal) {
	const float input
		= static_cast<float>(std::atof(literal.c_str()));

	if (is_pseudo_float(literal)) {
		std::cout << "char: impossible\n";
		std::cout << "int: impossible\n";
		std::cout << "float: " << input << "f (source)\n";
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
			std::cout << "float: " << input << ".0f (source)\n";
			std::cout << "double: " << static_cast<double>(input)
					  << ".0\n";
		} else {
			std::cout << "float: " << input << "f (source)\n";
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
		std::cout << "float: " << static_cast<float>(input)
				  << "f \n";
		std::cout << "double: " << input << " (source)\n";
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
			std::cout << "float: " << static_cast<float>(input)
					  << ".0f\n";
			std::cout << "double: " << input << ".0 (source)\n";
		} else {
			std::cout << "float: " << static_cast<float>(input)
					  << "f\n";
			std::cout << "double: " << input << " (source)\n";
		}
	}
}

bool check_int(std::string const& literal) {
	// std::cout << "int check for: " << literal << "\n";
	if (literal.find_first_of(".f") != std::string::npos) {
		return (false);
	}
	return true;
}

// @follow-up use function pointers like so:
// typedef bool (*FuncPtr)(std::string const&);
// FuncPtr from_type(...)

// @follow-up needs additional checks
static Type get_type(std::string const& literal) {
	// @todo deeper checks
	if ((literal.end()[-1] == 'f' && literal.end()[-3] == '.'
		 && std::isdigit(literal.end()[-2]))
		|| is_pseudo_float(literal)) {
		return (FLOAT);
	}
	if (literal.end()[-2] == '.' || is_pseudo_double(literal)) {
		return (DOUBLE);
	}
	if (literal.length() == 1 && std::iswalpha(literal[0])) {
		return (CHAR);
	}
	if (check_int(literal)) {
		return (INT);
	}
	return (ERR);
}

static void converter(std::string const& literal) {
	Converter self = {.type = get_type(literal)};

	// @follow-up dispatch using function pointers
	switch (self.type) {
	case CHAR:
		from_char(literal);
		break;
	case INT:
		from_int(literal);
		break;
	case FLOAT:
		from_float(literal);
		break;
	case DOUBLE:
		from_double(literal);
		break;
	default:
		std::cerr << "An error occurred. Terminating!\n";
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
	if ((literal.length() == 1
		 || (literal.length() > 1 && !contains_chars(literal)))
		&& get_type(literal) != ERR) {
		converter(literal);
	} else {
		std::cerr << "Error: invalid literal\n";
	}
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */