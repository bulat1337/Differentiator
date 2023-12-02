#ifndef B_TREE_H
#define B_TREE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef double btr_elem_t;

enum Err_ID
{
	ALL_GOOD 		         = 0,
	UNABLE_TO_OPEN_FILE      = 1 << 0,
	UNABLE_TO_ALLOCATE       = 1 << 1,
	UNEXPECTED_WRITTEN_ELEMS = 1 << 3,
	B_TREE_NULL_PTR          = 1 << 4,
	B_TREE_NODE_NULL_PTR     = 1 << 5,
	INVALID_VALUE            = 1 << 6,
	INVALID_INDEX            = 1 << 7,
	PARENT_NODE_IS_FREE      = 1 << 8,
	UNKNOWN_NODE_TYPE        = 1 << 9,
};

typedef enum Err_ID error_t;

enum Node_type
{
	NUM = 0,
	OP  = 1,
	VAR = 2,
};

enum Ops
{
	DO_NOTHING = 0,
	ADD        = 1,
	SUB        = 2,
	MUL        = 3,
	DIV        = 4,
	POW        = 5,
};

union Node_value
{
	double   num_value;
	enum Ops op_value;
};

struct B_tree_node
{
	enum   Node_type type;
	union  Node_value value;
	struct B_tree_node *left;
	struct B_tree_node *right;
};

struct Create_node_result
{
	struct B_tree_node *new_node;
	error_t error_code;
};

struct Gr_dump_code_gen_result
{
	error_t error_code;
	FILE *graphic_dump_code_file_ptr;
};

struct node_charachteristics
{
	char *name;
	char *color;
	char *label;
};

const size_t NODE_LABEL_STR_SIZE  = 100;
const size_t op_token_size = 15;


struct Create_node_result create_node(enum Node_type type, union Node_value);
error_t add_child(struct B_tree_node *parent, struct B_tree_node *child, bool is_right_child);
error_t destroy_subtree(struct B_tree_node *parent_node, bool is_right_child);
struct Gr_dump_code_gen_result gr_dump_code_gen(struct B_tree_node *root);


#endif
