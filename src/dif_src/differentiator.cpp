#include <math.h>

#include "differentiator.h"
#include "differentiator_secondary.h"

btr_elem_t eval(struct B_tree_node *node)
{
	if(node == NULL)
	{
		return NAN;
	}

	if(node->type == NUM)
	{
		return node->value.num_value;
	}

	btr_elem_t left_node_value = eval(node->left);
	btr_elem_t right_node_value = eval(node->right);

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
