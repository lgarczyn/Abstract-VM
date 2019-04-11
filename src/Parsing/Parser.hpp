#pragma once
#include "Operations/Operation.hpp"
#include "Operands/OperandFactory.hpp"
#include "Lexer.hpp"

class Parser:OperandFactory
{
  public:
	Operation getOperation(OperationToken token);
};