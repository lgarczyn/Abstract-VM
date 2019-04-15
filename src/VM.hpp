#include "Operations/Operation.hpp"
#include "Parsing/Lexer.hpp"
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
	VM( const VM& cpy );
	VM& operator=( const VM& rhs );
	~VM();

	OpOutput run_line( std::string& line );
	void checkExit() const;
};