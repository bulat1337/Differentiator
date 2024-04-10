#ifndef DIFFERENTIATOR_SECONDARY
#define DIFFERENTIATOR_SECONDARY

#include "differentiator.h"

struct Notat_check
{
	bool notated;
	char letter;
};

void         print_node           (B_tree_node *parent, bool is_right_child, FILE *expression);

void         tex_node_print       (struct B_tree_node *parent, bool is_right_child,
					               FILE *expression, bool do_var_rep);

void         tex_notations        (FILE *tex_file);

void         notations_dtor       ();

B_tree_node *get_node             (B_tree_node *parent, bool is_right_child);

btr_elem_t   get_var_value        (const char *var_name, const Labels_w_len *labels_w_len);

B_tree_node *differentiate        (B_tree_node *node, FILE *tex_file);

error_t      tex_src_diff_node    (FILE *tex_file, B_tree_node *node);

error_t      tex_src_simpl_node   (FILE *tex_file, B_tree_node *node);

error_t      tex_result           (FILE *tex_file, B_tree_node *node);

error_t      create_tex_expression(struct B_tree_node *root, FILE *tex_file, bool do_var_rep);

error_t      init_notations    ();

B_tree_node *simplify             (B_tree_node *node,  FILE *tex_file);

size_t       get_node_size        (B_tree_node *node);

size_t       manage_notations     (B_tree_node *node);

char         set_notation         (B_tree_node *node);

Notat_check  check_if_notated     (B_tree_node *node);

B_tree_node *node_copy            (B_tree_node *node);

B_tree_node *solve_trivial        (B_tree_node *node);

B_tree_node *wrap_consts          (B_tree_node *node);


#endif
