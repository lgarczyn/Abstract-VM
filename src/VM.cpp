#include "VM.hpp"
#include "Exceptions/Exceptions.hpp"

VM::VM(): _lexer(), _parser(), _stack(), _exited() {}

VM::~VM() {}

void VM::run_line(std::string &line)
{
	auto operation_token = _lexer.readLine(line);
	if (operation_token)
	{
		if (_exited)
		{
			throw PrematureExitException();
		}
		auto operation = _parser.getOperation(*operation_token);
		if (operation.run(_stack))
		{
			_exited = true;
		}
		int unexpected_chars = operation_token->unexpected_chars;
		delete operation_token;
		if (unexpected_chars >= 0)
		{
			throw UnexpectedCharactersException(line, unexpected_chars);
		}
	}
}

void VM::check_exit() {
	if (_exited == false)
	{
		throw MissingExitException();
	}
}