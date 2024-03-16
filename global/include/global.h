#ifndef GLOBAL_H
#define GLOBAL_H

const unsigned char ADDITIONAL_CONCATENATION_SPACE = 2;

void write_log(const char *file_name, const char *fmt, ...);

char *create_file_name(const char *name, const char *postfix);

#endif
