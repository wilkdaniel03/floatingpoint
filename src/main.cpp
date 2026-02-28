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

template <typename T>
requires std::floating_point<T>
T malcomm_precision() {
	auto radix = malcomm_radix<T>();
	T a = 1.0f;
	T i = 0.0f;
	while((a+1.0f) - a == 1.0f) {
		a *= radix;
		i++;
	}
	return i;
}

int main(void) {
	std::cout << "Radix(32-bit): " << malcomm_radix<float>() << std::endl;
	std::cout << "Radix(64-bit): " << malcomm_radix<double>() << std::endl;
	std::cout << "Precision(32-bit): " << malcomm_precision<float>() << std::endl;
	std::cout << "Precision(64-bit): " << malcomm_precision<double>() << std::endl;
	return EXIT_SUCCESS;
}
