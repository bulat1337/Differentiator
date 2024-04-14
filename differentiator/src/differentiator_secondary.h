#ifndef DIFFERENTIATOR_SECONDARY
#define DIFFERENTIATOR_SECONDARY

#include "differentiator.h"
#include "global.h"

struct Notat_check
{
	bool notated;
	char letter;
};

struct Notation
{
	char        letter;
	B_tree_node *node;
};

struct Notations
{
	size_t    size;
	Notation *data;
};

const size_t NOTAT_BOUND         = 5;
const size_t AMOUNT_OF_NOTATIONS = 26;
const size_t DIFF_TEX_LIMIT      = 2;
const size_t SIMPL_TEX_LIMIT     = 2;

const size_t DIFF_POOL_SIZE      = 9;
const size_t SIMPL_POOL_SIZE     = 8;

const char * const diff_phrase_pool[] =
{
	"Easy to differentiate:\n",
	"Let's do some kindergarden math:\n",
	"I solved this one in 0.0000000000000021 seconds:\n",
	"Bruh you could've solved this one by yourself:\n",
	"This one is obvius:\n",
	"Come on bro this is so easy:\n",
	"I solved this one in 0.0000000000000042 seconds:\n",
	"Bro kids in USSR were solving such differentials in mind:\n",
	"I solved this one in 0.0000000000000046 seconds:\n",
};

const char * const simpl_phrase_pool[] =
{
	"It's as big as ur mom, lets try to simpify:\n",
	"It's as big as ur dad, lets try to simpify:\n",
	"It's as big as ur granny, lets try to simpify:\n",
	"It's as big as ur grandpa, lets try to simpify:\n",
	"It's as big as ur sister, lets try to simpify:\n",
	"It's as big as ur brother, lets try to simpify:\n",
	"It's as big as ur cousin, lets try to simpify:\n",
	"It's as big as you, lets try to simpify:\n",
};

void         print_node           (B_tree_node *parent, bool is_right_child,
								   FILE *expression);

void         tex_node_print       (B_tree_node *parent, bool is_right_child,
					               FILE *expression, bool do_var_rep,
								   Notations *notations);

void         tex_notations        (FILE *tex_file, Notations *notations);

void         notations_dtor       (Notations *notations);

void         write_op             (FILE *expression_file, Ops op_value);

B_tree_node *get_node             (B_tree_node *parent, bool is_right_child);

btr_elem_t   get_var_value        (const char *var_name,
								   const Labels_w_len *labels_w_len);

B_tree_node *diff                 (B_tree_node *node, FILE *tex_file,
						           bool tex_process, Notations *notations);

error_t      tex_src_diff_node    (FILE *tex_file, B_tree_node *node,
								   Notations *notations);

error_t      tex_src_simpl_node   (FILE *tex_file, B_tree_node *node,
								   Notations *notations);

error_t      tex_result           (FILE *tex_file, B_tree_node *node,
								   Notations *notations);

error_t      create_tex_expression(B_tree_node *root, FILE *tex_file,
								   bool do_var_rep, Notations *notations);

error_t      init_notations       (Notations *notations);

B_tree_node *simpl                (B_tree_node *node,  FILE *tex_file,
							       bool tex_process, Notations *notations);

size_t       get_node_size        (B_tree_node *node, Notations *notations);

size_t       manage_notations     (B_tree_node *node, Notations *notations);

char         set_notation         (B_tree_node *node, Notations *notations);

Notat_check  check_if_notated     (B_tree_node *node, Notations *notations);

B_tree_node *node_copy            (B_tree_node *node);

B_tree_node *solve_trivial        (B_tree_node *node);

B_tree_node *fold_consts          (B_tree_node *node);

const char  *get_phrase           (const char *const phrase_pool[],
								   const size_t pool_size);


#endif
