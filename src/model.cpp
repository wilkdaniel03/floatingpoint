#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <concepts>
#include <cmath>
#include <memory>
#include <format>

#include <ac_int.h>
#include <ac_float.h>

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

template <uint8_t S, uint8_t I, uint8_t E>
ac_float<S,I,E> add_float(ac_float<S,I,E> f1, ac_float<S,I,E> f2) {
	if(f2.exp() > f1.exp()) std::swap(f1,f2);
	uint32_t diff = f1.exp() - f2.exp();
	auto f2Mant = f2.mantissa() >> diff;
	ac_float<S,I,E> res = 0.0;
	auto mantSum = f1.mantissa() + f2Mant;
	mantSum >>= 1;
	res.set_mantissa(mantSum);
	res.set_exp(f1.exp() + 1);
	return res;
}

int main(void) {
	ac_float<32,24,8> f1 = 1.2;
	ac_float<32,24,8> f2 = 1.5;
	std::cout << f1.mantissa() << ", " << f1.exp() << ", " << f1.to_string(ac_base_mode::AC_BIN) << std::endl;
	std::cout << f2.mantissa() << ", " << f2.exp() << ", " << f2.to_string(ac_base_mode::AC_BIN) << std::endl;
	std::cout << f1.to_double() << " + " << f2.to_double() << " = " << add_float<32,24,8>(f1,f2).to_double() << std::endl;

	return EXIT_SUCCESS;
}
