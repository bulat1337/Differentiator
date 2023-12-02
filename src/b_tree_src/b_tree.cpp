#include "b_tree.h"
#include "b_tree_secondary.h"

struct Create_node_result create_node(enum Node_type type, union Node_value value)
{
	struct Create_node_result result =
	{
		.new_node = allocate_memory(),
		.error_code = ALL_GOOD,
	};

	if(result.new_node == NULL)
	{
		result.error_code = UNABLE_TO_ALLOCATE;
		return result;
	}

	result.new_node->type = type;

	result.new_node->left  = NULL;
	result.new_node->right = NULL;

	switch(type)
	{
		case NUM:
		{
			result.new_node->value.num_value = value.num_value;
			break;
		}
		case OP:
		{
			result.new_node->value.op_value = value.op_value;
			break;
		}
		default:
		{
			result.error_code = UNKNOWN_NODE_TYPE;
			return result;
		}
	}

	return result;
}

error_t add_child(struct B_tree_node *parent, struct B_tree_node *child, bool is_right_child)
{
	if(parent == NULL || child == NULL)
	{
		return B_TREE_NODE_NULL_PTR;
	}

	if(is_right_child)
	{
		parent->right = child;
	}
	else
	{
		parent->left = child;
	}

	return ALL_GOOD;
}

error_t destroy_subtree(struct B_tree_node *parent_node, bool is_right_child)
{
	if(parent_node == NULL)
	{
		return PARENT_NODE_IS_FREE;
	}

	if(is_right_child)
	{
		node_delete(parent_node->right);
		parent_node->right = NULL;
	}
	else
	{
		node_delete(parent_node->left);
		parent_node->left = NULL;
	}



	return ALL_GOOD;
}

struct Gr_dump_code_gen_result gr_dump_code_gen(struct B_tree_node *root)
{
	struct Gr_dump_code_gen_result result =
	{
		.error_code = ALL_GOOD,
		.graphic_dump_code_file_ptr = fopen("b_tree_graphic_dump.dot", "w"),
	};

	if(result.graphic_dump_code_file_ptr == NULL)
	{
		fprintf(stderr, "Unable to open list_graphic_dump.dot\n");

		result.error_code = UNABLE_TO_OPEN_FILE;
		return result;
	}

	#define WRITE_TO_DUMP_FILE(...) fprintf(result.graphic_dump_code_file_ptr, __VA_ARGS__);

	WRITE_TO_DUMP_FILE("digraph BinaryTree {\n"
	"bgcolor = \"#48565D\";\n"
	"edge[minlen = 3, penwidth = 3; color = \"black\"];\n"
	"node[shape = \"rectangle\", style = \"rounded, filled\",\n"
	"\tfillcolor = \"#F08080\",\n"
	"\tfontsize = 30,\n"
	"\theight = 3,\n"
	"\tpenwidth = 5, color = \"#FFFFFF\"];\n");

	struct node_charachteristics nd_description =
	{
		.color = "#F08080",
		.name = "node_",
	};

	nd_description.label = (char *)calloc((NODE_LABEL_STR_SIZE), sizeof(char));
	if(nd_description.label == NULL)
	{
		fprintf(stderr, "Unable to allocate nd_description.label\n");
		result.error_code = UNABLE_TO_ALLOCATE;
		return result;
	}

	//	print_list_manager
	WRITE_TO_DUMP_FILE("{rank = min;\n"
    	"\tlist_manager [shape = Mrecord, fillcolor = \"#D7FF25\", "
		"label = \"{ROOT: %p}\"];\n"
	"}\n", root);

	if(root != NULL)
	{
		print_regular_nodes(root,
							&nd_description,
							result.graphic_dump_code_file_ptr);
	}

	connect_nodes(root, result.graphic_dump_code_file_ptr);

	WRITE_TO_DUMP_FILE("}");

	#undef WRITE_TO_DUMP_FILE

	free(nd_description.label);
	fclose(result.graphic_dump_code_file_ptr);

	return result;
}
