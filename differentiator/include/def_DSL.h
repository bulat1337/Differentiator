#ifndef DEF_DSL_H
#define DEF_DSL_H

#define dL\
	differentiate(node->left)

#define cL\
	node_copy(node->left)

#define dR\
	differentiate(node->right)

#define cR\
	node_copy(node->right)

#define ZERO\
	create_node(NUM, {.num_value = 0}, NULL, NULL).arg.node

#define ONE\
	create_node(NUM, {.num_value = 1}, NULL, NULL).arg.node

#define TWO\
	create_node(NUM, {.num_value = 2}, NULL, NULL).arg.node

#define MUL(left, right)\
	create_node(OP, {.op_value = MUL}, left, right).arg.node

#define DIV(left, right)\
	create_node(OP, {.op_value = DIV}, left, right).arg.node

#define POW(left, right)\
	create_node(OP, {.op_value = POW}, left, right).arg.node

#define ADD(left, right)\
	create_node(OP, {.op_value = ADD}, left, right).arg.node

#define SUB(left, right)\
	create_node(OP, {.op_value = SUB}, left, right).arg.node

#define LN(child)\
	create_node(OP, {.op_value = LN}, NULL, child).arg.node

#define SIN(child)\
	create_node(OP, {.op_value = SIN}, NULL, child).arg.node

#define COS(child)\
	create_node(OP, {.op_value = COS}, NULL, child).arg.node


#endif
