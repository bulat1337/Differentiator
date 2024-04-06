#include <stdio.h>

#include "differentiator.h"

int main()
{
	struct B_tree_node *expression = get_gen("x ^ 2 + x ^ 3");
	GR_DUMP_CODE_GEN(expression);
	TEX_EXP(expression);


	B_tree_node *differentiated = DIFF_EXP(expression).arg.node;
	GR_DUMP_CODE_GEN(differentiated);

	B_tree_node *simple_exp = SIMPL_EXP(differentiated).arg.node;
	GR_DUMP_CODE_GEN(simple_exp);

	B_tree_node *differentiated_2 = DIFF_EXP(simple_exp).arg.node;
	GR_DUMP_CODE_GEN(differentiated_2);

	B_tree_node *simple_exp_2 = SIMPL_EXP(differentiated_2).arg.node;
	GR_DUMP_CODE_GEN(simple_exp_2);


// 	TXT_DUMP(expression);


	return 0;
}
