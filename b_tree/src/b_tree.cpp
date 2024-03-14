#include "b_tree.h"
#include "b_tree_secondary.h"

Uni_ret create_node(Node_type type, Node_value value, B_tree_node *left_child,
													  B_tree_node *right_child)
{
	Uni_ret result =
	{
		.arg.node = allocate_node_memory(),
		.error_code = ALL_GOOD,
	};

	if(result.arg.node == NULL)
	{
		result.error_code = UNABLE_TO_ALLOCATE;
		return result;
	}

	result.arg.node->type  = type;

	result.arg.node->left  = left_child;
	result.arg.node->right = right_child;

	switch(type)
	{
		case NUM:
		{
			result.arg.node->value.num_value = value.num_value;
			break;
		}
		case OP:
		{
			result.arg.node->value.op_value  = value.op_value;
			break;
		}
		case VAR:
		{
			result.arg.node->value.var_value = value.var_value;
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
		parent->left  = child;
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

Uni_ret gr_dump_code_gen(B_tree_node *root, const char *b_tree_name)
{
	Uni_ret result =
	{
		.error_code   = ALL_GOOD,
		.arg.file_ptr = fopen(b_tree_name, "w"),
	};

	if(result.arg.file_ptr == NULL) //macro + stderr -> log_file
	{
		fprintf(stderr, "Unable to open list_graphic_dump.dot\n");

		result.error_code = UNABLE_TO_OPEN_FILE;
		return result;
	}

	#define WRITE_TO_DUMP_FILE(...) fprintf(result.arg.file_ptr, __VA_ARGS__);

	WRITE_TO_DUMP_FILE("digraph BinaryTree {\n"
	"bgcolor = \"%s\";\n"
	"edge[minlen = 3, penwidth = 3; color = \"black\"];\n"
	"node[shape = \"rectangle\", style = \"rounded, filled\",\n"
	"\tfillcolor = \"%s\",\n"
	"\tfontsize = 30,\n"
	"\theight = 3,\n"
	"\tpenwidth = 5, color = \"white\"];\n", MARGENGO, CORAL_PINK);

	struct Node_charachteristics nd_description =
	{
		.color = CORAL_PINK,
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
    	"\tlist_manager [shape = Mrecord, fillcolor = \"%s\", "
		"label = \"{ROOT: %p}\"];\n"
	"}\n", LIGHT_GREEN, root);

	if(root != NULL)
	{
		result.error_code = print_regular_nodes(root, &nd_description, result.arg.file_ptr);

		if(result.error_code != ALL_GOOD)
		{
			free(nd_description.label);
			fclose(result.arg.file_ptr);

			return result;
		}
	}

	gr_dump_connect_nodes(root, result.arg.file_ptr);

	WRITE_TO_DUMP_FILE("}");


//why donesn't work \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	// char *gr_dump_gen_cmd = (char *)calloc(GR_DUMP_GEN_CMD_SIZE, sizeof(char));
	// if(gr_dump_gen_cmd == NULL)
	// {
	// 	result.error_code = UNABLE_TO_ALLOCATE;
	// 	fprintf(stderr, "Unable to allocate\n");
	// 	return result;
	// }
	// snprintf(gr_dump_gen_cmd, GR_DUMP_GEN_CMD_SIZE,
	// 	"dot -Tpng %s -o %s.png -Gdpi=100", b_tree_name, b_tree_name);
	// system(gr_dump_gen_cmd);
	// free(gr_dump_gen_cmd);



	#undef WRITE_TO_DUMP_FILE

	free(nd_description.label);
	fclose(result.arg.file_ptr);

	return result;
}

error_t txt_dump(struct B_tree_node *root, const char *name)
{
	#define DUMP(...) fprintf(dump_file, __VA_ARGS__);

	char *file_name = create_file_name(name, "dump.txt");

	FILE *dump_file = fopen(file_name, "w");
	free(file_name);
	if(dump_file == NULL)
	{
		return UNABLE_TO_OPEN_FILE;
	}

	DUMP("address:");
	DUMP("             type:");
	DUMP("             value:");
	DUMP("             left:");
	DUMP("             right:\n");

	txt_dump_node(root, dump_file);

	#undef DUMP

	return ALL_GOOD;
}

// struct Construct_b_tree_result construct_b_tree(const char *data_base_file_name)
// {
// 	WRITE_IN_LOG_FILE("construct_b_tree log:\n");
// 	Construct_b_tree_result result =
// 	{
// 		.error_code = ALL_GOOD,
// 	};
//
// 	FILE *data_base = fopen(data_base_file_name, "r");
// 	if (data_base == NULL)
// 	{
// 		fprintf(stderr, "I cant open ur data base(%s)!\n", data_base_file_name);
// 		result.error_code = AKI_UNABLE_TO_OPEN_FILE;
//
// 		return result;
// 	}
//
// 	struct Buf_w_carriage_n_len data_base_buf_w_info = {};
//
// 	data_base_buf_w_info.length = get_file_length(data_base);
// 	data_base_buf_w_info.buf = (char *)calloc(data_base_buf_w_info.length, sizeof(char));
// 	if(data_base_buf_w_info.buf == NULL)
// 	{
// 		perror("ERROR:");
// 		result.error_code = UNABLE_TO_ALLOCATE;
// 		return result;
// 	}
//
// 	size_t read_elems_amount =
// 		fread(data_base_buf_w_info.buf, sizeof(char), data_base_buf_w_info.length, data_base);
// 	if(read_elems_amount != data_base_buf_w_info.length)
// 	{
// 		if(ferror(data_base))
// 		{
// 			perror("ERROR:");
//
// 			result.error_code = UNEXPECTED_WRITTEN_ELEMS;
//
// 			return result;
// 		}
// 		else if(feof(data_base))
// 		{
// 			fprintf(stderr ,
// 			"read_elems_amount != data_base_buf_w_info.length because end of the file "
// 			"EOF was reached.\n");
// 		}
// 	}
//
// 	size_t amount_of_lexems = count_buf_lexemes(data_base_buf_w_info);
// 	struct Lexemes_w_carriage data_base_lexemes =
// 	{
// 		.buf = (char * *)calloc(amount_of_lexems, sizeof(char *)),
// 		.carriage = 0,
// 	};
//
// 	if(data_base_lexemes.buf == NULL)
// 	{
// 		perror("ERROR:");
// 		result.error_code = UNABLE_TO_ALLOCATE;
// 		return result;
// 	}
//
// 	lexemes_ptr_arranger(data_base_lexemes.buf, data_base_buf_w_info);
//
// 	size_t amount_of_nodes = get_amount_of_nodes(data_base_lexemes.buf, amount_of_lexems);
//
//
//
// 	result.btr = b_tree_ctor(amount_of_nodes + SPACE_FOR_NEW_NODES).new_btr;
//
// 	int current_node_ID = 0;
// 	result.btr->root = &(result.btr->node[current_node_ID]);
// 	result.btr->capacity = amount_of_nodes + SPACE_FOR_NEW_NODES;
// 	read_node(&data_base_lexemes, &(current_node_ID), result.btr->node);
//
// 	result.btr->current_free = &(result.btr->node[current_node_ID + 1]);
//
// 	free(data_base_lexemes.buf);
// 	free(data_base_buf_w_info.buf);
//
// 	fclose(data_base);
//
// 	return result;
// }


