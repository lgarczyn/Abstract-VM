#include "Operand.hpp"

template<>
const eOperandType Operand<safe_int8>::type = e_ty_i8;
template<>
const eOperandType Operand<safe_int16>::type = e_ty_i16;
template<>
const eOperandType Operand<safe_int32>::type = e_ty_i32;
template<>
const eOperandType Operand<float>::type = e_ty_f32;
template<>
const eOperandType Operand<double>::type = e_ty_f64;
template<>
const eOperandType Operand<long double>::type = e_ty_f80;

const OperandInfo IOperand::operands[OPERAND_TYPE_NUM] = {
	{e_ty_i8, "int8"},
	{e_ty_i16, "int16"},
	{e_ty_i32, "int32"},
	{e_ty_f32, "float"},
	{e_ty_f64, "double"},
	{e_ty_f80, "ldouble"},
};

std::ostream &operator<<(std::ostream &out, const IOperand &hex)
{
	out << hex.toString();
	return out;
}