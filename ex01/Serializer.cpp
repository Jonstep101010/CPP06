#include "Serializer.hpp"

/*
** ------------------------------- CONSTRUCTOR --------------------------------
*/

Serializer::Serializer() {}

Serializer::Serializer(const Serializer& src) {
	*this = src;
}

/*
** -------------------------------- DESTRUCTOR --------------------------------
*/

Serializer::~Serializer() {}

/*
** --------------------------------- OVERLOAD ---------------------------------
*/

Serializer&
Serializer::operator=(Serializer const& rhs) {
	(void)rhs;
	return *this;
}

/*
** --------------------------------- METHODS ----------------------------------
*/

// It takes a pointer and converts it to the unsigned integer type uintptr_t
uintptr_t Serializer::serialize(Data* ptr) {
	return reinterpret_cast<uintptr_t>(ptr);
}

// It takes an unsigned integer parameter and converts it to a pointer to Data
Data* Serializer::deserialize(uintptr_t raw) {
	return reinterpret_cast<Data*>(raw);
}

/*
** --------------------------------- ACCESSOR ---------------------------------
*/

/* ************************************************************************** */