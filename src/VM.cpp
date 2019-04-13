#include "VM.hpp"
#include "Exceptions/VMException.hpp"

VM::VM(): _lexer(), _parser(), _stack(), _exited() {}

VM::VM(const VM& cpy)
{
	*this = cpy;
}

VM &VM::operator=(const VM& rhs)
{
	this->_lexer = rhs._lexer;
	this->_parser = rhs._parser;
	this->_exited = rhs._exited;

	for (auto operand:rhs._stack)
	{
		this->_stack.push_back(operand->clone());
	}
	return *this;
}

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