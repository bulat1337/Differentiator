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

error_t print_regular_nodes(struct B_tree_node *node,
						struct node_charachteristics *nd_description,
						FILE *graphic_dump_code_file_ptr)
{
	if(node == NULL)
	{
		return ALL_GOOD;
	}

	switch (node->type)
	{
		case NUM:
		{
			nd_description->color = "#2595FF";

			snprintf(nd_description->label, NODE_LABEL_STR_SIZE,
					"{%p | {type: NUM | val: %.2lf} | {L: %p | R: %p}}",
					node, node->value.num_value, node->left, node->right);
			break;
		}
		case OP:
		{
			char *operation_token = get_operation_token(node->value.op_value);
			if(operation_token == NULL)
			{
				return UNABLE_TO_ALLOCATE;
			}

			nd_description->color = "#FF5555";

			snprintf(nd_description->label, NODE_LABEL_STR_SIZE,
					"{%p | {type: OP | val: %s} | {L: %p | R: %p}}",
					node, operation_token, node->left, node->right);

			free(operation_token);

			break;
		}
		case VAR:
		{
			nd_description->color = PASTEL_GREEN;

			snprintf(nd_description->label, NODE_LABEL_STR_SIZE,
					"{%p | {type: VAR | val: %s} | {L: %p | R: %p}}",
					node, node->value.var_value, node->left, node->right);
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

	return ALL_GOOD;
}

void connect_nodes(struct B_tree_node *node, FILE *graphic_dump_code_file_ptr)
{
	if(node == NULL)
	{
		return;
	}

	if(node->left != NULL)
	{
		fprintf(graphic_dump_code_file_ptr, "%lu -> %lu\n", (unsigned long)node,
															(unsigned long)node->left);
		connect_nodes(node->left, graphic_dump_code_file_ptr);
	}

	if(node->right != NULL)
	{
		fprintf(graphic_dump_code_file_ptr, "%lu -> %lu\n", (unsigned long)node,
															(unsigned long)node->right);
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

	char *operation_token = (char *)calloc(op_token_size, sizeof(char));
	if(operation_token == NULL)
	{
		perror("Unable to allocate:");
		return NULL;
	}

	switch(op_type)
	{
		CASE(DO_NOTHING)
		CASE(ADD)
		CASE(SUB)
		CASE(MUL)
		CASE(DIV)
		CASE(POW)
		default:
		{
			strncpy(operation_token, "UNKNOWN", op_token_size);
			return operation_token;
			break;
		}
	}

	#undef CASE
}

error_t dump_node(struct B_tree_node *node, struct node_charachteristics *nd_description,
					FILE *graphic_dump_code_file_ptr)
{
	fprintf(graphic_dump_code_file_ptr, "\t%lu [shape = Mrecord, "
		"fillcolor = \"%s\", label = \"%s\" ];\n",
			(unsigned long)node, nd_description->color, nd_description->label);

	return ALL_GOOD;
}

void node_consoole_dump(struct B_tree_node *node, FILE *console_dump_file)
{
	#define DUMP(...) fprintf(console_dump_file, __VA_ARGS__);

	if(node == NULL)
	{
		return;
	}

	DUMP("%p", node);

	switch(node->type)
	{
		case NUM:
		{
			DUMP("                  NUM");
			DUMP("%18.2lf", node->value.num_value);
			break;
		}
		case OP:
		{
			DUMP("                  OP");

			#define CASE(OP_TYPE)\
			case OP_TYPE:\
			{\
				DUMP("                  "#OP_TYPE);\
				break;\
			}

			switch(node->value.op_value)
			{
				CASE(ADD)
				CASE(SUB)
				CASE(MUL)
				CASE(DIV)
				CASE(POW)
				CASE(DO_NOTHING)
				default:
				{
					DUMP("UNKNOWN");
				}
			}

			#undef CASE
			break;
		}
		case VAR:
		{
			DUMP("                  VAR");
			DUMP("                  %s", node->value.var_value);
			break;
		}
		default:
		{
			DUMP("UNKNOWN");
		}
	}

	DUMP("%18.p", node->left);
	DUMP("%18.p", node->right);

	DUMP("\n");

	node_consoole_dump(node->left,  console_dump_file);
	node_consoole_dump(node->right, console_dump_file);
}
