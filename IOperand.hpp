#pragma once
#include <string>

enum eOperandType {
	i8 = 0,
	i16 = 1,
	i32 = 2,
	f32 = 3,
	f64 = 4,
	OPERAND_TYPE_NUM = 5,
};

class IOperand {
	public:
	// Precision of the type of the instance
	virtual int getPrecision( void ) const = 0;
	// Type of the instance
	virtual eOperandType getType( void ) const = 0;
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
	// String representation of the instance
	virtual std::string const &toString( void ) const = 0;

	virtual int8_t asI8() const = 0;
	virtual int16_t asI16() const = 0;
	virtual int32_t asI32() const = 0;
	virtual float asF32() const = 0;
	virtual double asF64() const = 0;

	~IOperand( void ) {}
};
