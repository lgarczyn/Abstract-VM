#pragma once
#include "Exceptions/VMException.hpp"
#include "IOperand.hpp"
#include "Libs/SafeInt.hpp"

#include <string>

typedef SafeInt<int8_t> safe_int8;
typedef SafeInt<int16_t> safe_int16;
typedef SafeInt<int32_t> safe_int32;

// Implements all operations on the logical level
class AOperand : public virtual IOperand
{
  public:
	// Utility
	int getMaxPrecision( IOperand const& rhs ) const;

	// Operations
	IOperand const* operator+( IOperand const& rhs ) const;
	IOperand const* operator-( IOperand const& rhs ) const;
	IOperand const* operator*( IOperand const& rhs ) const;
	IOperand const* operator/( IOperand const& rhs ) const;
	IOperand const* operator%( IOperand const& rhs ) const;
	bool operator==( IOperand const& rhs ) const;
	bool operator!=( IOperand const& rhs ) const;

	// Cast to any of the underlying types
	virtual safe_int8 asI8() const = 0;
	virtual safe_int16 asI16() const = 0;
	virtual safe_int32 asI32() const = 0;
	virtual float asF32() const = 0;
	virtual double asF64() const = 0;
	virtual double asF80() const = 0;
	virtual bool isZero() const = 0;
};

// The type specific implementation of IOperand
// Handles type directly
template <typename T> class Operand : public AOperand
{

  private:
	static const eOperandType type;
	T _value;
	std::string _representation;

  public:
	// Coplien's form basic definitions
	Operand( T value );

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

	bool isZero( void ) const { return _value == 0; }

	bool operator!=( IOperand const& rhs ) const { return !( *this == rhs ); }

	std::string const& toString( void ) const { return this->_representation; }

	char toChar( void ) const
	{
		if ( type == TypeI8 )
			return _value;
		throw ForbiddenPrintException( this->getTypeName() );
	}

  private:
	// Casting functions

	safe_int8 asI8() const { return static_cast<safe_int8>( this->_value ); }

	safe_int16 asI16() const { return static_cast<safe_int16>( this->_value ); }

	safe_int32 asI32() const { return static_cast<safe_int32>( this->_value ); }

	float asF32() const { return static_cast<float>( this->_value ); }

	double asF64() const { return static_cast<double>( this->_value ); }

	double asF80() const { return static_cast<long double>( this->_value ); }

	static std::string toRepresentation( T i );
};

template<> Operand<safe_int8>::Operand( safe_int8 value );
template<> Operand<safe_int16>::Operand( safe_int16 value );
template<> Operand<safe_int32>::Operand( safe_int32 value );
template<> Operand<float>::Operand( float value );
template<> Operand<double>::Operand( double value );
template<> Operand<long double>::Operand( long double value );
