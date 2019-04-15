#pragma once
#include "Lexer.hpp"
#include "Operands/OperandFactory.hpp"
#include "Operations/Operation.hpp"

class Parser : OperandFactory
{
  public:
	Operation getOperation( OperationToken token );
};