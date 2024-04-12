#include <stdio.h>

#include "differentiator.h"

int main()
{
	// unstable tree
	// struct B_tree_node *unst_expression = get_gen("x + x - x + x + x - x + x");
	// GR_DUMP_CODE_GEN(unst_expression);
	// TEX_EXPR(unst_expression);


	struct B_tree_node *expression = parse_expr("sin(5 + ln(x ^ (y + (5 + 4))))");
	GR_DUMP_CODE_GEN(expression);


	TEX_EXPR(expression);
	TXT_EXPR(expression);



	B_tree_node *differentiated = DIFF_EXPR_TEX(expression, true).arg.node;
	GR_DUMP_CODE_GEN(differentiated);

	B_tree_node *simple_expr = SIMPL_EXPR_TEX(expression, true).arg.node;
	GR_DUMP_CODE_GEN(simple_expr);

	TXT_DUMP(expression);


	return 0;
}
