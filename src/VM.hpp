#include "Operations/Operation.hpp"
#include "Parsing/Lexer.hpp"
#include "Parsing/Parser.hpp"

// Contains the entire VM environment and handles its execution
// Returns output and debug info, or throw a VMException in any invalid state
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

	OpOutput runLine( std::string& line );
	void checkExit() const;
};