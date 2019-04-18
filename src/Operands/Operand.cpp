// Implements all Operand related symbols
// IOperand statics
// AOperand functions
// Operand<T> instance specific symbols

#include "Operand.hpp"

#include <iomanip>
#include <sstream>

// IOperand parsing table info

const OperandInfo IOperand::operands[ OPERAND_TYPE_NUM ] = {
	{ TypeI8, "int8" },
	{ TypeI16, "int16" },
	{ TypeI32, "int32" },
	{ TypeF32, "float" },
	{ TypeF64, "double" },
	{ TypeF80, "ldouble" },
};

OperandInfo::OperandInfo() = default;
OperandInfo::OperandInfo( eOperandType type, const std::string name )
	: type( type )
	, name( name )
{
}
OperandInfo::OperandInfo( const OperandInfo& cpy ) = default;
OperandInfo& OperandInfo::operator=( const OperandInfo& rhs ) = default;
OperandInfo::~OperandInfo() = default;

// IOperand display

std::ostream& operator<<( std::ostream& out, const IOperand& hex )
{
	out << hex.toString();
	return out;
}

// Implementation of AOperand operators

int AOperand::getMaxPrecision( IOperand const& rhs ) const
{
	return std::max( this->getPrecision(), rhs.getPrecision() );
}

IOperand const* AOperand::operator+( IOperand const& i_rhs ) const
{
	auto& rhs = dynamic_cast<const AOperand&>( i_rhs );
	int precision = this->getMaxPrecision( rhs );
	switch ( precision )
	{
	case TypeI8: return new Operand<safe_int8>( this->asI8() + rhs.asI8() );
	case TypeI16: return new Operand<safe_int16>( this->asI16() + rhs.asI16() );
	case TypeI32: return new Operand<safe_int32>( this->asI32() + rhs.asI32() );
	case TypeF32: return new Operand<float>( this->asF32() + rhs.asF32() );
	case TypeF64: return new Operand<double>( this->asF64() + rhs.asF64() );
	case TypeF80: return new Operand<long double>( this->asF80() + rhs.asF80() );
	}
	throw CorruptOperandException();
}

IOperand const* AOperand::operator-( IOperand const& i_rhs ) const
{
	auto& rhs = dynamic_cast<const AOperand&>( i_rhs );
	int precision = this->getMaxPrecision( rhs );
	switch ( precision )
	{
	case TypeI8: return new Operand<safe_int8>( this->asI8() - rhs.asI8() );
	case TypeI16: return new Operand<safe_int16>( this->asI16() - rhs.asI16() );
	case TypeI32: return new Operand<safe_int32>( this->asI32() - rhs.asI32() );
	case TypeF32: return new Operand<float>( this->asF32() - rhs.asF32() );
	case TypeF64: return new Operand<double>( this->asF64() - rhs.asF64() );
	case TypeF80: return new Operand<long double>( this->asF80() - rhs.asF80() );
	}
	throw CorruptOperandException();
}

IOperand const* AOperand::operator*( IOperand const& i_rhs ) const
{
	auto& rhs = dynamic_cast<const AOperand&>( i_rhs );
	int precision = this->getMaxPrecision( rhs );
	switch ( precision )
	{
	case TypeI8: return new Operand<safe_int8>( this->asI8() * rhs.asI8() );
	case TypeI16: return new Operand<safe_int16>( this->asI16() * rhs.asI16() );
	case TypeI32: return new Operand<safe_int32>( this->asI32() * rhs.asI32() );
	case TypeF32: return new Operand<float>( this->asF32() * rhs.asF32() );
	case TypeF64: return new Operand<double>( this->asF64() * rhs.asF64() );
	case TypeF80: return new Operand<long double>( this->asF80() * rhs.asF80() );
	}
	throw CorruptOperandException();
}

IOperand const* AOperand::operator/( IOperand const& i_rhs ) const
{
	auto& rhs = dynamic_cast<const AOperand&>( i_rhs );
	int precision = this->getMaxPrecision( rhs );
	switch ( precision )
	{
	case TypeI8: return new Operand<safe_int8>( this->asI8() / rhs.asI8() );
	case TypeI16: return new Operand<safe_int16>( this->asI16() / rhs.asI16() );
	case TypeI32: return new Operand<safe_int32>( this->asI32() / rhs.asI32() );
	case TypeF32: return new Operand<float>( this->asF32() / rhs.asF32() );
	case TypeF64: return new Operand<double>( this->asF64() / rhs.asF64() );
	case TypeF80: return new Operand<long double>( this->asF80() / rhs.asF80() );
	}
	throw CorruptOperandException();
}

IOperand const* AOperand::operator%( IOperand const& i_rhs ) const
{
	auto& rhs = dynamic_cast<const AOperand&>( i_rhs );
	int precision = this->getMaxPrecision( rhs );
	switch ( precision )
	{
	case TypeI8: return new Operand<safe_int8>( this->asI8() % rhs.asI8() );
	case TypeI16: return new Operand<safe_int16>( this->asI16() % rhs.asI16() );
	case TypeI32: return new Operand<safe_int32>( this->asI32() % rhs.asI32() );
	case TypeF32: return new Operand<float>( std::fmodf( this->asF32(), rhs.asF32() ) );
	case TypeF64: return new Operand<double>( std::fmod( this->asF64(), rhs.asF64() ) );
	case TypeF80: return new Operand<long double>( std::fmodl( this->asF80(), rhs.asF80() ) );
	}
	throw CorruptOperandException();
}

bool AOperand::operator==( IOperand const& i_rhs ) const
{
	auto& rhs = dynamic_cast<const AOperand&>( i_rhs );
	int precision = this->getMaxPrecision( rhs );
	switch ( precision )
	{
	case TypeI8: return this->asI8() == rhs.asI8();
	case TypeI16: return this->asI16() == rhs.asI16();
	case TypeI32: return this->asI32() == rhs.asI32();
	case TypeF32: return this->asF32() == rhs.asF32();
	case TypeF64: return this->asF64() == rhs.asF64();
	case TypeF80: return this->asF80() == rhs.asF80();
	}
	throw CorruptOperandException();
}

bool AOperand::operator!=( IOperand const& rhs ) const { return !( *this == rhs ); }

// Type value of all Operand instances

template <> const eOperandType Operand<safe_int8>::type = TypeI8;
template <> const eOperandType Operand<safe_int16>::type = TypeI16;
template <> const eOperandType Operand<safe_int32>::type = TypeI32;
template <> const eOperandType Operand<float>::type = TypeF32;
template <> const eOperandType Operand<double>::type = TypeF64;
template <> const eOperandType Operand<long double>::type = TypeF80;

// Get the string representation of an Operand instanciation

template <> std::string Operand<safe_int8>::toRepresentation( safe_int8 i )
{
	return std::to_string( static_cast<int32_t>( i ) );
}

template <> std::string Operand<safe_int16>::toRepresentation( safe_int16 i )
{
	return std::to_string( static_cast<int32_t>( i ) );
}

template <> std::string Operand<safe_int32>::toRepresentation( safe_int32 i )
{
	return std::to_string( static_cast<int32_t>( i ) );
}

template <> std::string Operand<float>::toRepresentation( float f )
{
	int precision = std::numeric_limits<float>::max_digits10 - 2;
	std::stringstream ss;
	ss << std::setprecision( precision ) << f;
	return ss.str();
}

template <> std::string Operand<double>::toRepresentation( double f )
{
	int precision = std::numeric_limits<double>::max_digits10 - 2;
	std::stringstream ss;
	ss << std::setprecision( precision ) << f;
	return ss.str();
}

template <> std::string Operand<long double>::toRepresentation( long double f )
{
	int precision = std::numeric_limits<long double>::max_digits10 - 2;
	std::stringstream ss;
	ss << std::setprecision( precision ) << f;
	return ss.str();
}