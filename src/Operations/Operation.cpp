#include "Operation.hpp"
#include "Exceptions/VMException.hpp"

const OperationInfo Operation::operations[OPERATION_TYPE_NUM] = {
	{e_op_push, "push", "", true, 0, &Operation::op_push},
	{e_op_pop, "pop", "", false, 1, &Operation::op_pop},
	{e_op_dup, "dup", "", false, 1, &Operation::op_dup},
	{e_op_dump, "dump", "", false, 0, &Operation::op_dump},
	{e_op_assert, "assert", "", true, 1, &Operation::op_assert},
	{e_op_add, "add", "+", false, 2, &Operation::op_add},
	{e_op_sub, "sub", "-", false, 2, &Operation::op_sub},
	{e_op_mul, "mul", "*", false, 2, &Operation::op_mul},
	{e_op_div, "div", "/", false, 2, &Operation::op_div},
	{e_op_mod, "mod", "%", false, 2, &Operation::op_mod},
	{e_op_print, "print", "", false, 1, &Operation::op_print},
	{e_op_exit, "exit", "", false, 0, &Operation::op_exit},
};

OperationInfo::OperationInfo() = default;
OperationInfo::OperationInfo(const OperationInfo&cpy) = default;
OperationInfo &OperationInfo::operator=(const OperationInfo&rhs) = default;
OperationInfo::~OperationInfo() = default;
OperationInfo::OperationInfo(
	eOperationType type,
	std::string name,
	std::string representation,
	bool takes_value,
	int required_operands,
	OperationMethod method
):	type(type),
	name(name),
	representation(representation),
	takes_value(takes_value),
	required_operands(required_operands),
	method(method){}

Operation::Operation() = default;
Operation::~Operation(void)
{
	delete _operand;
}

Operation &Operation::operator=(const Operation &cpy)
{
	this->_type = cpy._type;
	this->_operand = cpy._operand ? cpy._operand->clone() : NULL;
	return *this;
}

Operation::Operation(const Operation &cpy)
{
	*this = cpy;
}

Operation::Operation(eOperationType type, const IOperand *operand) : _type(type), _operand(operand) {}

bool Operation::run(Stack &stack)
{
	OperationInfo info = this->operations[this->_type];

	if (info.takes_value && this->_operand == NULL)
		throw MissingOperandException(info.name);

	if ((size_t)info.required_operands > stack.size())
		throw StackTooSmallException(info.name);

	try
	{
		(this->*(info.method))(stack);
	}
	catch (SafeIntException &e)
	{
		const IOperand *highest = stack.back();
		const IOperand *lowest = stack.at(stack.size() - 2);
		throw OverflowException(lowest->toString(), info.representation, highest->toString());
	}
	
	return this->_type == e_op_exit;
}

// Pushes the value at the top of the stack.
void Operation::op_push(Stack &stack)
{
	stack.push_back(_operand);
	_operand = NULL;
}

// Unstacks the value from the top of the stack.  If the stack is empty, theprogram execution must stop with an error.
void Operation::op_pop(Stack &stack)
{
	const IOperand *highest = stack.back();
	stack.pop_back();
	delete highest;
}

// Pushes the value at the top of the stack.
void Operation::op_dup(Stack &stack)
{
	const IOperand *highest = stack.back();
	stack.push_back(highest->clone());
	_operand = NULL;
}

// Displays each value of the stack, from the most recent one to the oldestone WITHOUT CHANGING the stack. Each value is separated from the next oneby a newline.
void Operation::op_dump(Stack &stack)
{
	for (auto it = stack.rbegin(); it != stack.rend(); it++)
	{
		std::cout << (*it)->getTypeName() << " " << **it << std::endl;
	}
}

// Asserts that the value at the top of the stack is equal to the one passedas parameter for this instruction. If it is not the case, the program execution muststop with an error. The valuevhas the same form that those passed as parametersto the instructionpush.
void Operation::op_assert(Stack &stack)
{
	const IOperand *highest = stack.back();
	if (*highest != *this->_operand)
	{
		throw FailedAssertException(this->_operand->toString(), highest->toString());
	}
}

// Unstacks the first two values on the stack, adds them together and stacks theresult. If the number of values on the stack is strictly inferior to 2, the programexecution must stop with an error.
void Operation::op_add(Stack &stack)
{
	const IOperand *highest = stack.back();
	const IOperand *lowest = stack.at(stack.size() - 2);

	auto res = *lowest + *highest;
	stack.pop_back();
	stack.pop_back();
	stack.push_back(res);
	delete highest;
	delete lowest;
}

// Unstacks the first two values on the stack, subtracts them, then stacks theresult. If the number of values on the stack is strictly inferior to 2, the programexecution must stop with an error.
void Operation::op_sub(Stack &stack)
{
	const IOperand *highest = stack.back();
	const IOperand *lowest = stack.at(stack.size() - 2);

	auto res = *lowest - *highest;
	stack.pop_back();
	stack.pop_back();
	stack.push_back(res);
	delete highest;
	delete lowest;
}

// Unstacks the first two values on the stack, multiplies them, then stacks theresult. If the number of values on the stack is strictly inferior to 2, the programexecution must stop with an error.4
void Operation::op_mul(Stack &stack)
{
	const IOperand *highest = stack.back();
	const IOperand *lowest = stack.at(stack.size() - 2);

	auto res = *lowest * *highest;
	stack.pop_back();
	stack.pop_back();
	stack.push_back(res);
	delete highest;
	delete lowest;
}

// Unstacks the first two values on the stack, divides them, then stacks the result.If the number of values on the stack is strictly inferior to 2, the program executionmust stop with an error. Moreover, if the divisor is equal to 0, the program executionmust stop with an error too. Chatting about floating point values is relevant a thispoint. If you don’t understand why, some will understand. The linked question isan open one, there’s no definitive answer.
void Operation::op_div(Stack &stack)
{
	const IOperand *highest = stack.back();
	const IOperand *lowest = stack.at(stack.size() - 2);

	if (highest->isZero())
		throw DivideByZeroException();
	auto res = *lowest / *highest;
	stack.pop_back();
	stack.pop_back();
	stack.push_back(res);
	delete highest;
	delete lowest;
}

// Unstacks the first two values on the stack, calculates the modulus, thenstacks the result. If the number of values on the stack is strictly inferior to 2, theprogram execution must stop with an error. Moreover, if the divisor is equal to 0,the program execution must stop with an error too. Same note as above about fpvalues.
void Operation::op_mod(Stack &stack)
{
	const IOperand *highest = stack.back();
	const IOperand *lowest = stack.at(stack.size() - 2);

	if (highest->isZero())
		throw ModuloByZeroException();
	auto res = *lowest % *highest;
	stack.pop_back();
	stack.pop_back();
	stack.push_back(res);
	delete highest;
	delete lowest;
}

// Asserts that the value at the top of the stack is an 8-bit integer. (If not,see the instructionassert), then interprets it as an ASCII value and displays thecorresponding character on the standard output.
void Operation::op_print(Stack &stack)
{
	const IOperand *highest = stack.back();

	if (highest->getType() != e_ty_i8)
		throw ForbiddenPrintException(highest->getTypeName());
	std::cout << static_cast<int8_t>(highest->asI8()) << std::endl;
}

// Terminate the execution of the current program. If this instruction does notappears while all others instruction has been processed, the execution must stop with an error
void Operation::op_exit(Stack &){}
