#ifndef GLOBAL_H
#define GLOBAL_H

#define WITH_OPEN(file_name, mode, file_ptr, ...)	\
	FILE *file_ptr = fopen(file_name, mode);		\
	FILE_PTR_CHECK(file_ptr);						\
													\
	__VA_ARGS__										\
													\
	fclose(file_ptr);


const unsigned char ADDITIONAL_CONCATENATION_SPACE = 2;

void  write_log        (const char *file_name, const char *fmt, ...);

char * create_file_name(const char *name, const char *postfix);

int    cmp_double      (double first_double, double second_double);

size_t max_len         (size_t len_1, size_t len_2);

#endif
