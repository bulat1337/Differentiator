#include <stdio.h>

#include "differentiator.h"

int main()
{
	struct B_tree_node *expression = get_G("ass + cos( x ) * 5.00 / ( 16.00 - ln( 3.00 ) ) ");
	GR_DUMP_CODE_GEN(expression);

	struct Var_label labels[2] =
	{
		{.name = "ass", .value = 3},
		{.name = "x", .value = 2}
	};

	struct Labels_w_len labels_w_len =
	{
		.labels = labels,
		.length = 2,
	};

	printf("eval result: %lf\n", eval(expression, &labels_w_len));


	create_tex_expression(expression, "expression_exp.tex");
	create_txt_expression(expression, "expression_exp.txt");

	TXT_DUMP(expression);

	struct B_tree_node *diff_exp = differentiate(expression);

	GR_DUMP_CODE_GEN(diff_exp);

	create_tex_expression(diff_exp, "diff_exp.tex");
	create_txt_expression(diff_exp, "diff_exp.txt");

	TXT_DUMP(diff_exp);


	return 0;
}
