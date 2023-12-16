#include "differentiator.h"
#include "differentiator_secondary.h"

#define PUT_PARENTHESIS_COND\
	  !((node->type == NUM) || 															\
	  	(node->type == VAR) ||		 													\
	   ((parent->type == OP) &&															\
	        ((parent->value.op_value == ADD) || (parent->value.op_value == SUB))		\
			&& (node->type == OP) &&													\
			((node->value.op_value == MUL) ||											\
				(node->value.op_value == DIV) ||										\
				(node->value.op_value == POW))) ||										\
		((parent->type == OP) && (parent->value.op_value == DO_NOTHING)))				\

#define PUT_PARENTHESIS_COND_TEX\
	  !((node->type == NUM) || 															\
	  	(node->type == VAR) ||		 													\
	   ((parent->type == OP) &&															\
	        ((parent->value.op_value == ADD) || (parent->value.op_value == SUB))		\
			&& (node->type == OP) &&													\
			((node->value.op_value == MUL) ||											\
				(node->value.op_value == DIV) ||										\
				(node->value.op_value == POW))) ||										\
		((parent->type == OP) && (parent->value.op_value == DO_NOTHING)) ||				\
		((parent->type == OP) && (parent->value.op_value == POW)) ||					\
		((parent->type == OP) && (parent->value.op_value == DIV)))						\

int cmp_double(double first_double, double second_double)
{
    const double eps = 1e-7;

    if(isnan(first_double) && isnan(second_double))
    {
        return 0;
    }
    if (fabs(first_double - second_double) < eps)
    {
        return 0;
    }
    else if ((first_double - second_double) > eps)
    {
        return 1;
    }
    else
    {
        return -1;
    }
}

void print_node(struct B_tree_node *parent, bool is_right_child, FILE *expression)
{
	#define WRITE_IN_EXPRESSION_FILE(...) fprintf(expression, __VA_ARGS__);

	struct B_tree_node *node = get_node(parent, is_right_child);

    if(node == NULL)
    {
        return;
    }

	if(PUT_PARENTHESIS_COND)
	{
    	WRITE_IN_EXPRESSION_FILE("( ");
	}
	print_node(node, false, expression);

	switch(node->type)
	{
		case OP:
		{
			switch(node->value.op_value)
			{
				case ADD:
				{
					WRITE_IN_EXPRESSION_FILE("+ ");
					break;
				}
				case SUB:
				{
					WRITE_IN_EXPRESSION_FILE("- ");
					break;
				}
				case MUL:
				{
					WRITE_IN_EXPRESSION_FILE("* ");
					break;
				}
				case DIV:
				{
					WRITE_IN_EXPRESSION_FILE("/ ");
					break;
				}
				case POW:
				{
					WRITE_IN_EXPRESSION_FILE("^");
					break;
				}
				case DO_NOTHING:
				{
					;
				}
				default:
				{
					fprintf(stderr, "Unknown operation in %s[%d]\n", __func__, __LINE__);
				}
			}

			break;
		}
		case NUM:
		{
			WRITE_IN_EXPRESSION_FILE("%lf ", node->value.num_value);
			break;
		}
		case VAR:
		{
			WRITE_IN_EXPRESSION_FILE("%s ", node->value.var_value);
			break;
		}
		default:
		{
			fprintf(stderr, "Unknown value_type in %s[%d]\n", __func__, __LINE__);
		}
	}

    print_node(node, true, expression);

   	if(PUT_PARENTHESIS_COND)
	{
    	WRITE_IN_EXPRESSION_FILE(") ");
	}

	#undef WRITE_IN_EXPRESSION_FILE
}

struct B_tree_node *get_node(struct B_tree_node *parent, bool is_right_child)
{
	if(is_right_child)
	{
		return parent->right;
	}
	{
		return parent->left;
	}
}

void tex_node_print(struct B_tree_node *parent, bool is_right_child, FILE *expression)
{
	#define WRITE_IN_EXPRESSION_FILE(...) fprintf(expression, __VA_ARGS__);

	struct B_tree_node *node = get_node(parent, is_right_child);

    if(node == NULL)
    {
        return;
    }

	if(PUT_PARENTHESIS_COND_TEX)
	{
    	WRITE_IN_EXPRESSION_FILE("(");
	}

	if((parent->type == OP) && (parent->value.op_value == POW))
	{
		WRITE_IN_EXPRESSION_FILE("{");
	}

	if(!((node->type == OP) && (node->value.op_value == DIV)))
	{
		tex_node_print(node, false, expression);
	}

	switch(node->type)
	{
		case OP:
		{
			switch(node->value.op_value)
			{
				case ADD:
				{
					WRITE_IN_EXPRESSION_FILE("+");
					break;
				}
				case SUB:
				{
					WRITE_IN_EXPRESSION_FILE("-");
					break;
				}
				case MUL:
				{
					WRITE_IN_EXPRESSION_FILE("*");
					break;
				}
				case DIV:
				{
					WRITE_IN_EXPRESSION_FILE("\\frac");
					break;
				}
				case POW:
				{
					WRITE_IN_EXPRESSION_FILE("^");
					break;
				}
				case DO_NOTHING:
				{
					break;
				}
				default:
				{
					fprintf(stderr, "Unknown operation in %s[%d]\n", __func__, __LINE__);
				}
			}

			break;
		}
		case NUM:
		{
			WRITE_IN_EXPRESSION_FILE("{%.2lf}", node->value.num_value);
			break;
		}
		case VAR:
		{
			WRITE_IN_EXPRESSION_FILE("{%s}", node->value.var_value);
			break;
		}
		default:
		{
			fprintf(stderr, "Unknown value_type in %s[%d]\n", __func__, __LINE__);
		}
	}

	if((node->type == OP) && (node->value.op_value == DIV))
	{
		WRITE_IN_EXPRESSION_FILE("{");
		tex_node_print(node, false, expression);
		WRITE_IN_EXPRESSION_FILE("}");

		WRITE_IN_EXPRESSION_FILE("{");
		tex_node_print(node, true, expression);
		WRITE_IN_EXPRESSION_FILE("}");
	}
	else
	{
    	tex_node_print(node, true, expression);
	}


	if(PUT_PARENTHESIS_COND_TEX)
	{
    	WRITE_IN_EXPRESSION_FILE(")");
	}

	if((parent->type == OP) && (parent->value.op_value == POW))
	{
		WRITE_IN_EXPRESSION_FILE("}");
	}

	#undef WRITE_IN_EXPRESSION_FILE
}

btr_elem_t get_var_value(const char *var_name, const struct Labels_w_len *labels_w_len)
{
	for(size_t label_ID = 0; label_ID < labels_w_len->length; label_ID++)
	{
		if(!strncmp(var_name, labels_w_len->labels[label_ID].name, strlen(var_name)))
		{
			return labels_w_len->labels[label_ID].value;
		}
	}

	return NAN;
}

struct B_tree_node *node_copy(struct B_tree_node *node)
{
	struct B_tree_node *copy = (struct B_tree_node *)calloc(1, sizeof(struct B_tree_node));

	if(copy == NULL)
	{
		fprintf(stderr, "Unable to allocate memory in %s", __func__);
		return NULL;
	}

	copy->left = node->left;
	copy->right = node->right;
	copy->type = node->type;
	copy->value = node->value;

	return copy;
}
