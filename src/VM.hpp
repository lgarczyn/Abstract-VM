#include "Operations/Operation.hpp"
#include "Parsing/Lexer.hpp"
#include "Parsing/Parser.hpp"

#include <stack>

class VM
{
  private:
	Lexer _lexer;
	Parser _parser;
	Stack _stack;
	bool _exited;

  public:
	VM();
	VM( const VM& cpy );
	~VM();
	VM& operator=( const VM& cpy );

	void run_line( std::string& line );

	void check_exit();
};