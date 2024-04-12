#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include "b_tree.h"
#include "recursive_parser.h"

const size_t NOTAT_BOUND         = 5;
const size_t AMOUNT_OF_NOTATIONS = 26;

#define CALLOC(ptr, amount, type)						\
	ptr = (type *)calloc(amount, sizeof(type));			\
	if(ptr == NULL)										\
	{													\
		fprintf(stderr, "Unable to allocate"#ptr"\n");	\
		return UNABLE_TO_ALLOCATE;						\
	}

#define DIFF_EXPR(node)\
	diff_expr(node, #node)

#define DIFF_EXPR_TEX(node, tex_process)\
	diff_expr(node, #node, tex_process)

#define TEX_EXPR(node)\
	tex_expr(node, #node);

#define TXT_EXPR(node)\
	txt_expr(node, #node);

#define SIMPL_EXPR(node)\
	simpl_expr(node, #node)\

#define SIMPL_EXPR_TEX(node, tex_process)\
	simpl_expr(node, #node, tex_process)

struct Notation
{
	char        letter;
	B_tree_node *node;
};

struct Notations
{
	size_t    size;
	Notation *data;
};

struct Var_label
{
	char *name;
	btr_elem_t value;
};

struct Labels_w_len
{
	struct Var_label *labels;
	size_t length;
};

btr_elem_t eval      (B_tree_node *node, Labels_w_len *labels_w_len);

Uni_ret    txt_expr   (B_tree_node *root, const char *name);

Uni_ret    simpl_expr (B_tree_node *root, const char *name, bool tex = false);

Uni_ret    diff_expr  (B_tree_node *root, const char *name, bool tex = false);

Uni_ret    tex_expr   (B_tree_node *root, const char *name);

#endif
