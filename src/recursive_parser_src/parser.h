#ifndef PARSER_H
#define PARSER_H

int get_G(const char *str);
void syn_assert(bool cond, size_t line);
int get_N();
int get_E();
int get_T();
int get_P();

#endif
