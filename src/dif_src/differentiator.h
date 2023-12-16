#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include "../b_tree_src/b_tree.h"
#include "../recursive_parser_src/recursive_parser.h"

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

btr_elem_t eval(struct B_tree_node *node, struct Labels_w_len *labels_w_len);
struct Create_expression_result create_txt_expression(struct B_tree_node *root,
													  const char *file_name);
struct Create_expression_result create_tex_expression(struct B_tree_node *root,
													  const char *file_name);
struct B_tree_node *differentiate(struct B_tree_node *node);

#endif
