#pragma once
#include <exception>
#include <string>

struct VMException : std::exception
{
  public:
	VMException();
	VMException( std::string _msg );
	VMException( const VMException& rhs );
	VMException& operator=( const VMException& rhs );
	~VMException() noexcept override;

	const std::string& toString() const noexcept;
	virtual char const* what() const noexcept override;

  protected:
	std::string _msg;
};

struct CorruptOperandException : VMException
{
	CorruptOperandException();
};

struct NoOperandException : VMException
{
	NoOperandException( const std::string& name );
};

struct StackTooSmallException : VMException
{
	StackTooSmallException( const std::string& name );
};

struct OverflowException : VMException
{
	OverflowException( const std::string& op );
};

struct FailedAssertException : VMException
{
	FailedAssertException( const std::string& op );
};

struct DivideByZeroException : VMException
{
	DivideByZeroException();
};

struct ModuloByZeroException : VMException
{
	ModuloByZeroException();
};

struct ForbiddenPrintException : VMException
{
	ForbiddenPrintException( const std::string& type );
};

struct UnexpectedCharactersException : VMException
{
	UnexpectedCharactersException( const std::string& line, int pos );
};

struct UnknownOperationException : VMException
{
	UnknownOperationException( const std::string& operation );
};

struct MissingOperandException : VMException
{
	MissingOperandException( const std::string& operation );
};

struct UselessOperandException : VMException
{
	UselessOperandException( const std::string& operation );
};

struct UnknownOperandException : VMException
{
	UnknownOperandException( const std::string& operand );
};

struct LargeIntegerException : VMException
{
	LargeIntegerException( const std::string& value, const std::string& type );
};

struct LargeFloatingPointException : VMException
{
	LargeFloatingPointException( const std::string& value, const std::string& type );
};


struct PrematureExitException : VMException
{
	PrematureExitException();
};

struct MissingExitException : VMException
{
	MissingExitException();
};
