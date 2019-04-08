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
	bool has_value = true;
	bool has_operator = true;
	int read_chars = 0;
	int read_tokens;

	// Reading "Operator Type(Value)" format
	read_tokens = sscanf(line.c_str(), "%30[a-z] %30[a-z0-9](%30[0-9.Ee+-])%n", operator_name, operand_type, operand_data, &read_chars);

	// If failed, attempt "Operator" format
	if (read_tokens != 3)
	{
		has_value = false;
		read_tokens = sscanf(line.c_str(), "%30[a-z]%n", operator_name, &read_chars);
		
		if (read_tokens != 1)
		{
			has_operator = false;
		}
	}
	std::cout << "read_chars: " << read_chars << std::endl;

	// Check for remaining characters
	size_t i = read_chars;
	while (line[i] && line[i] != ';')
	{
		if (line[i] != ' ')
		{
			throw std::logic_error(
				std::string("Could not parse string:\n") +
				line +
				"\n Unexpected character: " +
				line[i]);
		}
		i++;
	}
	// Skip empty lines
	if (has_operator == false)
		return NULL;

	// Build Token
	OperationToken *token = new OperationToken();

	token->operator_name = std::string(operator_name);
	token->has_value = has_value;

	if (has_value)
	{
		token->operand_type = std::string(operand_type);
		token->operand_data = std::string(operand_data);
	}
	return token;
}