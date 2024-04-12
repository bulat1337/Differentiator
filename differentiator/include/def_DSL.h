#ifndef DEF_DSL_H
#define DEF_DSL_H

/*---------->>          ~~DIFFERENTIATE~~           <<----------*/

#define dL														\
	diff(node->left, tex_file, tex_process)

#define cL														\
	node_copy(node->left)

#define dR														\
	diff(node->right, tex_file, tex_process)

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

/*------------->>         ~~SIMPLIFY~~          <<-------------*/

#define LEFT_VAR												\
	node->left->value.var_value

#define RIGHT_VAR												\
	node->right->value.var_value

#define MAX_VAR_LEN												\
	max_len(strlen(LEFT_VAR), strlen(RIGHT_VAR))

/*--------------->>          ~~TEX~~           <<---------------*/
#define TEX(...)\
	fprintf(tex_file, __VA_ARGS__);

/*--------------->>     ~~TRIVIAL_CASES~~      <<---------------*/

#define LEFT_IS_ZERO\
	node->left->type == NUM && cmp_double(node->left->value.num_value, 0) == 0

#define ZERO__MUL_DIV_POW__ANY				\
	(node->type == OP) &&					\
	(	(node->value.op_value == MUL)	||	\
		(node->value.op_value == DIV)	||	\
		(node->value.op_value == POW)	)

#define ZERO__ADD__ANY\
	node->type == OP && node->value.op_value == ADD

#define RIGHT_IS_ZERO\
	node->right->type == NUM && cmp_double(node->right->value.num_value, 0) == 0

#define ANY__MUL__ZERO\
	node->type == OP && node->value.op_value == MUL

#define ANY__POW__ZERO\
	node->type == OP && node->value.op_value == POW

#define ANY__DIV__ZERO				\
	(node->type == OP) &&			\
	(node->value.op_value == DIV)

#define ANY__ADD_SUB__ZERO					\
	(node->type == OP) &&					\
	(	(node->value.op_value == ADD)	||	\
		(node->value.op_value == SUB)	)
#define LEFT_IS_ONE\
	node->left->type == NUM && cmp_double(node->left->value.num_value, 1) == 0

#define ONE__MUL__ANY\
	node->type == OP && node->value.op_value == MUL

#define ONE__POW__ANY\
	node->type == OP && node->value.op_value == POW

#define RIGHT_IS_ONE\
	node->right->type == NUM && cmp_double(node->right->value.num_value, 1) == 0

#define ANY__MUL_POW_DIV__ONE				\
	(node->type == OP) &&					\
	(	(node->value.op_value == MUL) ||	\
		(node->value.op_value == POW) ||	\
		(node->value.op_value == DIV)	)

#define VAR__SUB__VAR												\
	(node->left->type == VAR) &&									\
			(node->right->type == VAR) &&							\
			(node->type == OP && node->value.op_value == SUB) &&	\
			(!strncmp(LEFT_VAR, RIGHT_VAR, MAX_VAR_LEN))


#endif
