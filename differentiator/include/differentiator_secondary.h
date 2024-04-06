#ifndef DIFFERENTIATOR_SECONDARY
#define DIFFERENTIATOR_SECONDARY

#include "differentiator.h"

void         print_node           (B_tree_node *parent, bool is_right_child, FILE *expression);

void         tex_node_print       (B_tree_node *parent, bool is_right_child, FILE *expression);

B_tree_node *get_node             (B_tree_node *parent, bool is_right_child);

btr_elem_t   get_var_value        (const char *var_name, const Labels_w_len *labels_w_len);

B_tree_node *differentiate        (B_tree_node *node, FILE *tex_file);

error_t      tex_src_diff_node    (FILE *tex_file, B_tree_node *node);

error_t      tex_src_simpl_node   (FILE *tex_file, B_tree_node *node);

error_t      tex_result           (FILE *tex_file, B_tree_node *result);

error_t      create_tex_expression(struct B_tree_node *root, FILE *tex_file);

B_tree_node *simplify             (B_tree_node *node,  FILE *tex_file);


#endif
