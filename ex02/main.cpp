#include "Base.hpp"
#include "derived.hpp"
#include "members.hpp"

int main() {

	A     instance_a;
	Base* sth = dynamic_cast<Base*>(&instance_a);

	identify(sth);
	A* a = dynamic_cast<A*>(sth);

	identify(dynamic_cast<Base*>(a));

	std::cout << "\nrandom:\n";
	identify(generate());
	identify(generate());
	identify(generate());
	identify(generate());
	identify(generate());
	identify(generate());

	// we need a base reference to pass to identify
	Base* ptr = generate();
	Base& ref = *ptr;

	identify(ref);
}