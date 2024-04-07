#ifndef DIFFERENTIATOR_SECONDARY
#define DIFFERENTIATOR_SECONDARY

#include "differentiator.h"

const size_t NOTAT_BOUND         = 10;
const size_t AMOUNT_OF_NOTATIONS = 26;

struct Notat_check
{
	bool notated;
	char letter;
};

void         print_node           (B_tree_node *parent, bool is_right_child, FILE *expression);

void         tex_node_print       (struct B_tree_node *parent, bool is_right_child,
					               FILE *expression, bool do_var_rep);

void         tex_notations        (FILE *tex_file);

B_tree_node *get_node             (B_tree_node *parent, bool is_right_child);

btr_elem_t   get_var_value        (const char *var_name, const Labels_w_len *labels_w_len);

B_tree_node *differentiate        (B_tree_node *node, FILE *tex_file);

error_t      tex_src_diff_node    (FILE *tex_file, B_tree_node *node);

error_t      tex_src_simpl_node   (FILE *tex_file, B_tree_node *node);

error_t      tex_result           (FILE *tex_file, B_tree_node *result);

error_t      create_tex_expression(struct B_tree_node *root, FILE *tex_file, bool do_var_rep);

error_t      refresh_notations    ();

B_tree_node *simplify             (B_tree_node *node,  FILE *tex_file);

size_t       get_node_size        (B_tree_node *node);

char         set_notation         (B_tree_node *node);

Notat_check  check_if_notated     (B_tree_node *node);


#endif
