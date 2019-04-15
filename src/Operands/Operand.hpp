#pragma once
#include "Exceptions/VMException.hpp"
#include "IOperand.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// Implements all operations on the logical level
class AOperand : public virtual IOperand
{
  public:
	int getMaxPrecision( IOperand const& rhs ) const;
	IOperand const* operator+( IOperand const& rhs ) const;
	IOperand const* operator-( IOperand const& rhs ) const;
	IOperand const* operator*( IOperand const& rhs ) const;
	IOperand const* operator/( IOperand const& rhs ) const;
	IOperand const* operator%( IOperand const& rhs ) const;
	bool operator==( IOperand const& rhs ) const;
	bool operator!=( IOperand const& rhs ) const;
};

// The type specific implementation of IOperand
// Handles type directly
template <typename T> class Operand : public AOperand
{

  private:
	static const eOperandType type;
	T value;
	std::string representation;

  public:
	// Coplien's form basic definitions
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

	// Various utility functions
	const IOperand* clone() const { return new Operand( *this ); }

	int getPrecision( void ) const { return static_cast<int>( type ); }

	eOperandType getType( void ) const { return type; }

	const std::string& getTypeName( void ) const { return IOperand::operands[ type ].name; }

	bool isZero( void ) const { return value == 0; }

	bool operator!=( IOperand const& rhs ) const { return !( *this == rhs ); }

	std::string const& toString( void ) const { return this->representation; }

  private:
	// Casting functions

	safe_int8 asI8() const { return static_cast<safe_int8>( this->value ); }

	safe_int16 asI16() const { return static_cast<safe_int16>( this->value ); }

	safe_int32 asI32() const { return static_cast<safe_int32>( this->value ); }

	float asF32() const { return static_cast<float>( this->value ); }

	double asF64() const { return static_cast<double>( this->value ); }

	double asF80() const { return static_cast<long double>( this->value ); }

	static std::string to_representation( safe_int8 i );
	static std::string to_representation( safe_int16 i );
	static std::string to_representation( safe_int32 i );
	static std::string to_representation( float f );
	static std::string to_representation( double f );
	static std::string to_representation( long double f );
};