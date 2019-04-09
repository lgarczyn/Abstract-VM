#pragma once
#include <string>
#include "IOperand.hpp"
#include <cmath>
#include <sstream>
#include <iomanip>

template <typename T>
class Operand: public IOperand {

private:
	static const eOperandType type;
	T value;
	std::string representation;

public:
	Operand(T value) : value(value)
	{
		int precision = std::numeric_limits<T>::max_digits10 - 2;
		std::stringstream ss;
		ss << std::setprecision(precision) << +value;
		representation = ss.str();
	}
	int getPrecision( void ) const {
		return static_cast<int>(type);
	}

	int getMaxPrecision( IOperand const& rhs ) const {
		return std::max(this->getPrecision(), rhs.getPrecision());
	} 
	
	eOperandType getType( void ) const {
		return type;
	}

	bool isZero( void ) const {
		return value == 0;
	}

	IOperand const *operator+( IOperand const& rhs ) const {
		int precision = this->getMaxPrecision(rhs);
		switch (precision) {
			case e_ty_i8: return new Operand<int8_t>(this->asI8() + rhs.asI8());
			case e_ty_i16: return new Operand<int16_t>(this->asI16() + rhs.asI16());
			case e_ty_i32: return new Operand<int32_t>(this->asI32() + rhs.asI32());
			case e_ty_f32: return new Operand<float>(this->asF32() + rhs.asF32());
			case e_ty_f64: return new Operand<double>(this->asF64() + rhs.asF64());
		}
		throw std::logic_error("bad type");
	}
	
	IOperand const *operator-( IOperand const& rhs ) const {
		int precision = this->getMaxPrecision(rhs);
		switch (precision) {
			case e_ty_i8: return new Operand<int8_t>(this->asI8() - rhs.asI8());
			case e_ty_i16: return new Operand<int16_t>(this->asI16() - rhs.asI16());
			case e_ty_i32: return new Operand<int32_t>(this->asI32() - rhs.asI32());
			case e_ty_f32: return new Operand<float>(this->asF32() - rhs.asF32());
			case e_ty_f64: return new Operand<double>(this->asF64() - rhs.asF64());
		}
		throw std::logic_error("bad type");
	}
	
	IOperand const *operator*( IOperand const& rhs ) const {
		int precision = this->getMaxPrecision(rhs);
		switch (precision) {
			case e_ty_i8: return new Operand<int8_t>(this->asI8() * rhs.asI8());
			case e_ty_i16: return new Operand<int16_t>(this->asI16() * rhs.asI16());
			case e_ty_i32: return new Operand<int32_t>(this->asI32() * rhs.asI32());
			case e_ty_f32: return new Operand<float>(this->asF32() * rhs.asF32());
			case e_ty_f64: return new Operand<double>(this->asF64() * rhs.asF64());
		}
		throw std::logic_error("bad type");
	}
	
	IOperand const *operator/( IOperand const& rhs ) const {
		int precision = this->getMaxPrecision(rhs);
		switch (precision) {
			case e_ty_i8: return new Operand<int8_t>(this->asI8() / rhs.asI8());
			case e_ty_i16: return new Operand<int16_t>(this->asI16() / rhs.asI16());
			case e_ty_i32: return new Operand<int32_t>(this->asI32() / rhs.asI32());
			case e_ty_f32: return new Operand<float>(this->asF32() / rhs.asF32());
			case e_ty_f64: return new Operand<double>(this->asF64() / rhs.asF64());
		}
		throw std::logic_error("bad type");
	}
	
	IOperand const *operator%( IOperand const& rhs ) const {
		int precision = this->getMaxPrecision(rhs);
		switch (precision) {
			case e_ty_i8: return new Operand<int8_t>(this->asI8() % rhs.asI8());
			case e_ty_i16: return new Operand<int16_t>(this->asI16() % rhs.asI16());
			case e_ty_i32: return new Operand<int32_t>(this->asI32() % rhs.asI32());
			case e_ty_f32: return new Operand<float>(std::fmodf(this->asF32(), rhs.asF32()));
			case e_ty_f64: return new Operand<double>(std::fmod(this->asF64(), rhs.asF64()));
		}
		throw std::logic_error("bad type");
	}
	
	bool operator==( IOperand const& rhs ) const {
		int precision = this->getMaxPrecision(rhs);
		switch (precision) {
			case e_ty_i8: return this->asI8() == rhs.asI8();
			case e_ty_i16: return this->asI16() == rhs.asI16();
			case e_ty_i32: return this->asI32() == rhs.asI32();
			case e_ty_f32: return this->asF32() == rhs.asF32();
			case e_ty_f64: return this->asF64() == rhs.asF64();
		}
		throw std::logic_error("bad type");
	}
	
	std::string const &toString( void ) const {
		return this->representation;
	}
	
	int8_t asI8() const {
		return static_cast<int8_t>(this->value);
	}

	int16_t asI16() const {
		return static_cast<int16_t>(this->value);
	}

	int32_t asI32() const {
		return static_cast<int32_t>(this->value);
	}

	float asF32() const {
		return static_cast<float>(this->value);
	}

	double asF64() const {
		return static_cast<double>(this->value);
	}
};
