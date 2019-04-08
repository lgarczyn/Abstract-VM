#include "Operation.hpp"

const OperationInfo Operation::operations[OPERATION_TYPE_NUM] = {
	{e_op_push, "push", true, 0, &Operation::op_push},
	{e_op_pop, "pop", false, 1, &Operation::op_pop},
	{e_op_dump, "dump", false, 0, &Operation::op_dump},
	{e_op_assert, "assert", true, 1, &Operation::op_assert},
	{e_op_add, "add", false, 2, &Operation::op_add},
	{e_op_sub, "sub", false, 2, &Operation::op_sub},
	{e_op_mul, "mul", false, 2, &Operation::op_mul},
	{e_op_div, "div", false, 2, &Operation::op_div},
	{e_op_mod, "mod", false, 2, &Operation::op_mod},
	{e_op_print, "print", false, 1, &Operation::op_print},
	{e_op_exit, "exit", false, 0, &Operation::op_exit},
};