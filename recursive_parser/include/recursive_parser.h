#ifndef PARSER_H
#define PARSER_H

#include "b_tree.h"

struct B_tree_node *get_G(const char *str);
struct B_tree_node *get_N();
struct B_tree_node *get_E();
struct B_tree_node *get_T();
struct B_tree_node *get_P();

void syn_assert(bool cond, size_t line);

#endif
