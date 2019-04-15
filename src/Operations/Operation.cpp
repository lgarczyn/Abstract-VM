#include "Operation.hpp"

#include "Exceptions/VMException.hpp"

#include <sstream>

const OperationInfo Operation::operations[ OPERATION_TYPE_NUM ] = {
	{ OpPush, "push", "push", true, 0, &Operation::opPush },
	{ OpPop, "pop", "pop", false, 1, &Operation::opPop },
	{ OpDup, "dup", "dup", false, 1, &Operation::opDup },
	{ OpDump, "dump", "dump", false, 0, &Operation::opDump },
	{ OpAssert, "assert", "==", true, 1, &Operation::opAssert },
	{ OpAdd, "add", "+", false, 2, &Operation::opAdd },
	{ OpSub, "sub", "-", false, 2, &Operation::opSub },
	{ OpMul, "mul", "*", false, 2, &Operation::opMul },
	{ OpDiv, "div", "/", false, 2, &Operation::opDiv },
	{ OpMod, "mod", "%", false, 2, &Operation::opMod },
	{ OpPrint, "print", "print", false, 1, &Operation::opPrint },
	{ OpExit, "exit", "exit", false, 0, &Operation::opExit },
};

OperationInfo::OperationInfo() = default;
OperationInfo::OperationInfo( const OperationInfo& cpy ) = default;
OperationInfo& OperationInfo::operator=( const OperationInfo& rhs ) = default;
OperationInfo::~OperationInfo() = default;
OperationInfo::OperationInfo( eOperationType type, std::string name, std::string representation,
	bool takesValue, int requiredOperands, OperationMethod method )
	: type( type )
	, name( name )
	, representation( representation )
	, takesValue( takesValue )
	, requiredOperands( requiredOperands )
	, method( method )
{
}

Operation::Operation()
	: Operation( OpAdd, NULL )
{
}

Operation::Operation( eOperationType type, const IOperand* operand )
	: _type( type )
	, _operand( operand )
	, _operation()
	, _result()
	, _output()
	, _ran()
{
}

Operation::~Operation( void ) { delete _operand; }

Operation& Operation::operator=( const Operation& cpy )
{
	this->_type = cpy._type;
	this->_operand = cpy._operand ? cpy._operand->clone() : NULL;
	return *this;
}

Operation::Operation( const Operation& cpy ) { *this = cpy; }

OperationInfo Operation::checkParameters( const Stack& stack ) const
{
	OperationInfo info = this->operations[ this->_type ];

	if ( info.takesValue && this->_operand == NULL )
		throw MissingOperandException( info.name );

	if ( (size_t)info.requiredOperands > stack.size() )
		throw StackTooSmallException( info.name );

	return info;
}

std::string Operation::getOperationString( const Stack& stack, const OperationInfo& info ) const
{
	if ( info.requiredOperands + info.takesValue == 2 )
	{
		const IOperand* highest = stack.back();
		const IOperand* lowest = this->_operand;
		if ( lowest == NULL )
			lowest = stack.at( stack.size() - 2 );

		return lowest->toString() + " " + info.representation + " " + highest->toString();
	}
	if ( info.requiredOperands == 1 || info.takesValue )
	{
		const IOperand* highest = this->_operand;
		if ( highest == NULL )
			highest = stack.back();

		return info.representation + " " + highest->toString();
	}
	return info.representation;
}

OpOutput Operation::run( Stack& stack )
{
	if ( this->_ran )
		throw std::logic_error( "Cannot run operation twice" );
	this->_ran = true;

	OperationInfo info = checkParameters( stack );
	this->_operation = getOperationString( stack, info );

	try
	{
		( this->*( info.method ) )( stack );
	}
	catch ( SafeIntException& e )
	{
		throw OverflowException( this->_operation );
	}
	if ( this->_result.size() )
		_operation += " = " + std::move( this->_result );

	return std::make_pair( std::move( this->_output ), std::move( this->_operation ) );
}

// Pushes the value at the top of the stack.
void Operation::opPush( Stack& stack )
{
	stack.push_back( _operand );
	_operand = NULL;
}

// Unstacks the value from the top of the stack.  If the stack is empty, theprogram execution must
// stop with an error.
void Operation::opPop( Stack& stack )
{
	const IOperand* highest = stack.back();
	stack.pop_back();
	delete highest;
}

// Pushes the value at the top of the stack.
void Operation::opDup( Stack& stack )
{
	const IOperand* highest = stack.back();
	stack.push_back( highest->clone() );
	_operand = NULL;
}

// Displays each value of the stack, from the most recent one to the oldestone WITHOUT CHANGING the
// stack. Each value is separated from the next oneby a newline.
void Operation::opDump( Stack& stack )
{
	std::stringstream ss;
	ss << "   +---" << std::endl;
	for ( auto it = stack.rbegin(); it != stack.rend(); it++ )
	{
		ss << "   | " << ( *it )->getTypeName() << ": " << **it << std::endl;
	}
	this->_output = ss.str();
}

// Asserts that the value at the top of the stack is equal to the one passedas parameter for this
// instruction. If it is not the case, the program execution muststop with an error. The valuevhas
// the same form that those passed as parametersto the instructionpush.
void Operation::opAssert( Stack& stack )
{
	const IOperand* highest = stack.back();
	if ( *highest != *this->_operand )
	{
		throw FailedAssertException( this->_operation );
	}
}

// Unstacks the first two values on the stack, adds them together and stacks theresult. If the
// number of values on the stack is strictly inferior to 2, the programexecution must stop with an
// error.
void Operation::opAdd( Stack& stack )
{
	const IOperand* highest = stack.back();
	const IOperand* lowest = stack.at( stack.size() - 2 );

	auto res = *lowest + *highest;
	stack.pop_back();
	stack.pop_back();
	stack.push_back( res );
	delete highest;
	delete lowest;
	this->_result = res->toString();
}

// Unstacks the first two values on the stack, subtracts them, then stacks theresult. If the number
// of values on the stack is strictly inferior to 2, the programexecution must stop with an error.
void Operation::opSub( Stack& stack )
{
	const IOperand* highest = stack.back();
	const IOperand* lowest = stack.at( stack.size() - 2 );

	auto res = *lowest - *highest;
	stack.pop_back();
	stack.pop_back();
	stack.push_back( res );
	delete highest;
	delete lowest;
	this->_result = res->toString();
}

// Unstacks the first two values on the stack, multiplies them, then stacks theresult. If the number
// of values on the stack is strictly inferior to 2, the programexecution must stop with an error.4
void Operation::opMul( Stack& stack )
{
	const IOperand* highest = stack.back();
	const IOperand* lowest = stack.at( stack.size() - 2 );

	auto res = *lowest * *highest;
	stack.pop_back();
	stack.pop_back();
	stack.push_back( res );
	delete highest;
	delete lowest;
	this->_result = res->toString();
}

// Unstacks the first two values on the stack, divides them, then stacks the result.If the number of
// values on the stack is strictly inferior to 2, the program executionmust stop with an error.
// Moreover, if the divisor is equal to 0, the program executionmust stop with an error too.
// Chatting about floating point values is relevant a thispoint. If you don’t understand why, some
// will understand. The linked question isan open one, there’s no definitive answer.
void Operation::opDiv( Stack& stack )
{
	const IOperand* highest = stack.back();
	const IOperand* lowest = stack.at( stack.size() - 2 );

	if ( highest->isZero() )
		throw DivideByZeroException();
	auto res = *lowest / *highest;
	stack.pop_back();
	stack.pop_back();
	stack.push_back( res );
	delete highest;
	delete lowest;
	this->_result = res->toString();
}

// Unstacks the first two values on the stack, calculates the modulus, thenstacks the result. If the
// number of values on the stack is strictly inferior to 2, theprogram execution must stop with an
// error. Moreover, if the divisor is equal to 0,the program execution must stop with an error too.
// Same note as above about fpvalues.
void Operation::opMod( Stack& stack )
{
	const IOperand* highest = stack.back();
	const IOperand* lowest = stack.at( stack.size() - 2 );

	if ( highest->isZero() )
		throw ModuloByZeroException();
	auto res = *lowest % *highest;
	stack.pop_back();
	stack.pop_back();
	stack.push_back( res );
	delete highest;
	delete lowest;
	this->_result = res->toString();
}

// Asserts that the value at the top of the stack is an 8-bit integer. (If not,see the
// instructionassert), then interprets it as an ASCII value and displays thecorresponding character
// on the standard output.
void Operation::opPrint( Stack& stack )
{
	const IOperand* highest = stack.back();

	if ( highest->getType() != TypeI8 )
		throw ForbiddenPrintException( highest->getTypeName() );

	this->_output = "   | ";
	this->_output.push_back( highest->asI8() );
	this->_output.push_back( '\n' );
}

// Terminate the execution of the current program. If this instruction does notappears while all
// others instruction has been processed, the execution must stop with an error
void Operation::opExit( Stack& ) {}

bool Operation::isExit() const { return _type == OpExit; }