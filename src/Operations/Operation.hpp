#pragma once
#include "Operands/IOperand.hpp"

#include <string>
#include <vector>

enum eOperationType
{
	e_op_push = 0,
	e_op_pop,
	e_op_dup,
	e_op_dump,
	e_op_assert,
	e_op_add,
	e_op_sub,
	e_op_mul,
	e_op_div,
	e_op_mod,
	e_op_print,
	e_op_exit,
	OPERATION_TYPE_NUM,
};

class Operation;

typedef std::vector<const IOperand*> Stack;

typedef void ( Operation::*OperationMethod )( Stack& stack );

typedef std::pair<std::string, std::string> OpOutput;

struct OperationInfo
{
	OperationInfo();
	OperationInfo( eOperationType type, std::string name, std::string representation,
		bool takes_value, int required_operands, OperationMethod method );
	OperationInfo( const OperationInfo& cpy );
	OperationInfo& operator=( const OperationInfo& rhs );
	~OperationInfo();

	eOperationType type;
	std::string name;
	std::string representation;
	bool takes_value;
	int required_operands;
	OperationMethod method;
};

class Operation
{
  private:
	eOperationType _type;
	const IOperand* _operand;

	std::string _operation;
	std::string _result;
	std::string _output;
	bool _ran;

  public:
	static const OperationInfo operations[ OPERATION_TYPE_NUM ];

	Operation();
	Operation( eOperationType type, const IOperand* operand );
	Operation( const Operation& cpy );
	~Operation( void );
	Operation& operator=( const Operation& cpy );
	bool isExit() const;

	OpOutput run( Stack& stack );
	std::string toString() const;

  private:
	OperationInfo checkParameters( const Stack& stack ) const;
	std::string getOperationString( const Stack& stack, const OperationInfo& info ) const;

	// Pushes the value at the top of the stack.
	void op_push( Stack& stack );
	// Unstacks the value from the top of the stack.  If the stack is empty, theprogram execution
	// must stop with an error.
	void op_pop( Stack& stack );
	// Duplicates the highest element of the stack, and pushes it to the stack
	void op_dup( Stack& stack );
	// Displays each value of the stack, from the most recent one to the oldestone WITHOUT CHANGING
	// the stack. Each value is separated from the next oneby a newline.
	void op_dump( Stack& stack );

	// Asserts that the value at the top of the stack is equal to the one passedas parameter for
	// this instruction. If it is not the case, the program execution muststop with an error. The
	// valuevhas the same form that those passed as parametersto the instructionpush.
	void op_assert( Stack& stack );
	// Unstacks the first two values on the stack, adds them together and stacks theresult. If the
	// number of values on the stack is strictly inferior to 2, the programexecution must stop with
	// an error.
	void op_add( Stack& stack );
	// Unstacks the first two values on the stack, subtracts them, then stacks theresult. If the
	// number of values on the stack is strictly inferior to 2, the programexecution must stop with
	// an error.
	void op_sub( Stack& stack );
	// Unstacks the first two values on the stack, multiplies them, then stacks theresult. If the
	// number of values on the stack is strictly inferior to 2, the programexecution must stop with
	// an error.4
	void op_mul( Stack& stack );
	// Unstacks the first two values on the stack, divides them, then stacks the result.If the
	// number of values on the stack is strictly inferior to 2, the program executionmust stop with
	// an error. Moreover, if the divisor is equal to 0, the program executionmust stop with an
	// error too. Chatting about floating point values is relevant a thispoint. If you don’t
	// understand why, some will understand. The linked question isan open one, there’s no
	// definitive answer.
	void op_div( Stack& stack );
	// Unstacks the first two values on the stack, calculates the modulus, thenstacks the result. If
	// the number of values on the stack is strictly inferior to 2, theprogram execution must stop
	// with an error. Moreover, if the divisor is equal to 0,the program execution must stop with an
	// error too. Same note as above about fpvalues.
	void op_mod( Stack& stack );
	// Asserts that the value at the top of the stack is an 8-bit integer. (If not,see the
	// instructionassert), then interprets it as an ASCII value and displays thecorresponding
	// character on the standard output.
	void op_print( Stack& stack );
	// Terminate the execution of the current program. If this instruction does notappears while all
	// others instruction has been processed, the execution must stop with an error
	void op_exit( Stack& stack );
};