#pragma once
#include "Exceptions/VMException.hpp"
#include "IOperand.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

template <typename T> class Operand : public IOperand
{

  private:
	static const eOperandType type;
	T value;
	std::string representation;

  public:
	Operand( T value )
		: value( value )
	{
		representation = to_representation( value );
	}

	Operand()
		: Operand( 0 )
	{
	}
	Operand( const Operand& cpy ) = default;
	Operand& operator=( const Operand& rhs ) = default;
	~Operand() = default;

	const IOperand* clone() const { return new Operand( *this ); }

	int getPrecision( void ) const { return static_cast<int>( type ); }

	int getMaxPrecision( IOperand const& rhs ) const
	{
		return std::max( this->getPrecision(), rhs.getPrecision() );
	}

	eOperandType getType( void ) const { return type; }

	const std::string& getTypeName( void ) const { return IOperand::operands[ type ].name; }

	bool isZero( void ) const { return value == 0; }

	IOperand const* operator+( IOperand const& rhs ) const
	{
		int precision = this->getMaxPrecision( rhs );
		switch ( precision )
		{
		case e_ty_i8: return new Operand<safe_int8>( this->asI8() + rhs.asI8() );
		case e_ty_i16: return new Operand<safe_int16>( this->asI16() + rhs.asI16() );
		case e_ty_i32: return new Operand<safe_int32>( this->asI32() + rhs.asI32() );
		case e_ty_f32: return new Operand<float>( this->asF32() + rhs.asF32() );
		case e_ty_f64: return new Operand<double>( this->asF64() + rhs.asF64() );
		case e_ty_f80: return new Operand<long double>( this->asF80() + rhs.asF80() );
		}
		throw CorruptOperandException();
	}

	IOperand const* operator-( IOperand const& rhs ) const
	{
		int precision = this->getMaxPrecision( rhs );
		switch ( precision )
		{
		case e_ty_i8: return new Operand<safe_int8>( this->asI8() - rhs.asI8() );
		case e_ty_i16: return new Operand<safe_int16>( this->asI16() - rhs.asI16() );
		case e_ty_i32: return new Operand<safe_int32>( this->asI32() - rhs.asI32() );
		case e_ty_f32: return new Operand<float>( this->asF32() - rhs.asF32() );
		case e_ty_f64: return new Operand<double>( this->asF64() - rhs.asF64() );
		case e_ty_f80: return new Operand<long double>( this->asF80() - rhs.asF80() );
		}
		throw CorruptOperandException();
	}

	IOperand const* operator*( IOperand const& rhs ) const
	{
		int precision = this->getMaxPrecision( rhs );
		switch ( precision )
		{
		case e_ty_i8: return new Operand<safe_int8>( this->asI8() * rhs.asI8() );
		case e_ty_i16: return new Operand<safe_int16>( this->asI16() * rhs.asI16() );
		case e_ty_i32: return new Operand<safe_int32>( this->asI32() * rhs.asI32() );
		case e_ty_f32: return new Operand<float>( this->asF32() * rhs.asF32() );
		case e_ty_f64: return new Operand<double>( this->asF64() * rhs.asF64() );
		case e_ty_f80: return new Operand<long double>( this->asF80() * rhs.asF80() );
		}
		throw CorruptOperandException();
	}

	IOperand const* operator/( IOperand const& rhs ) const
	{
		int precision = this->getMaxPrecision( rhs );
		switch ( precision )
		{
		case e_ty_i8: return new Operand<safe_int8>( this->asI8() / rhs.asI8() );
		case e_ty_i16: return new Operand<safe_int16>( this->asI16() / rhs.asI16() );
		case e_ty_i32: return new Operand<safe_int32>( this->asI32() / rhs.asI32() );
		case e_ty_f32: return new Operand<float>( this->asF32() / rhs.asF32() );
		case e_ty_f64: return new Operand<double>( this->asF64() / rhs.asF64() );
		case e_ty_f80: return new Operand<long double>( this->asF80() / rhs.asF80() );
		}
		throw CorruptOperandException();
	}

	IOperand const* operator%( IOperand const& rhs ) const
	{
		int precision = this->getMaxPrecision( rhs );
		switch ( precision )
		{
		case e_ty_i8: return new Operand<safe_int8>( this->asI8() % rhs.asI8() );
		case e_ty_i16: return new Operand<safe_int16>( this->asI16() % rhs.asI16() );
		case e_ty_i32: return new Operand<safe_int32>( this->asI32() % rhs.asI32() );
		case e_ty_f32: return new Operand<float>( std::fmodf( this->asF32(), rhs.asF32() ) );
		case e_ty_f64: return new Operand<double>( std::fmod( this->asF64(), rhs.asF64() ) );
		case e_ty_f80: return new Operand<long double>( std::fmodl( this->asF80(), rhs.asF80() ) );
		}
		throw CorruptOperandException();
	}

	bool operator==( IOperand const& rhs ) const
	{
		int precision = this->getMaxPrecision( rhs );
		switch ( precision )
		{
		case e_ty_i8: return this->asI8() == rhs.asI8();
		case e_ty_i16: return this->asI16() == rhs.asI16();
		case e_ty_i32: return this->asI32() == rhs.asI32();
		case e_ty_f32: return this->asF32() == rhs.asF32();
		case e_ty_f64: return this->asF64() == rhs.asF64();
		case e_ty_f80: return this->asF80() == rhs.asF80();
		}
		throw CorruptOperandException();
	}

	bool operator!=( IOperand const& rhs ) const { return !( *this == rhs ); }

	std::string const& toString( void ) const { return this->representation; }

  private:
	safe_int8 asI8() const { return static_cast<safe_int8>( this->value ); }

	safe_int16 asI16() const { return static_cast<safe_int16>( this->value ); }

	safe_int32 asI32() const { return static_cast<safe_int32>( this->value ); }

	float asF32() const { return static_cast<float>( this->value ); }

	double asF64() const { return static_cast<double>( this->value ); }

	double asF80() const { return static_cast<long double>( this->value ); }

	static std::string to_representation( safe_int8 i )
	{
		return std::to_string( static_cast<int64_t>( i ) );
	}
	static std::string to_representation( safe_int16 i )
	{
		return std::to_string( static_cast<int64_t>( i ) );
	}
	static std::string to_representation( safe_int32 i )
	{
		return std::to_string( static_cast<int64_t>( i ) );
	}
	static std::string to_representation( float f )
	{
		int precision = std::numeric_limits<T>::max_digits10 - 2;
		std::stringstream ss;
		ss << std::setprecision( precision ) << f;
		return ss.str();
	}
	static std::string to_representation( double f )
	{
		int precision = std::numeric_limits<T>::max_digits10 - 2;
		std::stringstream ss;
		ss << std::setprecision( precision ) << f;
		return ss.str();
	}
	static std::string to_representation( long double f )
	{
		int precision = std::numeric_limits<T>::max_digits10 - 2;
		std::stringstream ss;
		ss << std::setprecision( precision ) << f;
		return ss.str();
	}
};
