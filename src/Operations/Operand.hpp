#pragma once
#include <string>
#include "IOperand.hpp"
#include <cmath>
#include <sstream>
#include <iomanip>
#include <iostream>

template <typename T>
class Operand: public IOperand {

private:
	static const eOperandType type;
	T value;
	std::string representation;


	static std::string string_ugly(safe_int8 i)
	{
		return std::to_string(i.Ref());
	}
	static std::string string_ugly(safe_int16 i)
	{
		return std::to_string(i.Ref());
	}
	static std::string string_ugly(safe_int32 i)
	{
		return std::to_string(i.Ref());
	}
	static std::string string_ugly(float f)
	{
		int precision = std::numeric_limits<T>::max_digits10 - 2;
		std::stringstream ss;
		ss << std::setprecision(precision) << f;
		return ss.str();
	}
	static std::string string_ugly(double f)
	{
		int precision = std::numeric_limits<T>::max_digits10 - 2;
		std::stringstream ss;
		ss << std::setprecision(precision) << f;
		return ss.str();
	}
public:
	Operand(T value) : value(value)
	{
		representation = string_ugly(value);
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
	
	const std::string &getTypeName( void ) const {
		return IOperand::operands[type].name;
	}

	bool isZero( void ) const {
		return value == 0;
	}

	IOperand const *operator+( IOperand const& rhs ) const {
		int precision = this->getMaxPrecision(rhs);
		switch (precision) {
			case e_ty_i8: return new Operand<safe_int8>(this->asI8() + rhs.asI8());
			case e_ty_i16: return new Operand<safe_int16>(this->asI16() + rhs.asI16());
			case e_ty_i32: return new Operand<safe_int32>(this->asI32() + rhs.asI32());
			case e_ty_f32: return new Operand<float>(this->asF32() + rhs.asF32());
			case e_ty_f64: return new Operand<double>(this->asF64() + rhs.asF64());
		}
		throw std::logic_error("Bad operand type");
	}
	
	IOperand const *operator-( IOperand const& rhs ) const {
		int precision = this->getMaxPrecision(rhs);
		switch (precision) {
			case e_ty_i8: return new Operand<safe_int8>(this->asI8() - rhs.asI8());
			case e_ty_i16: return new Operand<safe_int16>(this->asI16() - rhs.asI16());
			case e_ty_i32: return new Operand<safe_int32>(this->asI32() - rhs.asI32());
			case e_ty_f32: return new Operand<float>(this->asF32() - rhs.asF32());
			case e_ty_f64: return new Operand<double>(this->asF64() - rhs.asF64());
		}
		throw std::logic_error("Bad operand type");
	}
	
	IOperand const *operator*( IOperand const& rhs ) const {
		int precision = this->getMaxPrecision(rhs);
		switch (precision) {
			case e_ty_i8: return new Operand<safe_int8>(this->asI8() * rhs.asI8());
			case e_ty_i16: return new Operand<safe_int16>(this->asI16() * rhs.asI16());
			case e_ty_i32: return new Operand<safe_int32>(this->asI32() * rhs.asI32());
			case e_ty_f32: return new Operand<float>(this->asF32() * rhs.asF32());
			case e_ty_f64: return new Operand<double>(this->asF64() * rhs.asF64());
		}
		throw std::logic_error("Bad operand type");
	}
	
	IOperand const *operator/( IOperand const& rhs ) const {
		int precision = this->getMaxPrecision(rhs);
		switch (precision) {
			case e_ty_i8: return new Operand<safe_int8>(this->asI8() / rhs.asI8());
			case e_ty_i16: return new Operand<safe_int16>(this->asI16() / rhs.asI16());
			case e_ty_i32: return new Operand<safe_int32>(this->asI32() / rhs.asI32());
			case e_ty_f32: return new Operand<float>(this->asF32() / rhs.asF32());
			case e_ty_f64: return new Operand<double>(this->asF64() / rhs.asF64());
		}
		throw std::logic_error("Bad operand type");
	}
	
	IOperand const *operator%( IOperand const& rhs ) const {
		int precision = this->getMaxPrecision(rhs);
		switch (precision) {
			case e_ty_i8: return new Operand<safe_int8>(this->asI8() % rhs.asI8());
			case e_ty_i16: return new Operand<safe_int16>(this->asI16() % rhs.asI16());
			case e_ty_i32: return new Operand<safe_int32>(this->asI32() % rhs.asI32());
			case e_ty_f32: return new Operand<float>(std::fmodf(this->asF32(), rhs.asF32()));
			case e_ty_f64: return new Operand<double>(std::fmod(this->asF64(), rhs.asF64()));
		}
		throw std::logic_error("Bad operand type");
	}
	
	bool operator==( IOperand const& rhs ) const {
		std::cout << this->asF64() << "==" << rhs.asF64() << std::endl;
		int precision = this->getMaxPrecision(rhs);
		switch (precision) {
			case e_ty_i8: return this->asI8() == rhs.asI8();
			case e_ty_i16: return this->asI16() == rhs.asI16();
			case e_ty_i32: return this->asI32() == rhs.asI32();
			case e_ty_f32: return this->asF32() == rhs.asF32();
			case e_ty_f64: return this->asF64() == rhs.asF64();
		}
		throw std::logic_error("Bad operand type");
	}

	bool operator!=( IOperand const& rhs ) const {
		return !(*this == rhs);
	}

	std::string const &toString( void ) const {
		return this->representation;
	}
	
	safe_int8 asI8() const {
		return static_cast<safe_int8>(this->value);
	}

	safe_int16 asI16() const {
		return static_cast<safe_int16>(this->value);
	}

	safe_int32 asI32() const {
		return static_cast<safe_int32>(this->value);
	}

	float asF32() const {
		return static_cast<float>(this->value);
	}

	double asF64() const {
		return static_cast<double>(this->value);
	}
};
