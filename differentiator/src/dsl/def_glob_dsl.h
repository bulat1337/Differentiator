#ifndef DEF_DSL_H
#define DEF_DSL_H

#define TEX(...)\
	fprintf(tex_file, __VA_ARGS__);

#define CALLOC(ptr, amount, type)						\
	ptr = (type *)calloc(amount, sizeof(type));			\
	if(ptr == NULL)										\
	{													\
		fprintf(stderr, "Unable to allocate"#ptr"\n");	\
		return UNABLE_TO_ALLOCATE;						\
	}

#define FILE_PTR_CHECK(ptr)								\
	{													\
		if(ptr == NULL)									\
		{												\
			fprintf(stderr, "Unable to open"#ptr"\n");	\
														\
			result.arg.node   = NULL;					\
			result.error_code = UNABLE_TO_OPEN_FILE;	\
														\
			return result;								\
		}												\
	}

#endif
