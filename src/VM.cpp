#include "VM.hpp"
#include "Exceptions/Exceptions.hpp"

VM::VM(): _lexer(), _parser(), _stack(), _exited() {}

VM::~VM() {
	for (auto ptr:this->_stack) {
		delete ptr;
	}
}

void VM::run_line(std::string &line)
{
	OperationToken token;
	
	bool success = _lexer.readLine(line, &token);

	if (success)
	{
		if (_exited)
		{
			throw PrematureExitException();
		}
		auto operation = _parser.getOperation(token);
		if (operation.run(_stack))
		{
			_exited = true;
		}
		if (token.unexpected_chars >= 0)
		{
			throw UnexpectedCharactersException(line, token.unexpected_chars);
		}
	}
}

void VM::check_exit() {
	if (_exited == false)
	{
		throw MissingExitException();
	}
}