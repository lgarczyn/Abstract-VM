#include "OperandFactory.hpp"
#include "Operand.hpp"

const OperandConstructor OperandFactory::constructors[OPERAND_TYPE_NUM] = {
	&OperandFactory::createInt8,
	&OperandFactory::createInt16,
	&OperandFactory::createInt32,
	&OperandFactory::createFloat,
	&OperandFactory::createDouble,
};

IOperand const * OperandFactory::createOperand( eOperandType type, std::string const & value ) const {
	OperandConstructor cons = constructors[static_cast<int>(type)];
	return (this->*cons)(value);
}

IOperand const * OperandFactory::createInt8( std::string const & value ) const {
	return new Operand<int8_t>(std::atoi(value.c_str()));
}

IOperand const * OperandFactory::createInt16( std::string const & value ) const {
	return new Operand<int16_t>(std::atoi(value.c_str()));
}

IOperand const * OperandFactory::createInt32( std::string const & value ) const {
	return new Operand<int32_t>(std::atoi(value.c_str()));
}

IOperand const * OperandFactory::createFloat( std::string const & value ) const {
	float f = std::strtof(value.c_str(), NULL);
	
	if (std::isfinite(f) == false)
		throw std::logic_error("Value is not finite: " + std::to_string(f));
		
	return new Operand<float>(f);
}

IOperand const * OperandFactory::createDouble( std::string const & value ) const {
	float f = std::atof(value.c_str());
	
	if (std::isfinite(f) == false)
		throw std::logic_error("Value is not finite: " + std::to_string(f));
		
	return new Operand<double>(f);
}
