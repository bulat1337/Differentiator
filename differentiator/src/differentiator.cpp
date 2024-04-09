#include <math.h>

#include "differentiator.h"
#include "differentiator_secondary.h"

#include "def_DSL.h"

Notations notations = {};

#define FILE_PTR_CHECK(ptr)								\
	{													\
		if(ptr == NULL)									\
		{												\
			fprintf(stderr, "Unable to open"#ptr"\n");	\
														\
			result.arg.node   = NULL;					\
			result.error_code = UNABLE_TO_OPEN_FILE;	\
														\
			return result;								\
		}												\
	}

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

Uni_ret diff_exp(B_tree_node *root, const char *name)
{
	Uni_ret result =
	{
		.error_code = ALL_GOOD,
	};

	char *file_name = create_file_name(name, "_diff.tex");

	WITH_OPEN
	(
		file_name, "w", tex_file,

		init_notations();

		result.arg.node = differentiate(root, tex_file);

		tex_notations(tex_file);

		notations_dtor();
	)

	return result;
}

Uni_ret tex_exp(B_tree_node *root, const char *name)
{
	Uni_ret result =
	{
		.error_code = ALL_GOOD,
	};

	char *file_name = create_file_name(name, ".tex");

	WITH_OPEN
	(
		file_name, "w", tex_file,

		init_notations();

		manage_notations(root);

		TEX("$$");
		create_tex_expression(root, tex_file, true);
		TEX("$$");

		tex_notations(tex_file);

		notations_dtor();
	)

	return result;
}

Uni_ret simpl_exp(B_tree_node *root, const char *name)
{
	Uni_ret result =
	{
		.error_code = ALL_GOOD,
	};

	char *file_name = create_file_name(name, "_simpl.tex");

	WITH_OPEN
	(
		file_name, "w", tex_file,

		init_notations();

		result.arg.node = simplify(root, tex_file);

		tex_notations(tex_file);

		notations_dtor();
	)

	return result;
}


#include "undef_DSL.h"
