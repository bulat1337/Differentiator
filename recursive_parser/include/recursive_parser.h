#ifndef PARSER_H
#define PARSER_H

#define PARSE_LOG(...)\
	write_log("parse_log.txt", __VA_ARGS__);

#include "b_tree.h"
#include "differentiator.h"
#include "global.h"

struct B_tree_node *get_G(const char *str);
struct B_tree_node *get_N();
struct B_tree_node *get_E();
struct B_tree_node *get_T();
struct B_tree_node *get_P();
struct B_tree_node *get_ID();

#endif
