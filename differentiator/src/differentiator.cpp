#include <math.h>

#include "differentiator.h"
#include "differentiator_secondary.h"
#include "def_DSL.h"

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

	btr_elem_t left_node_value  = eval(node->left, labels_w_len);
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
		case LN:
		{
			return log(right_node_value);
		}
		case SIN:
		{
			return sin(right_node_value);
		}
		case COS:
		{
			return cos(right_node_value);
		}
		case SQRT:
		{
			return sqrt(right_node_value);
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

Uni_ret create_txt_expression(struct B_tree_node *root, const char *file_name)
{
	Uni_ret result =
	{
		.error_code = ALL_GOOD,
		.arg.file_ptr = fopen(file_name, "w"),
	};

	if(result.arg.file_ptr == NULL)
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

	print_node(&fictitious_root_parent, RIGHT_CHILD, result.arg.file_ptr);

	fclose(result.arg.file_ptr);

	return result;
}

Uni_ret create_tex_expression(struct B_tree_node *root, const char *file_name)
{
	Uni_ret result =
	{
		.error_code = ALL_GOOD,
		.arg.file_ptr = fopen(file_name, "w"),
	};

	if(result.arg.file_ptr == NULL)
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

	fprintf(result.arg.file_ptr, "$$ ");

	tex_node_print(&fictitious_root_parent, RIGHT_CHILD, result.arg.file_ptr);

	fprintf(result.arg.file_ptr, " $$");

	fclose(result.arg.file_ptr);

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
			return ZERO;
			break;
		}
		case VAR:
		{
			return ONE;
			break;
		}
		case OP:
		{
			switch(node->value.op_value)
			{
				case ADD:
				{
					return ADD(dL, dR);
				}
				case SUB:
				{
					return SUB(dL, dR);
				}
				case MUL:
				{
					return ADD(MUL(dL, cR), MUL(cL, dR));
				}
				case DIV:
				{
					return DIV(SUB(MUL(dL, cR), MUL(cL, dR)), POW(cR, TWO));
				}
				case POW:
				{
					B_tree_node *left_child  = MUL(MUL(cR, POW(cL, SUB(cR, ONE))), dL);
					B_tree_node *right_child = MUL(MUL(POW(cL, cR), LN(cL)), dR);

					return ADD(left_child, right_child);
				}
				case LN:
				{
					return MUL(DIV(ONE, cR), dR);
				}
				case SIN:
				{
					return MUL(COS(cR), dR);
				}
				case COS:
				{
					return MUL(SUB(ZERO, SIN(cR)), dR);
				}
				case SQRT:
				{
					return MUL(DIV(ONE, MUL(TWO, SQRT(cR))), dR);
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

struct B_tree_node *node_copy(struct B_tree_node *node)
{
	if(node == NULL)
	{
		return NULL;
	}

	struct B_tree_node *copy = (struct B_tree_node *)calloc(1, sizeof(struct B_tree_node));

	if(copy == NULL)
	{
		fprintf(stderr, "Unable to allocate memory in %s", __func__);
		return NULL;
	}

	copy->left = node_copy(node->left);
	copy->right = node_copy(node->right);
	copy->type = node->type;
	copy->value = node->value;

	return copy;
}

static bool change_flag = false;
static bool non_trivial_flag = false;

B_tree_node *wrap_consts(B_tree_node *node)
{
	change_flag = false;

	if(node == NULL)
	{
		return NULL;
	}

	if(node->left == NULL || node->right == NULL)
	{
		return node;
	}

	if(node->left->type == NUM && node->right->type == NUM)
	{
		btr_elem_t result = eval(node, NULL);

		change_flag = true;

		return create_node(NUM, {.num_value = result}, NULL, NULL).arg.node;
	}
	else
	{
		return node;
	}
}

B_tree_node *solve_trivial(B_tree_node *node)
{
	change_flag      = false;
	non_trivial_flag = false;

	if(node == NULL)
	{
		return NULL;
	}

	if(node->left == NULL || node->right == NULL)
	{
		return node;
	}

	if(node->left->type == NUM && cmp_double(node->left->value.num_value, 0) == 0)
	{
		if(	(node->type == OP) &&
			(	(node->value.op_value == MUL)	||
				(node->value.op_value == DIV)	||
				(node->value.op_value == POW)	)	)
		{
			change_flag = true;
			return ZERO;
		}
		else if(node->type == OP && node->value.op_value == ADD)
		{
			change_flag      = true;
			non_trivial_flag = true;
			return node->right; // might be simplified further
		}
	}
	else if(node->right->type == NUM && cmp_double(node->right->value.num_value, 0) == 0)
	{
		if(node->type == OP && node->value.op_value == MUL)
		{
			change_flag = true;
			return ZERO;
		}
		else if(node->type == OP && node->value.op_value == POW)
		{
			change_flag = true;
			return ONE;
		}
		else if	(	(node->type == OP) &&
					(node->value.op_value == DIV)	)
		{
			change_flag = true;
			return create_node(NUM, {.num_value = NAN}, NULL, NULL).arg.node;
		}
		else if(	(node->type == OP) &&
					(	(node->value.op_value == ADD)	||
						(node->value.op_value == SUB)	)	)
		{
			change_flag      = true;
			non_trivial_flag = true;
			return node->left; // might be simplified further
		}
	}
	else if(node->left->type == NUM && cmp_double(node->left->value.num_value, 1) == 0)
	{
		if(node->type == OP && node->value.op_value == MUL)
		{
			change_flag      = true;
			non_trivial_flag = true;
			return node->right;	// might be simplified further
		}
		else if(node->type == OP && node->value.op_value == POW)
		{
			change_flag = true;
			return ONE;
		}
	}
	else if(node->right->type == NUM && cmp_double(node->right->value.num_value, 1) == 0)
	{
		if(	(node->type == OP) &&
			(	(node->value.op_value == MUL) ||
				(node->value.op_value == POW) ||
				(node->value.op_value == DIV)	)	)
		{
			change_flag      = true;
			non_trivial_flag = true;
			return node->left;	// might be simplified further
		}
	}
	else if(	(node->left->type == VAR) &&
				(node->right->type == VAR) &&
				(node->type == OP && node->value.op_value == SUB) &&
				(!strncmp(LEFT_VAR, RIGHT_VAR, MAX_VAR_LEN))	)
	{
		change_flag = true;
		return ZERO;
	}


	return node;
}

#define TRY_TO_SIMPLIFY					\
	if(node == NULL)					\
	{									\
		return NULL;					\
	}									\
										\
	simple_node = wrap_consts(node);	\
	if(change_flag == true)				\
	{									\
		return simple_node;				\
	}									\
										\
	simple_node = solve_trivial(node);	\
	if(non_trivial_flag == true)\
	{									\
		return simplify(simple_node);	\
	}									\
										\
	if(change_flag == true)				\
	{									\
		return simple_node;				\
	}

B_tree_node *simplify(B_tree_node *node)
{
	B_tree_node *simple_node = NULL;

	TRY_TO_SIMPLIFY;

	node->left  = simplify(node->left);
	node->right = simplify(node->right);

	TRY_TO_SIMPLIFY;

	return node;
}

#undef TRY_TO_SIMPLIFY


#include "undef_DSL.h"
