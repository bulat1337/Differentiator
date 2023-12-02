#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

static const char *s = NULL;
static int p = 0;

int get_G(const char *str)
{
	s = str;
	p = 0;
	int val = get_E();
	syn_assert(s[p] == '\0', __LINE__);
	return val;
}

int get_N()
{
	int val = 0;
	int old_p = p;

	while('0' <= s[p] && s[p] <= '9')
	{
		val = val * 10 + s[p] - '0';

		p++;
	}

	syn_assert(p > old_p, __LINE__);

	return val;
}

int get_E()
{
	int val = get_T();
	while(s[p] == '+' || s[p] == '-')
	{
		char op = s[p];

		p++;

		int val_2 = get_T();

		switch(op)
		{
			case '+':
			{
				val += val_2;
				break;
			}
			case '-':
			{
				val -= val_2;
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

int get_T()
{
	int val = get_P();
	while(s[p] == '*' || s[p] == '/')
	{
		char op = s[p];

		p++;

		int val_2 = get_P();

		switch(op)
		{
			case '*':
			{
				val *= val_2;
				break;
			}
			case '/':
			{
				val /= val_2;
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

int get_P()
{
	if(s[p] == '(')
	{
		int val = 0;
		p++;
		val = get_E();
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
