#include <iostream>
#include <cstdlib>
#include <concepts>

template <typename T>
requires std::floating_point<T>
T malcomm_radix() {
	double a,b;
	a = 1.0;
	while((a+1.0) - a == 1.0) {
		a *= 2.0;
	}
	b = 1.0;
	while((a+b) - a != b) {
		b += 1.0;
	}
	return b;
}

int main(void) {
	std::cout << "Radix: " << malcomm_radix<float>() << std::endl;
	std::cout << "Radix: " << malcomm_radix<double>() << std::endl;
	return EXIT_SUCCESS;
}
