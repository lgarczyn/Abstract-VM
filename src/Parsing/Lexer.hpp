#pragma once
#include <string>

class OperationToken
{
  public:
	OperationToken();
	OperationToken( const OperationToken& cpy );
	~OperationToken();
	OperationToken& operator=( const OperationToken& cpy );

	std::string operator_name;
	bool has_value;
	std::string operand_type;
	std::string operand_data;
};

class Lexer
{
  public:
	OperationToken* readLine( std::string& line );
};