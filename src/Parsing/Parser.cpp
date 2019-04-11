#include "Parser.hpp"
#include "Exceptions/Exceptions.hpp"

Operation Parser::getOperation(OperationToken token)
{
	eOperationType operation_type;
	eOperandType operand_type;

	int i;
	for (i = 0; i < OPERATION_TYPE_NUM; i++)
	{
		if (token.operator_name.compare(Operation::operations[i].name) == 0)
		{
			operation_type = Operation::operations[i].type;
			break;
		}
	}
	if (i == OPERATION_TYPE_NUM)
		throw UnknownOperationException(token.operator_name);

	bool takes_value = Operation::operations[operation_type].takes_value;

	if (takes_value && token.has_value == false)
		throw MissingOperandException(token.operator_name);

	if (takes_value == false && token.has_value)
		throw UselessOperandException(token.operator_name);

	const IOperand *operand = NULL;

	if (takes_value)
	{
		for (i = 0; i < OPERAND_TYPE_NUM; i++)
		{
			if (token.operand_type.compare(IOperand::operands[i].name) == 0)
			{
				operand_type = IOperand::operands[i].type;
				break;
			}
		}
		if (i == OPERAND_TYPE_NUM)
			throw UnknownOperandException(token.operand_type);

		try
		{
			operand = _factory.createOperand(operand_type, token.operand_data);
		}
		catch(SafeIntException&)
		{
			throw LargeIntegerException(token.operand_data, token.operand_type);
		}
	}

	return Operation(operation_type, operand);
}
