#pragma once
#include <string>
#include "IOperand.hpp"
#include <cmath>

template <typename T>
class Operand: public IOperand {

private:
	static const eOperandType type;
	T value;
	std::string representation;

public:
	Operand(T value) : value(value), representation(std::to_string(value)) {}

	int getPrecision( void ) const {
		return static_cast<int>(type);
	}

	int getMaxPrecision( IOperand const& rhs ) const {
		return std::max(this->getPrecision(), rhs.getPrecision());
	} 
	
	eOperandType getType( void ) const {
		return type;
	}
	
	IOperand const *operator+( IOperand const& rhs ) const {
		int precision = this->getMaxPrecision(rhs);
		switch (precision) {
			case e_ty_i8: return new Operand(this->asI8() + rhs.asI8());
			case e_ty_i16: return new Operand(this->asI16() + rhs.asI16());
			case e_ty_i32: return new Operand(this->asI32() + rhs.asI32());
			case e_ty_f32: return new Operand(this->asF32() + rhs.asF32());
			case e_ty_f64: return new Operand(this->asF64() + rhs.asF64());
		}
		throw std::logic_error("bad type");
	}
	
	IOperand const *operator-( IOperand const& rhs ) const {
		int precision = this->getMaxPrecision(rhs);
		switch (precision) {
			case e_ty_i8: return new Operand(this->asI8() - rhs.asI8());
			case e_ty_i16: return new Operand(this->asI16() - rhs.asI16());
			case e_ty_i32: return new Operand(this->asI32() - rhs.asI32());
			case e_ty_f32: return new Operand(this->asF32() - rhs.asF32());
			case e_ty_f64: return new Operand(this->asF64() - rhs.asF64());
		}
		throw std::logic_error("bad type");
	}
	
	IOperand const *operator*( IOperand const& rhs ) const {
		int precision = this->getMaxPrecision(rhs);
		switch (precision) {
			case e_ty_i8: return new Operand(this->asI8() * rhs.asI8());
			case e_ty_i16: return new Operand(this->asI16() * rhs.asI16());
			case e_ty_i32: return new Operand(this->asI32() * rhs.asI32());
			case e_ty_f32: return new Operand(this->asF32() * rhs.asF32());
			case e_ty_f64: return new Operand(this->asF64() * rhs.asF64());
		}
		throw std::logic_error("bad type");
	}
	
	IOperand const *operator/( IOperand const& rhs ) const {
		int precision = this->getMaxPrecision(rhs);
		switch (precision) {
			case e_ty_i8: return new Operand(this->asI8() / rhs.asI8());
			case e_ty_i16: return new Operand(this->asI16() / rhs.asI16());
			case e_ty_i32: return new Operand(this->asI32() / rhs.asI32());
			case e_ty_f32: return new Operand(this->asF32() / rhs.asF32());
			case e_ty_f64: return new Operand(this->asF64() / rhs.asF64());
		}
		throw std::logic_error("bad type");
	}
	
	IOperand const *operator%( IOperand const& rhs ) const {
		int precision = this->getMaxPrecision(rhs);
		switch (precision) {
			case e_ty_i8: return new Operand(this->asI8() % rhs.asI8());
			case e_ty_i16: return new Operand(this->asI16() % rhs.asI16());
			case e_ty_i32: return new Operand(this->asI32() % rhs.asI32());
			case e_ty_f32: return new Operand(std::fmodf(this->asF32(), rhs.asF32()));
			case e_ty_f64: return new Operand(std::fmod(this->asF64(), rhs.asF64()));
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