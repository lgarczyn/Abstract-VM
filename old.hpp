#pragma once
#include <string>
#include "IOperand.hpp"
#include <functional>

template <typename T>
class Operand: public IOperand {

private:
	static const eOperandType type;
	T value;
	std::string representation;

public:
	Operand(T value) : value(value), representation(std::to_string(value)) {}

	int getPrecision( void ) const {
		return static_cast<int>(type);
	}

	int getMaxPrecision( IOperand const& rhs ) const {
		return std::max(this->getPrecision(), rhs.getPrecision());
	} 
	
	eOperandType getType( void ) const {
		return type;
	}
	
	IOperand const *operator+( IOperand const& rhs ) const {

		if (rhs.getPrecision() > this->getPrecision())
			return rhs + *this;
		
		T rval = 0;
		rhs.toType(rval);
		return new Operand<T>(this->value + rval);
	}
	
	IOperand const *operator-( IOperand const& rhs ) const {
		if (rhs.getPrecision() > this->getPrecision())
			return rhs - *this;
		
		T rval = 0;
		rhs.toType(rval);
		return new Operand<T>(this->value - rval);
	}
	
	IOperand const *operator*( IOperand const& rhs ) const {
		if (rhs.getPrecision() > this->getPrecision())
			return rhs * *this;
		
		T rval = 0;
		rhs.toType(rval);
		return new Operand<T>(this->value * rval);
	}
	
	IOperand const *operator/( IOperand const& rhs ) const {
		if (rhs.getPrecision() > this->getPrecision())
			return rhs / *this;
		
		T rval = 0;
		rhs.toType(rval);
		return new Operand<T>(this->value / rval);
	}
	
	IOperand const *operator%( IOperand const& rhs ) const {
		if (rhs.getPrecision() > this->getPrecision())
			return rhs % *this;
		
		T rval = 0;
		rhs.toType(rval);

		T ret;
		if std::is_same<T, float>::value {
			ret = fmodf(this->value, rval);
		}
		return new Operand<T>(std::modulus<T>(this->value, rval));
	}
	
	std::string const &toString( void ) const {
		return this->representation;
	}
	
	void toType( int8_t & out ) const {
		out = static_cast<int8_t>(this->value);
	}

	void toType( int16_t & out ) const {
		out = static_cast<int16_t>(this->value);
	}

	void toType( int32_t & out ) const {
		out = static_cast<int32_t>(this->value);
	}

	void toType( float & out ) const {
		out = static_cast<float>(this->value);
	}

	void toType( double & out ) const {
		out = static_cast<double>(this->value);
	}
};
