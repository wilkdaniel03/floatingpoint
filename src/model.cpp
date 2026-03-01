#include <iostream>
#include <cstdlib>
#include <cstdint>

#include <ac_int.h>

template <uint8_t size>
class ShiftRegister {
	ac_int<size,false> reg;
	bool directionRight;
public:
	ShiftRegister() : reg(ac_int<size,false>(0)), directionRight(true) {}
	ShiftRegister(const uint64_t val) : reg(ac_int<size,false>(val)) {}
	ShiftRegister(const bool directionRight) : reg(ac_int<size,false>(0)), directionRight(directionRight) {}
	ShiftRegister(const uint64_t val, const bool directionRight) : reg(ac_int<size,false>(val)), directionRight(directionRight) {}
	uint64_t operator*() const {
		return this->reg.to_int64();
	}
	void Shift() {
		if(this->directionRight) {
			this->reg >>= 1;
		} else {
			this->reg <<= 1;
		}
	}
};

int main(void) {
	ShiftRegister<10> reg(13,false);
	std::cout << *reg << std::endl;
	reg.Shift();
	std::cout << *reg << std::endl;
	reg.Shift();
	std::cout << *reg << std::endl;
	reg.Shift();
	std::cout << *reg << std::endl;
	reg.Shift();

	return EXIT_SUCCESS;
}
