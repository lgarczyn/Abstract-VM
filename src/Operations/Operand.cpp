#include "Operand.hpp"

template<>
const eOperandType Operand<int8_t>::type = e_ty_i8;
template<>
const eOperandType Operand<int16_t>::type = e_ty_i16;
template<>
const eOperandType Operand<int32_t>::type = e_ty_i32;
template<>
const eOperandType Operand<float>::type = e_ty_f32;
template<>
const eOperandType Operand<double>::type = e_ty_f64;

const OperandInfo IOperand::Operands[OPERAND_TYPE_NUM] = {
	{e_ty_i8, "int8"},
	{e_ty_i16, "int16"},
	{e_ty_i32, "int32"},
	{e_ty_f32, "float"},
	{e_ty_f64, "double"},
};
