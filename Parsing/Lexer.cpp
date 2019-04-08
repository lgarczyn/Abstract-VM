#include "Lexer.hpp"
#include "../Operations/Operation.hpp"
#include "../Operations/Operation.hpp"
#include <cstring>
#include <cstdio>

OperationToken *Lexer::readLine(std::string &line)
{
	char operator_name[30];
	char operand_data[30];
	char operand_type[30];
	bool read_value = true;
	bool read_operator = true;
	int read_chars;
	int read_tokens;

	// Reading "Operator Type(Value)" format
	read_tokens = sscanf(line.c_str(), "%30[a-z] %30[a-z0-9](%30[a-z.Ee+-])%n", operator_name, operand_type, operand_data, &read_chars);

	// If failed, attempt "Operator" format
	if (read_tokens != 3)
	{
		read_value = false;
		read_tokens = sscanf(line.c_str(), "%30[a-z]%n", operator_name, &read_chars);

		if (read_tokens != 1)
		{
			read_operator = false;
		}
	}

	// Check for remaining characters
	size_t i = read_chars;
	while (line[i] && line[i] != ';' && line[i] != '\n')
	{
		if (line[i] != ' ')
		{
			throw std::logic_error(
				std::string("Could not parse string:\n") +
				line +
				"\n Unexpected character: " +
				line[i]);
		}
	}
	// Skip empty lines
	if (read_operator == false)
		return NULL;

	// Build Token
	OperationToken *token = new OperationToken();

	token->operator_name = std::string(operator_name);
	token->has_value = read_value;

	if (read_value)
	{
		token->operand_type = std::string(operand_type);
		token->operand_data = std::string(operand_data);
	}
	return token;
}