#pragma once
#include "Operations/Operation.hpp"
#include "Operations/OperandFactory.hpp"
#include "Lexer.hpp"

class Parser:OperandFactory
{
  public:
	Operation getOperation(OperationToken token);
};