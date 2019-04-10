#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include "IOperand.hpp"

enum eOperationType
{
	e_op_push = 0,
	e_op_pop,
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

typedef std::vector<const IOperand *> Stack;

typedef void (Operation::*OperationMethod)(Stack &stack, const IOperand *, const IOperand *);

struct OperationInfo
{
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
	const IOperand *_operand;

  public:
	static const OperationInfo operations[OPERATION_TYPE_NUM];

	Operation() : _type(), _operand() {}
	Operation(eOperationType type, const IOperand *operand) : _type(type), _operand(operand) {}
	Operation(const Operation &cpy) : _type(cpy._type), _operand(cpy._operand) {}
	~Operation(void) {}
	Operation &operator=(Operation &cpy)
	{
		this->_type = cpy._type;
		this->_operand = cpy._operand;
		return *this;
	}

	bool run(Stack &stack);
	// Pushes the valuevat the top of the stack.
	void op_push(Stack &stack, const IOperand *, const IOperand *);
	// Unstacks the value from the top of the stack.  If the stack is empty, theprogram execution must stop with an error.
	void op_pop(Stack &stack, const IOperand *, const IOperand *);
	// Displays each value of the stack, from the most recent one to the oldestone WITHOUT CHANGING the stack. Each value is separated from the next oneby a newline.
	void op_dump(Stack &stack, const IOperand *, const IOperand *);

	// Asserts that the value at the top of the stack is equal to the one passedas parameter for this instruction. If it is not the case, the program execution muststop with an error. The valuevhas the same form that those passed as parametersto the instructionpush.
	void op_assert(Stack &stack, const IOperand *, const IOperand *);
	// Unstacks the first two values on the stack, adds them together and stacks theresult. If the number of values on the stack is strictly inferior to 2, the programexecution must stop with an error.
	void op_add(Stack &stack, const IOperand *, const IOperand *);
	// Unstacks the first two values on the stack, subtracts them, then stacks theresult. If the number of values on the stack is strictly inferior to 2, the programexecution must stop with an error.
	void op_sub(Stack &stack, const IOperand *, const IOperand *);
	// Unstacks the first two values on the stack, multiplies them, then stacks theresult. If the number of values on the stack is strictly inferior to 2, the programexecution must stop with an error.4
	void op_mul(Stack &stack, const IOperand *, const IOperand *);
	// Unstacks the first two values on the stack, divides them, then stacks the result.If the number of values on the stack is strictly inferior to 2, the program executionmust stop with an error. Moreover, if the divisor is equal to 0, the program executionmust stop with an error too. Chatting about floating point values is relevant a thispoint. If you don’t understand why, some will understand. The linked question isan open one, there’s no definitive answer.
	void op_div(Stack &stack, const IOperand *, const IOperand *);
	// Unstacks the first two values on the stack, calculates the modulus, thenstacks the result. If the number of values on the stack is strictly inferior to 2, theprogram execution must stop with an error. Moreover, if the divisor is equal to 0,the program execution must stop with an error too. Same note as above about fpvalues.
	void op_mod(Stack &stack, const IOperand *, const IOperand *);
	// Asserts that the value at the top of the stack is an 8-bit integer. (If not,see the instructionassert), then interprets it as an ASCII value and displays thecorresponding character on the standard output.
	void op_print(Stack &stack, const IOperand *, const IOperand *);
	// Terminate the execution of the current program. If this instruction does notappears while all others instruction has been processed, the execution must stop with an error
	void op_exit(Stack &stack, const IOperand *, const IOperand *);
};
