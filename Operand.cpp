#include "Operand.hpp"

template<>
const eOperandType Operand<int8_t>::type = i8;
template<>
const eOperandType Operand<int16_t>::type = i16;
template<>
const eOperandType Operand<int32_t>::type = i32;
template<>
const eOperandType Operand<float>::type = f32;
template<>
const eOperandType Operand<double>::type = f64;