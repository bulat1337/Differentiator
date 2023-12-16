#include <stdio.h>

#include "differentiator.h"

int main()
{
    struct B_tree_node *node_1 = create_node(OP , {.op_value = MUL}, NULL, NULL).new_node;
    struct B_tree_node *node_2 = create_node(VAR , {.var_value = "x"}, NULL, NULL).new_node;
    struct B_tree_node *node_3 = create_node(VAR , {.var_value = "y"}, NULL, NULL).new_node;


	printf("node_1: %d\n", node_1->value.op_value);
	printf("node_2: %s\n", node_2->value.var_value);
	printf("node_3: %s\n", node_3->value.var_value);


	add_child(node_1, node_2, false);
	add_child(node_1, node_3, true);

	struct Var_label labels[2] =
	{
		{.name = "x", .value = 3},
		{.name = "y", .value = 5},
	};

	struct Labels_w_len labels_w_len =
	{
		.labels = labels,
		.length = 2,
	};

	printf("eval result: %lf\n", eval(node_1, &labels_w_len));

	GR_DUMP_CODE_GEN(node_1);

	create_tex_expression(node_1, "expression.tex");
	create_txt_expression(node_1, "expression.txt");

	b_tree_console_dump(node_1);

	struct B_tree_node *diff_exp = differentiate(node_1);
	b_tree_console_dump(diff_exp);
	GR_DUMP_CODE_GEN(diff_exp);

	create_tex_expression(diff_exp, "diff_exp.tex");
	create_txt_expression(diff_exp, "diff_exp.txt");

	// struct B_tree_node *parser_test = get_G("4+5*(7-3*(6+8))");
	// GR_DUMP_CODE_GEN(parser_test);




	return 0;
}
