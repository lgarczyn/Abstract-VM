#pragma once

#include <string>

enum eOperandType
{
	TypeI8 = 0,
	TypeI16 = 1,
	TypeI32 = 2,
	TypeF32 = 3,
	TypeF64 = 4,
	TypeF80 = 5,
	OPERAND_TYPE_NUM = 6,
};

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
	virtual bool isZero() const = 0;
	// String representation of the instance
	virtual std::string const& toString( void ) const = 0;
	virtual char toChar( void ) const = 0;

	virtual const IOperand* clone() const = 0;
	virtual ~IOperand( void ) {}
};

std::ostream& operator<<( std::ostream& out, const IOperand& rhs );