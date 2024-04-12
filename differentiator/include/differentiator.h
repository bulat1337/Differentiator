#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include "b_tree.h"
#include "recursive_parser.h"

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
