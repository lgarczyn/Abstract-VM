#include <exception>
#include <iostream>
#include <fstream>
#include <stack>
#include "Parsing/Lexer.hpp"
#include "Operations/Operation.hpp"
#include "Parsing/Parser.hpp"

void run(char *file)
{
	std::ifstream f;
	std::string line;
	f.open(file);

	Lexer lexer = Lexer();
	Parser parser = Parser();
	auto stack = Stack();
	size_t line_counter = 0;
	bool exited = false;

	while (std::getline(f, line))
	{
		line_counter++;
		std::cout << line << std::endl;
		auto operation_token = lexer.readLine(line);
		if (operation_token)
		{
			if (exited)
				throw std::logic_error("Operations attempted after exit");
			std::cout << operation_token->operator_name << " " << operation_token->has_value << " " << operation_token->operand_type << " " << operation_token->operand_data << std::endl;
			auto operation = parser.getOperation(*operation_token);
			delete operation_token;
			if (operation.run(stack))
			{
				exited = true;
			}
		}
	}
}

int main(int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
	{
		try
		{
			run(argv[i]);
		}
		catch (std::exception &e)
		{
			std::cerr << argv[0] << ": Error: " << e.what() << std::endl;
		}
	}
}