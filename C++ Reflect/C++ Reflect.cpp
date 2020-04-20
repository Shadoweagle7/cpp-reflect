// C++ Reflect.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "reflect.h"

class test {
private:
	int num;
	double num2;
public:
	float num3;

	test(int num, double num2) : num(num), num2(num2) {}

	int a() const & {
		return this->num;
	}
};

void boing() {}

test boing2(test t, int i1, std::ios i2) { return test(27, 9.9999); }

int main() {
	test aa(27, 9.999999999999);

	int ba = aa.a();

	test(0, 0.0000001).a();

	SE7::reflect<SE7::base> b_reflector;
	SE7::reflect<SE7::base> c_reflector;
	SE7::reflect<decltype(boing)> boing_reflector;
	SE7::reflect<decltype(boing2)> boing2_reflector;
	SE7::reflect<decltype(&test::a)> test_a_reflector;
	SE7::reflect<void *> vp_reflector;

	std::cout << "Name: " << b_reflector.get_name() << " | Size: " << b_reflector.get_size_in_bytes() << std::endl;
	std::cout << "Name: " << boing_reflector.get_name() << " | Pointer Size: " << boing_reflector.get_pointer_size() << " | Minimum Frame Size: " << boing_reflector.get_minimum_frame_size() << std::endl;
	std::cout << "Name: " << boing2_reflector.get_name() << " | Pointer Size: " << boing2_reflector.get_pointer_size() << " | Minimum Frame Size: " << boing2_reflector.get_minimum_frame_size()  << std::endl;
	std::cout << "Name: " << test_a_reflector.get_name() << " | Pointer Size: " << test_a_reflector.get_pointer_size() << " | Minimum Frame Size: " << test_a_reflector.get_minimum_frame_size()  << std::endl;
	boing2_reflector.get_reflected_type_of_arg<0>();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
