#include <stdio.h>

#include "differentiator.h"

int main()
{
	// unstable tree
	// struct B_tree_node *expression = get_gen("x + x + x + x + x + x + x");

	struct B_tree_node *expression = get_gen("sin(5 + ln(x ^ (y + (5 + 4))))");
	GR_DUMP_CODE_GEN(expression);


	TEX_EXP(expression);

	B_tree_node *differentiated = DIFF_EXP(expression).arg.node;
	GR_DUMP_CODE_GEN(differentiated);


//некорректно определяет размер в симпле

	B_tree_node *simple_exp = SIMPL_EXP(expression).arg.node;
	GR_DUMP_CODE_GEN(simple_exp);

// 	TXT_DUMP(expression);


	return 0;
}
