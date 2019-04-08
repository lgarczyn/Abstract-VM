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