#include "Exceptions.hpp"


VMException::VMException():std::exception(){};
VMException::VMException(std::string _msg):_msg(_msg){};
VMException::VMException(const VMException &rhs):_msg(rhs._msg) {}
VMException &VMException::operator=(const VMException &rhs)
{
	this->_msg = rhs._msg;
	return *this;
}
VMException::~VMException() noexcept {}

const std::string& VMException::toString() const noexcept
{
	return this->_msg;
}
char const * VMException::what() const noexcept
{
	return this->_msg.c_str();
}

CorruptOperandException::CorruptOperandException(): VMException() {
	this->_msg = "Corrupt operand id";
}

NoOperandException::NoOperandException(const std::string & name): VMException() {
	this->_msg = "No operand was passed to operation: " + name;
}

StackTooSmallException::StackTooSmallException(const std::string & name): VMException() {
	this->_msg = "Stack too small on operation: " + name;
}

OverflowException::OverflowException(const std::string & lhs, const std::string & op, const std::string & rhs): VMException() {
	this->_msg = "Overflow in " + lhs + " " + op + " " + rhs;
}

FailedAssertException::FailedAssertException(const std::string & lhs, const std::string & rhs): VMException() {
	this->_msg = "Failed assert: " + lhs + " != " + rhs;
}

DivideByZeroException::DivideByZeroException(): VMException() {
	this->_msg = "Division by 0";
}

ModuloByZeroException::ModuloByZeroException(): VMException() {
	this->_msg = "Modulo by 0";
}

ForbiddenPrintException::ForbiddenPrintException(const std::string & type): VMException() {
	this->_msg = "Print on type " + type;
}

UnexpectedCharactersException::UnexpectedCharactersException(const std::string & line, int pos): VMException() {
	this->_msg = "Could not parse: \"" + line.substr(0, pos) + "\e[4m" + line.substr(pos) + "\e[0m\"";
}

UnknownOperationException::UnknownOperationException(const std::string & operation): VMException() {
	this->_msg = "Unknown operation: " + operation;
}

MissingOperandException::MissingOperandException(const std::string & operation): VMException() {
	this->_msg = "No value provided for operation: " + operation;
}

UselessOperandException::UselessOperandException(const std::string & operation): VMException() {
	this->_msg = "Useless value provided for operation: " + operation;
}

UnknownOperandException::UnknownOperandException(const std::string & operand): VMException() {
	this->_msg = "Unknown operand: " + operand;
}

LargeIntegerException::LargeIntegerException(const std::string & value, const std::string & type): VMException() {
	this->_msg = "Value \"" + value + "\" is too big for an " + type;
}

LargeFloatingPointException::LargeFloatingPointException(const std::string & value, const std::string & type): VMException() {
	this->_msg = "Value \"" + value + "\" is too big for a finite " + type;
}

PrematureExitException::PrematureExitException(): VMException() {
	this->_msg = "Operations attempted after exit";
}

MissingExitException::MissingExitException(): VMException() {
	this->_msg = "No exit operator before EOF";
}
