#include "Base.hpp"
#include "derived.hpp"
#include <cstdlib>

// randomly instanciates A, B or C and returns the instance as a Base pointer.
Base* generate(void) {
	// seed the random number generator

	// generate a random number of variance 3

	// std::srand(time(NULL));
	switch (std::rand() / (RAND_MAX / 3) % 3) {
	case 0:
		return new A;
	case 1:
		return new B;
	case 2:
		return new C;
	default:
		return NULL;
	}
}

// It prints the actual type of the object pointed to by p: "A", "B" or "C"
void identify(Base* p) {
	if (!p) {
		std::cout << "pointer to Base is null\n";
	} else if (dynamic_cast<A*>(p)) {
		std::cout << "A\n";
	} else if (dynamic_cast<B*>(p)) {
		std::cout << "B\n";
	} else if (dynamic_cast<C*>(p)) {
		std::cout << "C\n";
	}
}

// It prints the actual type of the object pointed to by p: "A", "B" or "C".
// Using a pointer inside this function is forbidden.
// including the typeinfo header is forbidden
void identify(Base& p) {
	// std::cerr << "Base ref is null\n";
	try {
		A& a = dynamic_cast<A&>(p);
		(void)a; // suppress warning (unused variable)
		std::cout << "A ref\n";
	} catch (std::exception& e) {
		try {
			B& b = dynamic_cast<B&>(p);
			(void)b; // suppress warning (unused variable)
			std::cout << "B ref\n";
		} catch (std::exception& e) {
			try {
				C& c = dynamic_cast<C&>(p);
				(void)c; // suppress warning (unused variable)
				std::cout << "C ref\n";
			} catch (std::exception& e) {
				std::cerr << "Base ref is null\n";
			}
		}
	}
}
