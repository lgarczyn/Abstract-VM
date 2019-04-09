#pragma once
#include "../Operations/OperandFactory.hpp"
#include "../Operations/Operation.hpp"
#include "Lexer.hpp"

class Parser
{
  private:
	OperandFactory _factory;

  public:
	Parser();
	Parser( const Parser& cpy );
	~Parser();
	Parser& operator=( const Parser& cpy );

	Operation getOperation( OperationToken token );
};