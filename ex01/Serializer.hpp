#pragma once
#include <stdint.h>
#include <string>

struct Data {
	std::string member;
};

class Serializer {

public:
	Serializer(Serializer const& src);
	~Serializer();

	Serializer&      operator=(Serializer const& rhs);
	static uintptr_t serialize(Data* ptr);
	static Data*     deserialize(uintptr_t raw);

private:
	Serializer();
};
