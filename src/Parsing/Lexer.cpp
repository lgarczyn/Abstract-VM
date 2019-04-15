#include "Lexer.hpp"

#include "Exceptions/VMException.hpp"
#include "Operations/Operation.hpp"

#include <cstdio>
#include <cstring>

OperationToken::OperationToken()
	: operatorName()
	, hasValue()
	, operandType()
	, operandData()
	, unexpectedChars()
{
}

OperationToken::OperationToken( const OperationToken& cpy ) = default;
OperationToken& OperationToken::operator=( const OperationToken& rhs ) = default;
OperationToken::~OperationToken() = default;

bool Lexer::readLine( std::string& line, OperationToken& token )
{
	char operatorName[ 30 ];
	char operandData[ 30 ];
	char operandType[ 30 ];
	bool hasValue = true;
	bool hasOperator = true;
	int readChars = 0;
	int readTokens;

	// Reading "Operator Type(Value)" format
	readTokens = sscanf( line.c_str(), "%30[a-z] %30[a-z0-9](%30[0-9.Ee+-])%n", operatorName,
		operandType, operandData, &readChars );

	// If failed, attempt "Operator" format
	if ( readTokens != 3 )
	{
		hasValue = false;
		readTokens = sscanf( line.c_str(), "%30[a-z]%n", operatorName, &readChars );

		if ( readTokens != 1 )
		{
			hasOperator = false;
		}
	}
	// Skip empty lines
	if ( hasOperator == false )
		return false;

	// Fill Token

	// Check for remaining characters
	token.unexpectedChars = -1;
	size_t i = readChars;
	while ( line[ i ] && line[ i ] != ';' )
	{
		if ( line[ i ] != ' ' )
		{
			token.unexpectedChars = i;
			break;
		}
		i++;
	}

	token.operatorName = std::string( operatorName );
	token.hasValue = hasValue;

	if ( hasValue )
	{
		token.operandType = std::string( operandType );
		token.operandData = std::string( operandData );
	}
	return true;
}