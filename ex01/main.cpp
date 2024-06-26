#include "Serializer.hpp"
#include <iostream>
#include <stdint.h>

/*
static_casting a pointer to and from void* preserves the address.
That is, in the following, a, b and c all point to the same address:

int* a = new int();
void* b = static_cast<void*>(a);
int* c = static_cast<int*>(b);
reinterpret_cast only guarantees that if you cast a pointer to a different type
, and then reinterpret_cast it back to the original type, you get the original value.

So in the following:

int* a = new int();
void* b = reinterpret_cast<void*>(a);
int* c = reinterpret_cast<int*>(b);
a and c contain the same value, but the value of b is unspecified.
(in practice it will typically contain the same address as a and c)

For casting to and from void*, static_cast should be preferred.

abridged: https://stackoverflow.com/questions/573294/when-to-use-reinterpret-cast
*/

int main() {
	Data serializeData;
	serializeData.member = "membernonmod";

	uintptr_t serializedData
		= Serializer::serialize(&serializeData);
	Data* deserializedData
		= Serializer::deserialize(serializedData);

	std::cout << "original data value: " << serializeData.member
			  << "\t\t(" << std::hex << &serializeData
			  << ")\noriginal deserialized value: "
			  << deserializedData->member << "\t(" << std::hex
			  << deserializedData << ")\n";

	serializeData.member = "changed value!";
	std::cout << "changed data value: " << serializeData.member
			  << "\t\t(" << std::hex << &serializeData
			  << ")\nchanged deserialized value: "
			  << deserializedData->member << "\t(" << std::hex
			  << deserializedData << ")\n";
}