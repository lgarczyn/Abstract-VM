#pragma once
#include <string>

struct OperationToken
{
	std::string operator_name;
	bool has_value;
	std::string operand_type;
	std::string operand_data;
};

class Lexer
{
	public:
	OperationToken *readLine(std::string &line);
	Lexer() {};
	~Lexer() {};
};