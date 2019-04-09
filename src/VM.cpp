
#include "VM.hpp"

VM::VM(): _lexer(), _parser(), _stack(), _exited() {}

VM::~VM() {}

void VM::run_line(std::string &line)
{
	auto operation_token = _lexer.readLine(line);
	if (operation_token)
	{
		if (_exited)
			throw std::logic_error("Operations attempted after exit");
		auto operation = _parser.getOperation(*operation_token);
		delete operation_token;
		if (operation.run(_stack))
		{
			_exited = true;
		}
	}
}

void VM::check_exit() {
	if (_exited == false)
		throw std::logic_error("No exit operator before EOF");
}