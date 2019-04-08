#pragma once
#include "../Operations/Operation.hpp"
#include "Lexer.hpp"

class Parser
{
  public:
	Parser();
	~Parser();
	Operation getOperation(OperationToken token);
};