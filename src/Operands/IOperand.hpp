#pragma once
#include "Libs/SafeInt.hpp"

#include <ostream>
#include <string>

enum eOperandType
{
	e_ty_i8 = 0,
	e_ty_i16 = 1,
	e_ty_i32 = 2,
	e_ty_f32 = 3,
	e_ty_f64 = 4,
	e_ty_f80 = 5,
	OPERAND_TYPE_NUM = 6,
};

typedef SafeInt<int8_t> safe_int8;
typedef SafeInt<int16_t> safe_int16;
typedef SafeInt<int32_t> safe_int32;

struct OperandInfo
{
	OperandInfo();
	OperandInfo( const OperandInfo& cpy );
	OperandInfo( eOperandType, std::string );
	OperandInfo& operator=( const OperandInfo& rhs );
	~OperandInfo();

	eOperandType type;
	std::string name;
};

// Represents a value of abritrary precision
class IOperand
{
  public:
	// List of operand types and associated info
	static const OperandInfo operands[ OPERAND_TYPE_NUM ];
	// Precision of the type of the instance
	virtual int getPrecision( void ) const = 0;
	// Type of the instance
	virtual eOperandType getType( void ) const = 0;
	// String representation of the type of the instance
	virtual std::string const& getTypeName( void ) const = 0;
	// Sum
	virtual IOperand const* operator+( IOperand const& rhs ) const = 0;
	// Difference
	virtual IOperand const* operator-( IOperand const& rhs ) const = 0;
	// Product
	virtual IOperand const* operator*( IOperand const& rhs ) const = 0;
	// Quotient
	virtual IOperand const* operator/( IOperand const& rhs ) const = 0;
	// Modulo
	virtual IOperand const* operator%( IOperand const& rhs ) const = 0;
	// Equality
	virtual bool operator==( IOperand const& rhs ) const = 0;
	virtual bool operator!=( IOperand const& rhs ) const = 0;
	// String representation of the instance
	virtual std::string const& toString( void ) const = 0;

	// Cast to any of the underlying types
	virtual safe_int8 asI8() const = 0;
	virtual safe_int16 asI16() const = 0;
	virtual safe_int32 asI32() const = 0;
	virtual float asF32() const = 0;
	virtual double asF64() const = 0;
	virtual double asF80() const = 0;
	virtual bool isZero() const = 0;

	virtual const IOperand* clone() const = 0;
	virtual ~IOperand( void ) {}
};

std::ostream& operator<<( std::ostream& out, const IOperand& rhs );