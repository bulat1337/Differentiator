#include <stdio.h>

#include "differentiator.h"

int main()
{
	// unstable tree
	// struct B_tree_node *unst_expression = get_gen("x + x - x + x + x - x + x");
	// GR_DUMP_CODE_GEN(unst_expression);
	// TEX_EXP(unst_expression);


	struct B_tree_node *expression = get_gen("sin(5 + ln(x ^ (y + (5 + 4))))");
	GR_DUMP_CODE_GEN(expression);


	TEX_EXP(expression);
	TXT_EXP(expression);



	B_tree_node *differentiated = DIFF_EXP_TEX(expression, true).arg.node;
	GR_DUMP_CODE_GEN(differentiated);

	B_tree_node *simple_exp = SIMPL_EXP_TEX(expression, true).arg.node;
	GR_DUMP_CODE_GEN(simple_exp);

	TXT_DUMP(expression);


	return 0;
}
