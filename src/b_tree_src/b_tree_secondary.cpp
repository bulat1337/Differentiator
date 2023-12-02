#include "b_tree_secondary.h"

void node_delete(struct B_tree_node *node)
{
	if(node == NULL)
	{
		return;
	}

	node_delete(node->left);
	node_delete(node->right);

	deallocate_memory(node);
}

struct B_tree_node *allocate_memory(void)
{
	return (struct B_tree_node *)calloc(1, sizeof(struct B_tree_node));
}

error_t deallocate_memory(struct B_tree_node *node)
{
	if(node == NULL)
	{
		return B_TREE_NODE_NULL_PTR;
	}

	free(node);
	node = NULL;

	return ALL_GOOD;
}

void print_regular_nodes(struct B_tree_node *node,
						struct node_charachteristics *nd_description,
						FILE *graphic_dump_code_file_ptr)
{
	if(node == NULL)
	{
		return;
	}

	switch (node->type)
	{
		case NUM:
		{
			nd_description->color = "#5325FF";

			snprintf(nd_description->label, NODE_LABEL_STR_SIZE,
					"{%p | {type: NUM | val: %.2lf} | {L: %p | R: %p}}",
					node, node->value.num_value, node->left, node->right);
			break;
		}
		case OP:
		{
			char *operation_token = get_operation_token(node->value.op_value);

			nd_description->color = "#2595FF";

			snprintf(nd_description->label, NODE_LABEL_STR_SIZE,
					"{%p | {type: OP | val: %s} | {L: %p | R: %p}}",
					node, operation_token, node->left, node->right);
			break;
		}
		default:
		{
			fprintf(stderr, "Unknown node type\n");
		}
	}



	dump_node(node, nd_description, graphic_dump_code_file_ptr);

	print_regular_nodes(node->left,
						nd_description,
						graphic_dump_code_file_ptr);
	print_regular_nodes(node->right,
						nd_description,
						graphic_dump_code_file_ptr);
}

void connect_nodes(struct B_tree_node *node, FILE *graphic_dump_code_file_ptr)
{
	if(node == NULL)
	{
		return;
	}

	if(node->left != NULL)
	{
		fprintf(graphic_dump_code_file_ptr, "%lu -> %lu\n", node, node->left);
		connect_nodes(node->left, graphic_dump_code_file_ptr);
	}

	if(node->right != NULL)
	{
		fprintf(graphic_dump_code_file_ptr, "%lu -> %lu\n", node, node->right);
		connect_nodes(node->right, graphic_dump_code_file_ptr);
	}
}

char *get_operation_token(enum Ops op_type)
{
	#define CASE(op_type)\
	case op_type:\
	{\
		strncpy(operation_token, #op_type, op_token_size);\
		return operation_token;\
		break;\
	}\

	char operation_token[op_token_size] = {};
	switch(op_type)
	{
		CASE(DO_NOTHING)
		CASE(ADD)
		CASE(SUB)
		CASE(MUL)
		CASE(DIV)
		default:
		{
			strncpy(operation_token, "UNKNOWN", op_token_size);
			return operation_token;
			break;
		}
	}
}

error_t dump_node(struct B_tree_node *node, struct node_charachteristics *nd_description,
					FILE *graphic_dump_code_file_ptr)
{
	fprintf(graphic_dump_code_file_ptr, "\t%lu [shape = Mrecord, "
		"fillcolor = \"%s\", label = \"%s\" ];\n",
			node, nd_description->color, nd_description->label);

	return ALL_GOOD;
}
