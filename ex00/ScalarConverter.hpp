#pragma once
#include <string>

class ScalarConverter {

public:
	ScalarConverter(ScalarConverter const& src);
	~ScalarConverter();

	static void convert(std::string const& literal);

	ScalarConverter& operator=(ScalarConverter const& rhs);

private:
	ScalarConverter();
};
