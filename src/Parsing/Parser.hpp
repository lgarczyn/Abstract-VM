#pragma once
#include "Lexer.hpp"
#include "Operands/OperandFactory.hpp"
#include "Operations/Operation.hpp"

// Transform operation and operand string into actual instruction codes and values
// if possible
class Parser : OperandFactory
{
  public:
	Operation getOperation( OperationToken token );
};