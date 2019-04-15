// Implements all Operand related symbols
// IOperand statics
// AOperand functions
// Operand<T> instance specific symbols

#include "Operand.hpp"

// IOperand parsing table info

const OperandInfo IOperand::operands[ OPERAND_TYPE_NUM ] = {
	{ e_ty_i8, "int8" },
	{ e_ty_i16, "int16" },
	{ e_ty_i32, "int32" },
	{ e_ty_f32, "float" },
	{ e_ty_f64, "double" },
	{ e_ty_f80, "ldouble" },
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

IOperand const* AOperand::operator+( IOperand const& rhs ) const
{
	int precision = this->getMaxPrecision( rhs );
	switch ( precision )
	{
	case e_ty_i8: return new Operand<safe_int8>( this->asI8() + rhs.asI8() );
	case e_ty_i16: return new Operand<safe_int16>( this->asI16() + rhs.asI16() );
	case e_ty_i32: return new Operand<safe_int32>( this->asI32() + rhs.asI32() );
	case e_ty_f32: return new Operand<float>( this->asF32() + rhs.asF32() );
	case e_ty_f64: return new Operand<double>( this->asF64() + rhs.asF64() );
	case e_ty_f80: return new Operand<long double>( this->asF80() + rhs.asF80() );
	}
	throw CorruptOperandException();
}

IOperand const* AOperand::operator-( IOperand const& rhs ) const
{
	int precision = this->getMaxPrecision( rhs );
	switch ( precision )
	{
	case e_ty_i8: return new Operand<safe_int8>( this->asI8() - rhs.asI8() );
	case e_ty_i16: return new Operand<safe_int16>( this->asI16() - rhs.asI16() );
	case e_ty_i32: return new Operand<safe_int32>( this->asI32() - rhs.asI32() );
	case e_ty_f32: return new Operand<float>( this->asF32() - rhs.asF32() );
	case e_ty_f64: return new Operand<double>( this->asF64() - rhs.asF64() );
	case e_ty_f80: return new Operand<long double>( this->asF80() - rhs.asF80() );
	}
	throw CorruptOperandException();
}

IOperand const* AOperand::operator*( IOperand const& rhs ) const
{
	int precision = this->getMaxPrecision( rhs );
	switch ( precision )
	{
	case e_ty_i8: return new Operand<safe_int8>( this->asI8() * rhs.asI8() );
	case e_ty_i16: return new Operand<safe_int16>( this->asI16() * rhs.asI16() );
	case e_ty_i32: return new Operand<safe_int32>( this->asI32() * rhs.asI32() );
	case e_ty_f32: return new Operand<float>( this->asF32() * rhs.asF32() );
	case e_ty_f64: return new Operand<double>( this->asF64() * rhs.asF64() );
	case e_ty_f80: return new Operand<long double>( this->asF80() * rhs.asF80() );
	}
	throw CorruptOperandException();
}

IOperand const* AOperand::operator/( IOperand const& rhs ) const
{
	int precision = this->getMaxPrecision( rhs );
	switch ( precision )
	{
	case e_ty_i8: return new Operand<safe_int8>( this->asI8() / rhs.asI8() );
	case e_ty_i16: return new Operand<safe_int16>( this->asI16() / rhs.asI16() );
	case e_ty_i32: return new Operand<safe_int32>( this->asI32() / rhs.asI32() );
	case e_ty_f32: return new Operand<float>( this->asF32() / rhs.asF32() );
	case e_ty_f64: return new Operand<double>( this->asF64() / rhs.asF64() );
	case e_ty_f80: return new Operand<long double>( this->asF80() / rhs.asF80() );
	}
	throw CorruptOperandException();
}

IOperand const* AOperand::operator%( IOperand const& rhs ) const
{
	int precision = this->getMaxPrecision( rhs );
	switch ( precision )
	{
	case e_ty_i8: return new Operand<safe_int8>( this->asI8() % rhs.asI8() );
	case e_ty_i16: return new Operand<safe_int16>( this->asI16() % rhs.asI16() );
	case e_ty_i32: return new Operand<safe_int32>( this->asI32() % rhs.asI32() );
	case e_ty_f32: return new Operand<float>( std::fmodf( this->asF32(), rhs.asF32() ) );
	case e_ty_f64: return new Operand<double>( std::fmod( this->asF64(), rhs.asF64() ) );
	case e_ty_f80: return new Operand<long double>( std::fmodl( this->asF80(), rhs.asF80() ) );
	}
	throw CorruptOperandException();
}

bool AOperand::operator==( IOperand const& rhs ) const
{
	int precision = this->getMaxPrecision( rhs );
	switch ( precision )
	{
	case e_ty_i8: return this->asI8() == rhs.asI8();
	case e_ty_i16: return this->asI16() == rhs.asI16();
	case e_ty_i32: return this->asI32() == rhs.asI32();
	case e_ty_f32: return this->asF32() == rhs.asF32();
	case e_ty_f64: return this->asF64() == rhs.asF64();
	case e_ty_f80: return this->asF80() == rhs.asF80();
	}
	throw CorruptOperandException();
}

bool AOperand::operator!=( IOperand const& rhs ) const { return !( *this == rhs ); }

// Type value of all Operand instances

template <> const eOperandType Operand<safe_int8>::type = e_ty_i8;
template <> const eOperandType Operand<safe_int16>::type = e_ty_i16;
template <> const eOperandType Operand<safe_int32>::type = e_ty_i32;
template <> const eOperandType Operand<float>::type = e_ty_f32;
template <> const eOperandType Operand<double>::type = e_ty_f64;
template <> const eOperandType Operand<long double>::type = e_ty_f80;

// Get the string representation of an Operand instanciation

template <> std::string Operand<safe_int8>::to_representation( safe_int8 i )
{
	return std::to_string( static_cast<int32_t>( i ) );
}

template <> std::string Operand<safe_int16>::to_representation( safe_int16 i )
{
	return std::to_string( static_cast<int32_t>( i ) );
}

template <> std::string Operand<safe_int32>::to_representation( safe_int32 i )
{
	return std::to_string( static_cast<int32_t>( i ) );
}

template <> std::string Operand<float>::to_representation( float f )
{
	int precision = std::numeric_limits<float>::max_digits10 - 2;
	std::stringstream ss;
	ss << std::setprecision( precision ) << f;
	return ss.str();
}

template <> std::string Operand<double>::to_representation( double f )
{
	int precision = std::numeric_limits<double>::max_digits10 - 2;
	std::stringstream ss;
	ss << std::setprecision( precision ) << f;
	return ss.str();
}

template <> std::string Operand<long double>::to_representation( long double f )
{
	int precision = std::numeric_limits<long double>::max_digits10 - 2;
	std::stringstream ss;
	ss << std::setprecision( precision ) << f;
	return ss.str();
}