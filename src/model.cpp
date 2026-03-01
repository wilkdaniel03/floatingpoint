#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <concepts>
#include <cmath>

#include <ac_int.h>

template <uint8_t size>
concept SizeConcept = size <= 64;

template <uint8_t size>
requires SizeConcept<size>
class ShiftRegister {
	ac_int<size,false> reg;
	bool directionRight;
public:
	ShiftRegister() : reg(ac_int<size,false>(0)), directionRight(true) {}
	ShiftRegister(const int32_t val) : reg(ac_int<size,false>(val)) {}
	ShiftRegister(const bool directionRight) : reg(ac_int<size,false>(0)), directionRight(directionRight) {}
	ShiftRegister(const uint64_t val, const bool directionRight) : reg(ac_int<size,false>(val)), directionRight(directionRight) {}
	uint64_t operator*() const {
		return this->reg.to_uint64();
	}
	void Shift() {
		if(this->directionRight) {
			this->reg >>= 1;
		} else {
			this->reg <<= 1;
		}
	}
};

template <uint8_t size>
requires SizeConcept<size>
class Counter {
	ac_int<size,false> reg;
public:
	Counter() : reg(ac_int<size,false>(0)) {}
	Counter(const int32_t val) : reg(ac_int<size,false>(val)) {}
	uint64_t operator*() const {
		return this->reg.to_uint64();
	}
	void operator+=(const uint32_t val) {
		this->reg += val;
	}
	bool CheckRco() const {
		auto maxValue = std::pow(2.0,size) - 1.0;
		return this->reg.to_uint64() == maxValue;
	}
};

int main(void) {
	ShiftRegister<8> reg(13);
	Counter<2> counter;

	return EXIT_SUCCESS;
}
