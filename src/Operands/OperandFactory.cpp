#include "OperandFactory.hpp"

#include "Exceptions/VMException.hpp"
#include "Operand.hpp"

#include <fstream>

const OperandConstructor OperandFactory::constructors[ OPERAND_TYPE_NUM ] = {
	&OperandFactory::createInt8,
	&OperandFactory::createInt16,
	&OperandFactory::createInt32,
	&OperandFactory::createFloat,
	&OperandFactory::createDouble,
	&OperandFactory::createLongDouble,
};


template <typename T> T create( std::string const& value, std::string const& type )
{
	T out = 0;
	auto ss = std::stringstream( value );

	ss >> out;

	if ( std::isfinite( out ) == false )
	{
		throw LargeFloatingPointException( value, type );
	}
	if ( ss.fail() )
	{
		throw LargeIntegerException( value, type );
	}
	if ( ss.eof() != true )
	{
		throw UnexpectedCharactersException( value, ss.tellg() );
	}
	return out;
}

IOperand const* OperandFactory::createOperand( eOperandType type, std::string const& value ) const
{
	OperandConstructor cons = constructors[ static_cast<int>( type ) ];
	return ( this->*cons )( value );
}

IOperand const* OperandFactory::createInt8( std::string const& value ) const
{
	// Getting character as int16 to avoid reading one ASCII value
	int16_t parsed = create<int16_t>( value, "Int8" );
	int8_t out;
	if ( SafeCast( parsed, out ) )
	{
		return new Operand<safe_int8>( safe_int8( out ) );
	}
	throw LargeIntegerException( value, "Int8" );
}

IOperand const* OperandFactory::createInt16( std::string const& value ) const
{
	return new Operand<safe_int16>( safe_int16( create<int16_t>( value, "Int16" ) ) );
}

IOperand const* OperandFactory::createInt32( std::string const& value ) const
{
	return new Operand<safe_int32>( safe_int32( create<int32_t>( value, "Int32" ) ) );
}

IOperand const* OperandFactory::createFloat( std::string const& value ) const
{
	return new Operand<float>( create<float>( value, "float" ) );
}

IOperand const* OperandFactory::createDouble( std::string const& value ) const
{
	return new Operand<double>( create<double>( value, "double" ) );
}

IOperand const* OperandFactory::createLongDouble( std::string const& value ) const
{
	return new Operand<long double>( create<long double>( value, "ldouble" ) );
}