#pragma once
#include <string>
#include <ostream>
#include "Libs/SafeInt.hpp"

enum eOperandType {
	e_ty_i8 = 0,
	e_ty_i16 = 1,
	e_ty_i32 = 2,
	e_ty_f32 = 3,
	e_ty_f64 = 4,
	OPERAND_TYPE_NUM = 5,
};

typedef SafeInt<int8_t> safe_int8;
typedef SafeInt<int16_t> safe_int16;
typedef SafeInt<int32_t> safe_int32;

struct OperandInfo
{
	eOperandType type;
	const std::string name;
};

class IOperand {
	public:
	// List of operand types and associated info
	static const OperandInfo operands[OPERAND_TYPE_NUM];
	// Precision of the type of the instance
	virtual int getPrecision( void ) const = 0;
	// Type of the instance
	virtual eOperandType getType( void ) const = 0;
	// String representation of the type of the instance
	virtual std::string const &getTypeName( void ) const = 0;
	// Sum
	virtual IOperand const *operator+( IOperand const & rhs ) const = 0;
	// Difference
	virtual IOperand const *operator-( IOperand const & rhs ) const = 0;
	// Product
	virtual IOperand const *operator*( IOperand const & rhs ) const = 0;
	// Quotient
	virtual IOperand const *operator/( IOperand const & rhs ) const = 0;
	// Modulo
	virtual IOperand const *operator%( IOperand const & rhs ) const = 0;
	// Equality
	virtual bool operator==( IOperand const & rhs ) const = 0;
	virtual bool operator!=( IOperand const & rhs ) const = 0;
	// String representation of the instance
	virtual std::string const &toString( void ) const = 0;

	virtual safe_int8 asI8() const = 0;
	virtual safe_int16 asI16() const = 0;
	virtual safe_int32 asI32() const = 0;
	virtual float asF32() const = 0;
	virtual double asF64() const = 0;
	virtual bool isZero() const = 0;

	virtual ~IOperand( void ) {}
};

std::ostream &operator<<(std::ostream &out, const IOperand &rhs);