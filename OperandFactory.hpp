#pragma once
#include "IOperand.hpp"

class OperandFactory;

typedef const IOperand * (OperandFactory::*OperandConstructor)(std::string const & value ) const;

class OperandFactory {
private:
	static OperandConstructor constructors[OPERAND_TYPE_NUM];
public:
	IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;
};
