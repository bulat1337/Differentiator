#include "differentiator.h"
#include "differentiator_secondary.h"
#include "def_DSL.h"

#define PUT_PARENTHESIS_COND\
		(	(parent->type == OP) &&															\
			(	(parent->value.op_value == LN) ||											\
				(parent->value.op_value == SIN) ||											\
				(parent->value.op_value == SQRT) ||											\
				(parent->value.op_value == COS)	)	) ||									\
		!(	(node->type == NUM) || 															\
	  		(node->type == VAR) ||		 													\
	    	(	(	(node->type == OP) &&													\
						(	(node->value.op_value == MUL) ||								\
							(node->value.op_value == POW) ||								\
							(node->value.op_value == DIV)	)	) &&						\
					!(	(parent->type == OP) &&												\
						(parent->value.op_value == POW)	)	) ||							\
	    	(	(node->type == OP) &&														\
				(	(node->value.op_value == LN) ||											\
					(node->value.op_value == SIN) ||										\
					(node->value.op_value == SQRT) ||										\
					(node->value.op_value == COS)	)	) ||								\
			(	(parent->type == OP) && (parent->value.op_value == DO_NOTHING)	)	)		\

#define PUT_PARENTHESIS_COND_TEX															\
		(	(parent->type == OP) &&															\
		(	(parent->value.op_value == LN) ||												\
			(parent->value.op_value == SIN) ||												\
			(parent->value.op_value == COS)	)	) ||										\
	  	!(	(node->type == NUM) || 															\
	  		(node->type == VAR) ||		 													\
	  		(	(parent->type == OP) &&														\
				(parent->value.op_value == POW) &&											\
				!(node->value.op_value == POW)	) ||		 								\
	   		(	(node->type == OP) &&														\
				(	(node->value.op_value == MUL) ||										\
					(node->value.op_value == DIV) ||										\
					(node->value.op_value == LN) ||											\
					(node->value.op_value == SQRT) ||										\
					(node->value.op_value == SIN) ||										\
					(node->value.op_value == COS) ||										\
					(	(node->value.op_value == POW) &&									\
						!(parent->value.op_value == POW)	)	)	) ||					\
			(	(parent->type == OP) && (parent->value.op_value == DO_NOTHING)	)	) &&	\
			!do_var_rep																		\

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
					FILE *tex_file, bool do_var_rep)
{
	struct B_tree_node *node = get_node(parent, is_right_child);

    if(node == NULL)
    {
        return;
    }

	if(PUT_PARENTHESIS_COND_TEX)
	{
    	TEX("(");
	}

	if(	(parent->type == OP) &&
		(	(parent->value.op_value == POW) ||
			(parent->value.op_value == SQRT)	)	)
	{
		TEX("{");
	}

	if(do_var_rep)
	{
		//check if there is notation
		Notat_check check = check_if_notated(node);
		if(check.notated)
		{
			TEX("%c", check.letter);

			if(	(parent->type == OP) &&
				(	(parent->value.op_value == POW) ||
					(parent->value.op_value == SQRT)	)	)
			{
				TEX("}");
			}

			if(PUT_PARENTHESIS_COND_TEX)
			{
				TEX(")");
			}

			return;
		}
	}

	if(	!(	(node->type == OP) && (node->value.op_value == DIV)	)	)
	{
		tex_node_print(node, LEFT_CHILD, tex_file, true);
	}

	switch(node->type)
	{
		case OP:
		{
			switch(node->value.op_value)
			{
				case ADD:
				{
					TEX("+");
					break;
				}
				case SUB:
				{
					TEX("-");
					break;
				}
				case MUL:
				{
					TEX("*");
					break;
				}
				case DIV:
				{
					TEX("\\frac");
					break;
				}
				case POW:
				{
					TEX("^");
					break;
				}
				case LN:
				{
					TEX("\\ln");
					break;
				}
				case SIN:
				{
					TEX("\\sin");
					break;
				}
				case COS:
				{
					TEX("\\cos");
					break;
				}
				case SQRT:
				{
					TEX("\\sqrt");
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
			TEX("{%.2lf}", node->value.num_value);
			break;
		}
		case VAR:
		{
			TEX("{%s}", node->value.var_value);
			break;
		}
		default:
		{
			fprintf(stderr, "Unknown value_type in %s[%d]\n", __func__, __LINE__);
		}
	}

	if(	(	(node->type == OP) && (node->value.op_value == DIV)	))
	{
		TEX("{");
		tex_node_print(node, LEFT_CHILD, tex_file, true);
		TEX("}");

		TEX("{");
		tex_node_print(node, RIGHT_CHILD, tex_file, true);
		TEX("}");
	}
	else
	{
    	tex_node_print(node, RIGHT_CHILD, tex_file, true);
	}

	if(	(parent->type == OP) &&
		(	(parent->value.op_value == POW) ||
			(parent->value.op_value == SQRT)	)	)
	{
		TEX("}");
	}

	if(PUT_PARENTHESIS_COND_TEX)
	{
    	TEX(")");
	}
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
	manage_notations(node);

	TEX("Let's solve:\n");
	TEX("$$ d(");
	create_tex_expression(node, tex_file, true);
	TEX(") $$\n");

	return ALL_GOOD;
}

error_t tex_src_simpl_node(FILE *tex_file, B_tree_node *node)
{
	manage_notations(node);

	TEX("Let's simplify:\n");
	TEX("$$ ");
	create_tex_expression(node, tex_file, true);
	TEX(" $$\n");

	return ALL_GOOD;
}

error_t tex_result(FILE *tex_file, B_tree_node *node)
{
	manage_notations(node);

	fprintf(tex_file, "result:\n$$ ");
	create_tex_expression(node, tex_file, true);
	fprintf(tex_file, " $$\n");

	return ALL_GOOD;
}

struct B_tree_node *diff(struct B_tree_node *node, FILE *tex_file,
								  bool tex_process)
{
	if(node == NULL)
	{
		fprintf(stderr, "NODE_NULL_PTR\n");
		return NULL;
	}

	if(tex_process)
	{
		tex_src_diff_node(tex_file, node);
	}

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

	if(tex_process)
	{
		tex_result(tex_file, result);
	}

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

#define TRY_TO_SIMPLIFY												\
	simple_node = wrap_consts(node_clone);							\
	if(change_flag == true)											\
	{																\
		tex_result(tex_file, simple_node);							\
		return simple_node;											\
	}																\
																	\
	simple_node = solve_trivial(node_clone);						\
	if(non_trivial_flag == true)									\
	{																\
		simple_node = simpl(simple_node, tex_file, tex_process);	\
		tex_result(tex_file, simple_node);							\
		return simple_node;											\
	}																\
																	\
	if(change_flag == true)											\
	{																\
		tex_result(tex_file, simple_node);							\
		return simple_node;											\
	}

B_tree_node *simpl(B_tree_node *node, FILE *tex_file, bool tex_process)
{
	B_tree_node *node_clone = node_copy(node);

	if(node_clone == NULL)
	{
		return NULL;
	}

	B_tree_node *simple_node = NULL;

	if(tex_process)
	{
		tex_src_simpl_node(tex_file, node_clone);
	}

	TRY_TO_SIMPLIFY;

	change_flag = false;

	node_clone->left  = simpl(node_clone->left,  tex_file, tex_process);
	node_clone->right = simpl(node_clone->right, tex_file, tex_process);

	TRY_TO_SIMPLIFY;

	if(tex_process)
	{
		tex_result(tex_file, node_clone);
	}

	return node_clone;
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

error_t init_notations()
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
	if(notations.size == 0)
	{
		return;
	}

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
		if(notations.data[notat_ID].node == node ||
			cmp_nodes(notations.data[notat_ID].node, node))
		{
			result.notated = true;
			result.letter  = notations.data[notat_ID].letter;

			return result;
		}
	}

	return result;
}

void notations_dtor()
{
	free(notations.data);

	notations.data = NULL;

	notations.size = 0;
}

size_t manage_notations(B_tree_node *node)
{
	if(node == NULL)
	{
		return 0;
	}

	size_t size = 1;

	size += manage_notations(node->left);
	size += manage_notations(node->right);

	if(size > NOTAT_BOUND)
	{
		//check if there is notation
		Notat_check check = check_if_notated(node);
		if(!check.notated)
		{
			set_notation(node);
		}

		return 1;
	}

	return size;
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


#undef TEX
#include "undef_DSL.h"
