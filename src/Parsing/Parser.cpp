#include "Parser.hpp"

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
		throw std::logic_error(std::string("Unknown operation: ") + token.operator_name);

	bool takes_value = Operation::operations[operation_type].takes_value;

	if (takes_value && token.has_value == false)
		throw std::logic_error(std::string("No value provided for operation: ") + token.operator_name);

	if (takes_value == false && token.has_value)
		throw std::logic_error(std::string("Useless value provided for operation: ") + token.operator_name);

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
			throw std::logic_error(std::string("Unknown operand: ") + token.operand_type);
		
		operand = _factory.createOperand(operand_type, token.operand_data);
	}

	return Operation(operation_type, operand);
}
