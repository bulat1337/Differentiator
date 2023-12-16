#include <math.h>

#include "differentiator.h"
#include "differentiator_secondary.h"

btr_elem_t eval(struct B_tree_node *node, struct Labels_w_len *labels_w_len)
{
	if(node == NULL)
	{
		return NAN;
	}

	if(node->type == NUM)
	{
		return node->value.num_value;
	}

	if(node->type == VAR)
	{
		return get_var_value(node->value.var_value, labels_w_len);
	}

	btr_elem_t left_node_value = eval(node->left, labels_w_len);
	btr_elem_t right_node_value = eval(node->right, labels_w_len);

	switch(node->value.op_value)
	{
		case ADD:
		{
			return left_node_value + right_node_value;
			break;
		}
		case SUB:
		{
			return left_node_value - right_node_value;
			break;
		}
		case MUL:
		{
			return left_node_value * right_node_value;
			break;
		}
		case DIV:
		{
			if(cmp_double(right_node_value, 0) == 0)
			{
				return NAN;
			}

			return left_node_value / right_node_value;

			break;
		}
		case POW:
		{
			return pow(left_node_value, right_node_value);
		}
		case DO_NOTHING:
		{
			return NAN;
			break;
		}
		default:
		{
			return NAN;
		}

	}

}

struct Create_expression_result create_txt_expression(struct B_tree_node *root,
													  const char *file_name)
{
	struct Create_expression_result result=
	{
		.error_code = ALL_GOOD,
		.expression = fopen(file_name, "w"),
	};

	if(result.expression == NULL)
	{
		perror("ERROR:");
		result.error_code = UNABLE_TO_OPEN_FILE;

		return result;
	}

	struct B_tree_node fictitious_root_parent =
	{
		.type = OP,
		.value.op_value = DO_NOTHING,
		.left = root,
		.right = root,
	};

	print_node(&fictitious_root_parent, true, result.expression);

	fclose(result.expression);

	return result;
}

struct Create_expression_result create_tex_expression(struct B_tree_node *root,
													  const char *file_name)
{
	struct Create_expression_result result=
	{
		.error_code = ALL_GOOD,
		.expression = fopen(file_name, "w"),
	};

	if(result.expression == NULL)
	{
		perror("ERROR:");
		result.error_code = UNABLE_TO_OPEN_FILE;

		return result;
	}

	struct B_tree_node fictitious_root_parent =
	{
		.type = OP,
		.value.op_value = DO_NOTHING,
		.left = root,
		.right = root,
	};

	fprintf(result.expression, "$$ ");

	tex_node_print(&fictitious_root_parent, true, result.expression);

	fprintf(result.expression, " $$");

	fclose(result.expression);

	return result;
}

struct B_tree_node *differentiate(struct B_tree_node *node)
{
	if(node == NULL)
	{
		fprintf(stderr, "NODE_NULL_PTR\n");
		return NULL;
	}

	switch(node->type)
	{
		case NUM:
		{
			return create_node(NUM, {.num_value = 0}, NULL, NULL).new_node;
			break;
		}
		case VAR:
		{
			return create_node(NUM, {.num_value = 1}, NULL, NULL).new_node;
			break;
		}
		case OP:
		{
			switch(node->value.op_value)
			{
				case ADD:
				{
					return create_node(OP, {.op_value = ADD},
						differentiate(node->left), differentiate(node->right)).new_node;
					break;
				}
				case SUB:
				{
					return create_node(OP, {.op_value = SUB},
						differentiate(node->left), differentiate(node->right)).new_node;
					break;
				}
				case MUL:
				{
					struct B_tree_node *left_node =
						create_node(OP, {.op_value = MUL},
									differentiate(node->left), node_copy(node->right)).new_node;
					struct B_tree_node *right_node =
						create_node(OP, {.op_value = MUL},
									node_copy(node->left), differentiate(node->right)).new_node;
					return create_node(OP, {.op_value = ADD}, left_node, right_node).new_node;
					break;
				}
				case DIV:
				{
					struct B_tree_node *left_of_the_left_node =
						create_node(OP, {.op_value = MUL},
									differentiate(node->left), node_copy(node->right)).new_node;
					struct B_tree_node *right_of_the_left_node =
						create_node(OP, {.op_value = MUL},
									node_copy(node->left), differentiate(node->right)).new_node;
					struct B_tree_node *left_node  =
						create_node(OP, {.op_value = SUB},
									left_of_the_left_node, right_of_the_left_node).new_node;
					struct B_tree_node *right_node =
						create_node(OP, {.op_value = POW},
									node->right,
									create_node(NUM, {.num_value = 2}, NULL, NULL).new_node).new_node;
					return create_node(OP, {.op_value = DIV}, left_node, right_node).new_node;
					break;
				}
				case POW:
				{
					exit(EXIT_FAILURE);
				}
				case DO_NOTHING:
				{
					exit(EXIT_FAILURE);
				}
				default:
				{
					exit(EXIT_FAILURE);
				}
			}
		}
		default:
		{
			fprintf(stderr, "Unknown node type %d\n", node->type);
			return NULL;
		}
	}
}
