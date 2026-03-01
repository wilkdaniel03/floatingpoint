#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <concepts>
#include <cmath>
#include <memory>
#include <any>

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
	ShiftRegister(const int32_t val) : reg(ac_int<size,false>(val)), directionRight(true) {}
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
	void operator-=(const uint32_t val) {
		this->reg -= val;
	}
	bool CheckRco() const {
		auto maxValue = std::pow(2.0,size) - 1.0;
		return this->reg.to_uint64() == maxValue;
	}
	bool CheckEmpty() const {
		return this->reg.to_uint64() == 0;
	}
};

template <uint8_t size>
requires SizeConcept<size>
class NBitShifter {
	static constexpr uint8_t counterWidth = std::ceil(std::log2(size))+1;
	ShiftRegister<size> reg;
	Counter<counterWidth> counter;
public:
	NBitShifter() : counter(Counter<counterWidth>((int32_t) std::pow(2.0,counterWidth))) {}
	NBitShifter(const int32_t val, const int32_t shiftCount) : reg(ShiftRegister<size>(val)), counter(Counter<counterWidth>(shiftCount)) {}
	void Shift() {
		while(*this->counter != 0) {
			this->reg.Shift();
			this->counter -= 1;
		}
	}
	uint64_t operator*() const {
		return *this->reg;
	}
};

int main(void) {
	NBitShifter<10> shifter(327,6);
	std::cout << "Start -> " << *shifter << std::endl;
	shifter.Shift();
	std::cout << *shifter << ", " << (327 >> 6) << std::endl;

	return EXIT_SUCCESS;
}
