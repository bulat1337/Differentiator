#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include "b_tree.h"
#include "recursive_parser.h"

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

btr_elem_t   eval                 (B_tree_node *node, Labels_w_len *labels_w_len);

Uni_ret      create_txt_expression(B_tree_node *root, const char *file_name);

Uni_ret      create_tex_expression(B_tree_node *root, const char *file_name);

B_tree_node *differentiate        (B_tree_node *node);

#endif
