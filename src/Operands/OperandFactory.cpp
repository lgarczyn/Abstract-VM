#include "OperandFactory.hpp"
#include "Operand.hpp"
#include "Exceptions/VMException.hpp"

const OperandConstructor OperandFactory::constructors[OPERAND_TYPE_NUM] = {
	&OperandFactory::createInt8,
	&OperandFactory::createInt16,
	&OperandFactory::createInt32,
	&OperandFactory::createFloat,
	&OperandFactory::createDouble,
	&OperandFactory::createLongDouble,
};

IOperand const * OperandFactory::createOperand( eOperandType type, std::string const & value ) const {
	OperandConstructor cons = constructors[static_cast<int>(type)];
	return (this->*cons)(value);
}

IOperand const * OperandFactory::createInt8( std::string const & value ) const {
	return new Operand<safe_int8>(std::atoi(value.c_str()));
}

IOperand const * OperandFactory::createInt16( std::string const & value ) const {
	return new Operand<safe_int16>(std::atoi(value.c_str()));
}

IOperand const * OperandFactory::createInt32( std::string const & value ) const {
	return new Operand<safe_int32>(std::atoi(value.c_str()));
}

IOperand const * OperandFactory::createFloat( std::string const & value ) const {
	float f = std::strtof(value.c_str(), NULL);

	if (std::isfinite(f) == false)
		throw LargeFloatingPointException(value, "float");

	return new Operand<float>(f);
}

IOperand const * OperandFactory::createDouble( std::string const & value ) const {
	double f = std::strtod(value.c_str(), NULL);

	if (std::isfinite(f) == false)
		throw LargeFloatingPointException(value, "double");

	return new Operand<double>(f);
}


IOperand const * OperandFactory::createLongDouble( std::string const & value ) const {
	long double f = std::strtold(value.c_str(), NULL);

	if (std::isfinite(f) == false)
		throw LargeFloatingPointException(value, "double");

	return new Operand<double>(f);
}
