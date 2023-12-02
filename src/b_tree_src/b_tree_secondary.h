#ifndef B_TREE_SECONDARY_H
#define B_TREE_SECONDARY_H

#include "b_tree.h"

void node_delete(struct B_tree_node *node);
struct B_tree_node *allocate_memory(void);
error_t deallocate_memory(struct B_tree_node *node);
char *get_operation_token(enum Ops op_type);
void print_regular_nodes(struct B_tree_node *node,
						struct node_charachteristics *nd_description,
						FILE *graphic_dump_code_file_ptr);
void connect_nodes(struct B_tree_node *node, FILE *graphic_dump_code_file_ptr);
error_t dump_node(struct B_tree_node *node, struct node_charachteristics *nd_description,
					FILE *graphic_dump_code_file_ptr);

#endif
