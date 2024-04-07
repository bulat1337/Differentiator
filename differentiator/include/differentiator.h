#ifndef DIFFERENTIATOR_H
#define DIFFERENTIATOR_H

#include "b_tree.h"
#include "recursive_parser.h"

#define CALLOC(ptr, amount, type)						\
	ptr = (type *)calloc(amount, sizeof(type));			\
	if(ptr == NULL)										\
	{													\
		fprintf(stderr, "Unable to allocate"#ptr"\n");	\
		return UNABLE_TO_ALLOCATE;						\
	}

#define DIFF_EXP(node)\
	diff_exp(node, #node)

#define TEX_EXP(node)\
	tex_exp(node, #node);

#define SIMPL_EXP(node)\
	simpl_exp(node, #node)

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

extern Notations notations;


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

B_tree_node *node_copy            (B_tree_node *node);

B_tree_node *solve_trivial        (B_tree_node *node);

B_tree_node *wrap_consts          (B_tree_node *node);

Uni_ret      simpl_exp            (B_tree_node *root, const char *name);

Uni_ret      diff_exp             (B_tree_node *root, const char *name);

error_t      tex_exp              (B_tree_node *root, const char *name);

#endif
