#pragma once
#include "Operations/Operation.hpp"
#include "Operations/OperandFactory.hpp"
#include "Lexer.hpp"

class Parser
{
  private:
	OperandFactory _factory;

  public:
	Parser():_factory() {}
	~Parser() {}
	Operation getOperation(OperationToken token);
};