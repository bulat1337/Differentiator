#include <stdio.h>

#include "differentiator.h"

int main()
{
	struct B_tree_node *expression = get_gen("x ^ 2");
	GR_DUMP_CODE_GEN(expression);

	create_tex_expression(expression, "expression_exp.tex");

	B_tree_node *diff_exp = differentiate(expression);
	create_tex_expression(diff_exp, "diff_exp.tex");
	GR_DUMP_CODE_GEN(diff_exp);

	B_tree_node *simple_exp = simplify(diff_exp);
	GR_DUMP_CODE_GEN(simple_exp);

// 	struct Var_label labels[2] =
// 	{
// 		{.name = "ass", .value = 3},
// 		{.name = "x", .value = 2}
// 	};
//
// 	struct Labels_w_len labels_w_len =
// 	{
// 		.labels = labels,
// 		.length = 2,
// 	};
//
// 	printf("eval result: %lf\n", eval(expression, &labels_w_len));

	create_tex_expression(expression, "expression_exp.tex");
	create_txt_expression(expression, "expression_exp.txt");

	TXT_DUMP(expression);


	return 0;
}
