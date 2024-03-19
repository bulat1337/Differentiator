#ifndef DEF_DSL_H
#define DEF_DSL_H

/*---------->>     ~~DIFFERENTIATE MACROSES~~      <<----------*/

#define dL														\
	differentiate(node->left)

#define cL														\
	node_copy(node->left)

#define dR														\
	differentiate(node->right)

#define cR														\
	node_copy(node->right)

#define ZERO													\
	create_node(NUM, {.num_value = 0}, NULL, NULL).arg.node

#define ONE														\
	create_node(NUM, {.num_value = 1}, NULL, NULL).arg.node

#define TWO														\
	create_node(NUM, {.num_value = 2}, NULL, NULL).arg.node

#define MUL(left, right)										\
	create_node(OP, {.op_value = MUL}, left, right).arg.node

#define DIV(left, right)										\
	create_node(OP, {.op_value = DIV}, left, right).arg.node

#define POW(left, right)										\
	create_node(OP, {.op_value = POW}, left, right).arg.node

#define ADD(left, right)										\
	create_node(OP, {.op_value = ADD}, left, right).arg.node

#define SUB(left, right)										\
	create_node(OP, {.op_value = SUB}, left, right).arg.node

#define LN(child)												\
	create_node(OP, {.op_value = LN}, NULL, child).arg.node

#define SIN(child)												\
	create_node(OP, {.op_value = SIN}, NULL, child).arg.node

#define COS(child)												\
	create_node(OP, {.op_value = COS}, NULL, child).arg.node

#define SQRT(child)												\
	create_node(OP, {.op_value = SQRT}, NULL, child).arg.node

/*------------->>     ~~SIMPLIFY MACROSES~~      <<-------------*/

#define LEFT_VAR												\
	node->left->value.var_value

#define RIGHT_VAR												\
	node->right->value.var_value

#define MAX_VAR_LEN												\
	max_len(strlen(LEFT_VAR), strlen(RIGHT_VAR))


#endif
