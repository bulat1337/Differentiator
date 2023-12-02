#include <stdio.h>

#include "differentiator.h"

int main()
{
	union Node_value OP_value_1 =
	{
		.op_value  = POW,
	};

	union Node_value NUM_value_2 =
	{
		.num_value = 2,
	};

	union Node_value NUM_value_3 =
	{
		.num_value = 8,
	};

    struct B_tree_node *node_1 = create_node(OP , OP_value_1 ).new_node;
    struct B_tree_node *node_2 = create_node(NUM, NUM_value_2).new_node;
    struct B_tree_node *node_3 = create_node(NUM, NUM_value_3).new_node;

	printf("node_1: %d\n", node_1->value.op_value);
	printf("node_2: %.2lf\n", node_2->value.num_value);
	printf("node_3: %.2lf\n", node_3->value.num_value);

	add_child(node_1, node_2, false);
	add_child(node_1, node_3, true);

	printf("eval result: %lf\n", eval(node_1));

	gr_dump_code_gen(node_1);

	return 0;
}
