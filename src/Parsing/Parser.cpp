#include "Parser.hpp"

#include "Exceptions/VMException.hpp"

Operation Parser::getOperation( OperationToken token )
{
	eOperationType operationType;
	eOperandType operandType;

	int i;
	for ( i = 0; i < OPERATION_TYPE_NUM; i++ )
	{
		if ( token.operatorName == Operation::operations[ i ].name )
		{
			operationType = Operation::operations[ i ].type;
			break;
		}
	}
	if ( i == OPERATION_TYPE_NUM )
		throw UnknownOperationException( token.operatorName );

	bool takesValue = Operation::operations[ operationType ].takesValue;

	if ( takesValue && token.hasValue == false )
		throw MissingOperandException( token.operatorName );

	if ( takesValue == false && token.hasValue )
		throw UselessOperandException( token.operatorName );

	const IOperand* operand = NULL;

	if ( takesValue )
	{
		for ( i = 0; i < OPERAND_TYPE_NUM; i++ )
		{
			if ( token.operandType == IOperand::operands[ i ].name )
			{
				operandType = IOperand::operands[ i ].type;
				break;
			}
		}
		if ( i == OPERAND_TYPE_NUM )
			throw UnknownOperandException( token.operandType );
		operand = createOperand( operandType, token.operandData );
	}
	return Operation( operationType, operand );
}
