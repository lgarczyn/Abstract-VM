#include "VM.hpp"

#include "Exceptions/VMException.hpp"

VM::VM()
	: _lexer()
	, _parser()
	, _stack()
	, _exited()
{
}

VM::VM( const VM& cpy ) { *this = cpy; }

VM& VM::operator=( const VM& rhs )
{
	this->_lexer = rhs._lexer;
	this->_parser = rhs._parser;
	this->_exited = rhs._exited;

	for ( auto operand : rhs._stack )
	{
		this->_stack.push_back( operand->clone() );
	}
	return *this;
}

VM::~VM()
{
	for ( auto ptr : this->_stack )
	{
		delete ptr;
	}
}

OpOutput VM::runLine( std::string& line )
{
	OperationToken token;
	OpOutput output;

	bool success = _lexer.readLine( line, &token );

	if ( success )
	{
		auto operation = _parser.getOperation( token );

		output = operation.run( _stack );

		if ( _exited )
		{
			throw PrematureExitException();
		}
		_exited |= operation.isExit();
		if ( token.unexpectedChars >= 0 )
		{
			throw UnexpectedCharactersException( line, token.unexpectedChars );
		}
	}
	return output;
}

void VM::checkExit() const
{
	if ( _exited == false )
	{
		throw MissingExitException();
	}
}