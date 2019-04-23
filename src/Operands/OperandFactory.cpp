#include "OperandFactory.hpp"

#include "Exceptions/VMException.hpp"
#include "Operand.hpp"

#include <sstream>

const OperandConstructor OperandFactory::constructors[ OPERAND_TYPE_NUM ] = {
	&OperandFactory::createInt8,
	&OperandFactory::createInt16,
	&OperandFactory::createInt32,
	&OperandFactory::createFloat,
	&OperandFactory::createDouble,
	&OperandFactory::createLongDouble,
};


template <typename T> T create( eOperandType type, std::string const& value )
{
	T out = 0;
	auto ss = std::stringstream( value );

	ss >> out;

	if ( std::isfinite( out ) == false )
	{
		throw LargeFloatingPointException( value, IOperand::operands[ type ].name );
	}
	if ( ss.fail() )
	{
		throw LargeIntegerException( value, IOperand::operands[ type ].name );
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
	int16_t parsed = create<int16_t>( TypeI8, value );
	int8_t out;
	if ( SafeCast( parsed, out ) )
	{
		return new Operand<safe_int8>( safe_int8( out ) );
	}
	throw LargeIntegerException( value, IOperand::operands[ TypeI8 ].name );
}

IOperand const* OperandFactory::createInt16( std::string const& value ) const
{
	return new Operand<safe_int16>( safe_int16( create<int16_t>( TypeI16, value ) ) );
}

IOperand const* OperandFactory::createInt32( std::string const& value ) const
{
	return new Operand<safe_int32>( safe_int32( create<int32_t>( TypeI32, value ) ) );
}

IOperand const* OperandFactory::createFloat( std::string const& value ) const
{
	return new Operand<float>( create<float>( TypeF32, value ) );
}

IOperand const* OperandFactory::createDouble( std::string const& value ) const
{
	return new Operand<double>( create<double>( TypeF64, value ) );
}

IOperand const* OperandFactory::createLongDouble( std::string const& value ) const
{
	return new Operand<long double>( create<long double>( TypeF80, value ) );
}