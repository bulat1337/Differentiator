#include "differentiator.h"
#include "differentiator_secondary.h"
#include "def_DSL.h"

#define PUT_PARENTHESIS_COND\
		(	(parent->type == OP) &&														\
			(	(parent->value.op_value == LN) ||										\
				(parent->value.op_value == SIN) ||										\
				(parent->value.op_value == SQRT) ||										\
				(parent->value.op_value == COS)	)	) ||								\
		!(	(node->type == NUM) || 														\
	  		(node->type == VAR) ||		 												\
	    	(	(	(node->type == OP) &&												\
						(	(node->value.op_value == MUL) ||							\
							(node->value.op_value == POW) ||							\
							(node->value.op_value == DIV)	)	) &&					\
					!(	(parent->type == OP) &&											\
						(parent->value.op_value == POW)	)	) ||						\
	    	(	(node->type == OP) &&													\
				(	(node->value.op_value == LN) ||										\
					(node->value.op_value == SIN) ||									\
					(node->value.op_value == SQRT) ||									\
					(node->value.op_value == COS)	)	) ||							\
			(	(parent->type == OP) && (parent->value.op_value == DO_NOTHING)	)	)	\

#define PUT_PARENTHESIS_COND_TEX\
		(	(parent->type == OP) &&														\
			(	(parent->value.op_value == LN) ||										\
				(parent->value.op_value == SIN) ||										\
				(parent->value.op_value == COS)	)	) ||								\
	  	!(	(node->type == NUM) || 														\
	  		(node->type == VAR) ||		 												\
	  		(	(parent->type == OP) &&													\
				(parent->value.op_value == POW) &&										\
				!(node->value.op_value == POW)	) ||		 							\
	   		(	(node->type == OP) &&													\
				(	(node->value.op_value == MUL) ||									\
					(node->value.op_value == DIV) ||									\
					(node->value.op_value == LN) ||										\
					(node->value.op_value == SQRT) ||									\
					(node->value.op_value == SIN) ||									\
					(node->value.op_value == COS) ||									\
					(	(node->value.op_value == POW) &&								\
						!(parent->value.op_value == POW)	)	)	) ||				\
			(	(parent->type == OP) && (parent->value.op_value == DO_NOTHING)	)	)	\

void print_node(struct B_tree_node *parent, bool is_right_child, FILE *expression_file)
{
	#define WRITE_IN_EXPRESSION_FILE(...) fprintf(expression_file, __VA_ARGS__);

	struct B_tree_node *node = get_node(parent, is_right_child);

    if(node == NULL)
    {
        return;
    }

	if(PUT_PARENTHESIS_COND)
	{
    	WRITE_IN_EXPRESSION_FILE("( ");
	}

	print_node(node, LEFT_CHILD, expression_file);

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
					WRITE_IN_EXPRESSION_FILE("^ ");
					break;
				}
				case LN:
				{
					WRITE_IN_EXPRESSION_FILE("ln");
					break;
				}
				case SIN:
				{
					WRITE_IN_EXPRESSION_FILE("sin");
					break;
				}
				case COS:
				{
					WRITE_IN_EXPRESSION_FILE("cos");
					break;
				}
				case SQRT:
				{
					WRITE_IN_EXPRESSION_FILE("sqrt");
					break;
				}
				case DO_NOTHING:
				{
					;
				}
				default:
				{
					fprintf(stderr, "Unknown operation %d in %s[%d]\n",
							node->value.op_value, __func__, __LINE__);
				}
			}

			break;
		}
		case NUM:
		{
			WRITE_IN_EXPRESSION_FILE("%.2lf ", node->value.num_value);
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

    print_node(node, RIGHT_CHILD, expression_file);

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

void tex_node_print(struct B_tree_node *parent, bool is_right_child,
					FILE *expression, bool do_var_rep)
{
	#define WRITE_IN_EXPRESSION_FILE(...) fprintf(expression, __VA_ARGS__);

	struct B_tree_node *node = get_node(parent, is_right_child);

    if(node == NULL)
    {
        return;
    }

	if(do_var_rep)
	{
		//get node size
		size_t node_size = get_node_size(node);

		//check if notation already exists
		Notat_check check = check_if_notated(node);
		if(check.notated)
		{
			WRITE_IN_EXPRESSION_FILE("%c", check.letter);

			return;
		}

		//decide if the temp variable is needed
		if(node_size > NOTAT_BOUND)
		{
			char notation = set_notation(node);

			printf("cause node_size = %lu\n", node_size);

			WRITE_IN_EXPRESSION_FILE("%c", notation)

			return;
		}
	}

	if(PUT_PARENTHESIS_COND_TEX)
	{
    	WRITE_IN_EXPRESSION_FILE("(");
	}

	if(	(parent->type == OP) &&
		(	(parent->value.op_value == POW) ||
			(parent->value.op_value == SQRT)	)	)
	{
		WRITE_IN_EXPRESSION_FILE("{");
	}

	if(	!(	(node->type == OP) && (node->value.op_value == DIV)	)	)
	{
		tex_node_print(node, LEFT_CHILD, expression, true);
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
				case LN:
				{
					WRITE_IN_EXPRESSION_FILE("\\ln");
					break;
				}
				case SIN:
				{
					WRITE_IN_EXPRESSION_FILE("\\sin");
					break;
				}
				case COS:
				{
					WRITE_IN_EXPRESSION_FILE("\\cos");
					break;
				}
				case SQRT:
				{
					WRITE_IN_EXPRESSION_FILE("\\sqrt");
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

	if(	(	(node->type == OP) && (node->value.op_value == DIV)	)	)
	{
		WRITE_IN_EXPRESSION_FILE("{");
		tex_node_print(node, LEFT_CHILD, expression, true);
		WRITE_IN_EXPRESSION_FILE("}");

		WRITE_IN_EXPRESSION_FILE("{");
		tex_node_print(node, RIGHT_CHILD, expression, true);
		WRITE_IN_EXPRESSION_FILE("}");
	}
	else
	{
    	tex_node_print(node, RIGHT_CHILD, expression, true);
	}

	if(	(parent->type == OP) &&
		(	(parent->value.op_value == POW) ||
			(parent->value.op_value == SQRT)	)	)
	{
		WRITE_IN_EXPRESSION_FILE("}");
	}

	if(PUT_PARENTHESIS_COND_TEX)
	{
    	WRITE_IN_EXPRESSION_FILE(")");
	}

	#undef WRITE_IN_EXPRESSION_FILE
}

btr_elem_t get_var_value(const char *var_name, const struct Labels_w_len *labels_w_len)
{
	if(labels_w_len == NULL)
	{
		return NAN;
	}
	for(size_t label_ID = 0; label_ID < labels_w_len->length; label_ID++)
	{
		if(!strncmp(var_name, labels_w_len->labels[label_ID].name, strlen(var_name)))
		{
			return labels_w_len->labels[label_ID].value;
		}
	}

	return NAN;
}

error_t tex_src_diff_node(FILE *tex_file, B_tree_node *node)
{
	TEX("Let's solve:\n");
	TEX("$$ d(");
	create_tex_expression(node, tex_file, true);
	TEX(") $$\n");

	return ALL_GOOD;
}

error_t tex_src_simpl_node(FILE *tex_file, B_tree_node *node)
{
	TEX("Let's simplify:\n");
	TEX("$$ ");
	create_tex_expression(node, tex_file, true);
	TEX(" $$\n");

	return ALL_GOOD;
}

error_t tex_result(FILE *tex_file, B_tree_node *result)
{
	fprintf(tex_file, "result:\n$$ ");
	create_tex_expression(result, tex_file, true);
	fprintf(tex_file, " $$\n");

	return ALL_GOOD;
}

struct B_tree_node *differentiate(struct B_tree_node *node, FILE *tex_file)
{
	if(node == NULL)
	{
		fprintf(stderr, "NODE_NULL_PTR\n");
		return NULL;
	}

	tex_src_diff_node(tex_file, node);

	B_tree_node *result = NULL;

	switch(node->type)
	{
		case NUM:
		{
			result = ZERO;
			break;
		}
		case VAR:
		{
			result = ONE;
			break;
		}
		case OP:
		{
			switch(node->value.op_value)
			{
				case ADD:
				{
					result = ADD(dL, dR);
					break;
				}
				case SUB:
				{
					result = SUB(dL, dR);
					break;
				}
				case MUL:
				{
					result = ADD(MUL(dL, cR), MUL(cL, dR));
					break;
				}
				case DIV:
				{
					result = DIV(SUB(MUL(dL, cR), MUL(cL, dR)), POW(cR, TWO));
					break;
				}
				case POW:
				{
					B_tree_node *left_child  = MUL(MUL(cR, POW(cL, SUB(cR, ONE))), dL);
					B_tree_node *right_child = MUL(MUL(POW(cL, cR), LN(cL)), dR);

					result = ADD(left_child, right_child);
					break;
				}
				case LN:
				{
					result = MUL(DIV(ONE, cR), dR);
					break;
				}
				case SIN:
				{
					result = MUL(COS(cR), dR);
					break;
				}
				case COS:
				{
					result = MUL(SUB(ZERO, SIN(cR)), dR);
					break;
				}
				case SQRT:
				{
					result = MUL(DIV(ONE, MUL(TWO, SQRT(cR))), dR);
					break;
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

			break;
		}
		default:
		{
			fprintf(stderr, "Unknown node type %d\n", node->type);
			return NULL;
		}
	}

	tex_result(tex_file, result);

	return result;
}

error_t create_tex_expression(struct B_tree_node *root, FILE *tex_file, bool do_var_rep)
{
	struct B_tree_node fictitious_root_parent =
	{
		.type = OP,
		.value.op_value = DO_NOTHING,
		.left = root,
		.right = root,
	};

	tex_node_print(&fictitious_root_parent, RIGHT_CHILD, tex_file, do_var_rep);

	return ALL_GOOD;
}

static bool change_flag      = false;
static bool non_trivial_flag = false;

#define TRY_TO_SIMPLIFY								\
	simple_node = wrap_consts(node);				\
	if(change_flag == true)							\
	{												\
		tex_result(tex_file, simple_node);			\
		return simple_node;							\
	}												\
													\
	simple_node = solve_trivial(node);				\
	if(non_trivial_flag == true)					\
	{												\
		result = simplify(simple_node, tex_file);	\
		tex_result(tex_file, result);				\
		return result;								\
	}												\
													\
	if(change_flag == true)							\
	{												\
		tex_result(tex_file, simple_node);			\
		return simple_node;							\
	}

B_tree_node *simplify(B_tree_node *node, FILE *tex_file)
{
	if(node == NULL)
	{
		return NULL;
	}

	B_tree_node *simple_node = NULL;
	B_tree_node *result = NULL;

	tex_src_simpl_node(tex_file, node);

	TRY_TO_SIMPLIFY;

	node->left  = simplify(node->left, tex_file);
	node->right = simplify(node->right, tex_file);

	TRY_TO_SIMPLIFY;

	tex_result(tex_file, node);

	return node;
}

#undef TRY_TO_SIMPLIFY

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

	if(LEFT_IS_ZERO)
	{
		if(ZERO__MUL_DIV_POW__ANY)
		{
			change_flag = true;
			return ZERO;
		}
		else if(ZERO__ADD__ANY)
		{
			change_flag      = true;
			non_trivial_flag = true;
			return node->right; // might be simplified further
		}
	}
	else if(RIGHT_IS_ZERO)
	{
		if(ANY__MUL__ZERO)
		{
			change_flag = true;
			return ZERO;
		}
		else if(ANY__POW__ZERO)
		{
			change_flag = true;
			return ONE;
		}
		else if	(ANY__DIV__ZERO)
		{
			change_flag = true;
			return create_node(NUM, {.num_value = NAN}, NULL, NULL).arg.node;
		}
		else if(ANY__ADD_SUB__ZERO)
		{
			change_flag      = true;
			non_trivial_flag = true;
			return node->left; // might be simplified further
		}
	}
	else if(LEFT_IS_ONE)
	{
		if(ONE__MUL__ANY)
		{
			change_flag      = true;
			non_trivial_flag = true;
			return node->right;	// might be simplified further
		}
		else if(ONE__POW__ANY)
		{
			change_flag = true;
			return ONE;
		}
	}
	else if(RIGHT_IS_ONE)
	{
		if(ANY__MUL_POW_DIV__ONE)
		{
			change_flag      = true;
			non_trivial_flag = true;
			return node->left;	// might be simplified further
		}
	}
	else if(VAR__SUB__VAR)
	{
		change_flag = true;
		return ZERO;
	}
// 	else if(SAME_OP_W_CONSTS)
//
// 	#define SAME_OP_W_CONSTS\
// 	left or right is const
// 		and the other one is op
// 			and left or right of the op is the same op
// 				and left or right child of the ops op is const


	return node;
}

size_t get_node_size(B_tree_node *node)
{
	if(node == NULL)
	{
		return 0;
	}

	if(check_if_notated(node).notated)
	{
		return 1;
	}

	size_t size = 1;

	size += get_node_size(node->left);
	size += get_node_size(node->right);

	return size;
}

char set_notation(B_tree_node *node)
{
	size_t cur_ID = notations.size;
	char cur_letter = 'A' + (char)cur_ID;

	notations.data[cur_ID].node = node;
	notations.data[cur_ID].letter = cur_letter;

	(notations.size)++;

	return cur_letter;
}

error_t refresh_notations()
{
	CALLOC(notations.data, AMOUNT_OF_NOTATIONS, Notation);

	for(size_t notat_ID = 0; notat_ID < notations.size; notat_ID++)
	{
		notations.data[notat_ID].node   = NULL;
		notations.data[notat_ID].letter = 0;
	}

	notations.size = 0;

	return ALL_GOOD;
}

void tex_notations(FILE *tex_file)
{
	TEX("Where:\\newline ");

	for(size_t notat_ID = 0; notat_ID < notations.size; notat_ID++)
	{
		TEX("%c = ", notations.data[notat_ID].letter);
		TEX("$$ ");
		/* происодит повторная нотация узлов
		   когда мы поднимаемся на уровень выше должны использоваться
		   те переменные которые мы ввели. сейчас decition if notate происходит
		   на каждом уровне игнорируя предыдущие нотации, основываясь только на размере дерева
		   нужно больше условий для ввода переменных*/
		create_tex_expression(notations.data[notat_ID].node, tex_file, false);
		TEX(" $$\n");
	}
}

//true if there is notation
Notat_check check_if_notated(B_tree_node *node)
{
	Notat_check result =
	{
		.notated = false,
		.letter  = 0,
	};

	for(size_t notat_ID = 0; notat_ID < notations.size; notat_ID++)
	{
		if(notations.data[notat_ID].node == node)
		{
			result.notated = true;
			result.letter  = notations.data[notat_ID].letter;

			return result;
		}
	}

	return result;
}

#undef TEX
#include "undef_DSL.h"
