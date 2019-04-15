#pragma once
#include <string>

struct OperationToken
{
	OperationToken();
	OperationToken( const OperationToken& cpy );
	OperationToken& operator=( const OperationToken& rhs );
	~OperationToken();

	std::string operatorName;
	bool hasValue;
	std::string operandType;
	std::string operandData;
	int unexpectedChars;
};

// Transform a single instruction line into a token, with seperated content
class Lexer
{
  public:
	bool readLine( std::string& line, OperationToken* out );
};