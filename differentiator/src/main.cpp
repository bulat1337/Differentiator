#include <stdio.h>

#include "differentiator.h"

int main()
{
    struct B_tree_node *node_1 = create_node(OP , {.op_value = POW}, NULL, NULL).arg.node;
    struct B_tree_node *node_2 = create_node(VAR , {.var_value = "x"}, NULL, NULL).arg.node;
    struct B_tree_node *node_3 = create_node(VAR , {.var_value = "y"}, NULL, NULL).arg.node;
    // struct B_tree_node *node_3 = create_node(OP , {.op_value = LN}, NULL, NULL).arg.node;
    // struct B_tree_node *node_3 = create_node(NUM , {.num_value = 6}, NULL, NULL).arg.node;
    struct B_tree_node *node_4 = create_node(NUM , {.num_value = 2}, NULL, NULL).arg.node;
    struct B_tree_node *node_5 = create_node(NUM , {.num_value = 3}, NULL, NULL).arg.node;


	printf("node_1: %d\n", node_1->value.op_value);
	printf("node_2: %s\n", node_2->value.var_value);
	printf("node_3: %s\n", node_3->value.var_value);
	// printf("node_4: %lf\n", node_4->value.num_value);
	// printf("node_5: %lf\n", node_5->value.num_value);


	add_child(node_1, node_2, LEFT_CHILD);
	add_child(node_1, node_3, RIGHT_CHILD);
//
	// add_child(node_3, node_4, LEFT_CHILD);
	// add_child(node_3, node_5, RIGHT_CHILD);

	struct Var_label labels[2] =
	{
		{.name = "x", .value = 3},
		{.name = "y", .value = 2}
	};

	struct Labels_w_len labels_w_len =
	{
		.labels = labels,
		.length = 2,
	};

	printf("eval result: %lf\n", eval(node_1, &labels_w_len));

	GR_DUMP_CODE_GEN(node_1);

	create_tex_expression(node_1, "node_1_exp.tex");
	create_txt_expression(node_1, "node_1_exp.txt");

	TXT_DUMP(node_1);

	struct B_tree_node *diff_exp = differentiate(node_1);

	TXT_DUMP(diff_exp);

	GR_DUMP_CODE_GEN(diff_exp);

	create_tex_expression(diff_exp, "diff_exp.tex");

	create_txt_expression(diff_exp, "diff_exp.txt");

	// struct B_tree_node *parser_test = get_G("4+5*(7-3*(6+8))");
	// GR_DUMP_CODE_GEN(parser_test);




	return 0;
}
