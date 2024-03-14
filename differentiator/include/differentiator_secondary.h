#ifndef DIFFERENTIATOR_SECONDARY
#define DIFFERENTIATOR_SECONDARY

#include "differentiator.h"

int          cmp_double    (double first_double, double second_double);

void         print_node    (B_tree_node *parent, bool is_right_child, FILE *expression);

void         tex_node_print(B_tree_node *parent, bool is_right_child, FILE *expression);

B_tree_node *get_node      (B_tree_node *parent, bool is_right_child);

btr_elem_t   get_var_value (const char *var_name, const Labels_w_len *labels_w_len);

B_tree_node *node_copy     (B_tree_node *node);

#endif