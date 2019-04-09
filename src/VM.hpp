#include <stack>
#include "Parsing/Lexer.hpp"
#include "Operations/Operation.hpp"
#include "Parsing/Parser.hpp"

class VM
{
  private:
	Lexer _lexer;
	Parser _parser;
	Stack _stack;
	bool _exited;

  public:
	VM();
	~VM();

	void run_line(std::string &line);

	void check_exit();
};