#ifndef DIFFERENTIATOR_SECONDARY
#define DIFFERENTIATOR_SECONDARY

#include "differentiator.h"

struct Notat_check
{
	bool notated;
	char letter;
};

void         print_node           (B_tree_node *parent, bool is_right_child, FILE *expression);

void         tex_node_print       (B_tree_node *parent, bool is_right_child,
					               FILE *expression, bool do_var_rep,
								   Notations *notations);

void         tex_notations        (FILE *tex_file, Notations *notations);

void         notations_dtor       (Notations *notations);

void         write_op             (FILE *expression_file, Ops op_value);

B_tree_node *get_node             (B_tree_node *parent, bool is_right_child);

btr_elem_t   get_var_value        (const char *var_name, const Labels_w_len *labels_w_len);

B_tree_node *diff        (struct B_tree_node *node, FILE *tex_file,
						  bool tex_process, Notations *notations);

error_t      tex_src_diff_node    (FILE *tex_file, B_tree_node *node,
								   Notations *notations);

error_t      tex_src_simpl_node   (FILE *tex_file, B_tree_node *node,
								   Notations *notations);

error_t      tex_result           (FILE *tex_file, B_tree_node *node,
								   Notations *notations);

error_t      create_tex_expression(struct B_tree_node *root, FILE *tex_file,
								   bool do_var_rep, Notations *notations);

error_t      init_notations       (Notations *notations);

B_tree_node *simpl                (B_tree_node *node,  FILE *tex_file,
							       bool tex_process, Notations *notations);

size_t       get_node_size        (B_tree_node *node, Notations *notations);

size_t       manage_notations     (B_tree_node *node, Notations *notations);

char         set_notation         (B_tree_node *node, Notations *notations);

Notat_check  check_if_notated     (B_tree_node *node, Notations *notations);

B_tree_node *node_copy            (B_tree_node *node);

B_tree_node *solve_trivial        (B_tree_node *node);

B_tree_node *wrap_consts          (B_tree_node *node);


#endif
