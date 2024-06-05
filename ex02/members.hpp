#pragma once

#include "Base.hpp"

// randomly instanciates A, B or C and returns the instance as a Base pointer.
Base* generate(void);

// It prints the actual type of the object pointed to by p: "A", "B" or "C"
void identify(Base* p);

// It prints the actual type of the object pointed to by p: "A", "B" or "C".
// Using a pointer inside this function is forbidden.
// including the typeinfo header is forbidden
void identify(Base& p);
