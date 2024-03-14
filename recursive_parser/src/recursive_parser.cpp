#include <stdio.h>
#include <stdlib.h>

#include "recursive_parser.h"

static const char *s = NULL;
static int p = 0;

struct B_tree_node *get_G(const char *str)
{
	s = str;
	p = 0;
	struct B_tree_node *val = get_E();
	syn_assert(s[p] == '\0', __LINE__);
	return val;
}

struct B_tree_node *get_N()
{
	btr_elem_t val = 0;
	int old_p = p;

	while('0' <= s[p] && s[p] <= '9')
	{
		val = val * 10 + s[p] - '0';

		p++;
	}

	syn_assert(p > old_p, __LINE__);

	return create_node(NUM, {.num_value = val}, NULL, NULL).arg.node;
}

struct B_tree_node *get_E()
{
	struct B_tree_node *val = get_T();
	while(s[p] == '+' || s[p] == '-')
	{
		char op = s[p];

		p++;

		struct B_tree_node *val_2 = get_T();

		switch(op)
		{
			case '+':
			{
				val = create_node(OP, {.op_value = ADD}, val, val_2).arg.node;
				break;
			}
			case '-':
			{
				val = create_node(OP, {.op_value = SUB}, val, val_2).arg.node;
				break;
			}
			default:
			{
				syn_assert(true, __LINE__);
			}
		}
	}

	return val;
}

struct B_tree_node *get_T()
{
	struct B_tree_node *val = get_P();
	while(s[p] == '*' || s[p] == '/')
	{
		char op = s[p];

		p++;

		struct B_tree_node *val_2 = get_P();

		switch(op)
		{
			case '*':
			{
				val = create_node(OP, {.op_value = MUL}, val, val_2).arg.node;
				break;
			}
			case '/':
			{
				val = create_node(OP, {.op_value = DIV}, val, val_2).arg.node;
				break;
			}
			default:
			{
				syn_assert(true, __LINE__);
			}
		}
	}

	return val;
}

struct B_tree_node *get_P()
{
	if(s[p] == '(')
	{
		p++;
		struct B_tree_node *val = get_E();
		syn_assert(s[p] == ')', __LINE__);
		p++;
		return val;
	}
	else
	{
		return get_N();
	}
}

void syn_assert(bool cond, size_t line)
{
	if(!cond)
	{
		printf("error on: %lu\n", line);
		exit(EXIT_FAILURE);
	}
}
