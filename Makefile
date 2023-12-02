PREF_DIF_OBJ = ./obj/dif_obj/
PREF_DIF_SRC = ./src/dif_src/
B_TREE_SRC = ./src/b_tree_src/
B_TREE_OBJ = ./obj/b_tree_obj/
PARS_SRC = ./src/recursive_parser_src/
PARS_OBJ = ./obj/recursive_parser_obj/
CC = g++
TARGET_1 = dif.out
FLAGS = -D _DEBUG -ggdb3 \
    -std=c++17 -O0 -Wall -Wextra -Weffc++ -Wc++14-compat        \
    -Wmissing-declarations -Wcast-qual -Wchar-subscripts  \
    -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security \
    -Wformat=2 -Winline -Wnon-virtual-dtor -Woverloaded-virtual \
    -Wpacked -Wpointer-arith -Winit-self -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo \
    -Wstrict-overflow=2 \
    -Wsuggest-override -Wswitch-default -Wswitch-enum -Wundef \
    -Wunreachable-code -Wunused -Wvariadic-macros \
    -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs \
    -Wstack-protector -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow \
    -fno-omit-frame-pointer -Wlarger-than=8192 \
    -fPIE -Werror=vla -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

LINK_FLAGS = -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr

$(TARGET_1): $(PREF_DIF_OBJ)main.o $(PREF_DIF_OBJ)differentiator.o $(PREF_DIF_OBJ)differentiator_secondary.o $(B_TREE_OBJ)b_tree.o $(B_TREE_OBJ)b_tree_secondary.o
	@ $(CC) $(LINK_FLAGS) $(PREF_DIF_OBJ)main.o $(PREF_DIF_OBJ)differentiator.o $(PREF_DIF_OBJ)differentiator_secondary.o $(B_TREE_OBJ)b_tree.o $(B_TREE_OBJ)b_tree_secondary.o -o $(TARGET_1)

$(PREF_DIF_OBJ)main.o: $(PREF_DIF_SRC)main.cpp
	@ $(CC) -c $(PREF_DIF_SRC)main.cpp -o $(PREF_DIF_OBJ)main.o $(FLAGS)

$(PREF_DIF_OBJ)differentiator.o: $(PREF_DIF_SRC)differentiator.cpp
	@ $(CC) -c $(PREF_DIF_SRC)differentiator.cpp -o $(PREF_DIF_OBJ)differentiator.o $(FLAGS)

$(PREF_DIF_OBJ)differentiator_secondary.o: $(PREF_DIF_SRC)differentiator_secondary.cpp
	@ $(CC) -c $(PREF_DIF_SRC)differentiator_secondary.cpp -o $(PREF_DIF_OBJ)differentiator_secondary.o $(FLAGS)

$(B_TREE_OBJ)b_tree.o: $(B_TREE_SRC)b_tree.cpp
	@ $(CC) -c $(B_TREE_SRC)b_tree.cpp -o $(B_TREE_OBJ)b_tree.o $(FLAGS)

$(B_TREE_OBJ)b_tree_secondary.o: $(B_TREE_SRC)b_tree_secondary.cpp
	@ $(CC) -c $(B_TREE_SRC)b_tree_secondary.cpp -o $(B_TREE_OBJ)b_tree_secondary.o $(FLAGS)

$(PARS_OBJ)recursive_parser.o: $(PARS_SRC)recursive_parser.cpp
	@ $(CC) -c $(PARS_SRC)recursive_parser.cpp -o $(PARS_OBJ)recursive_parser.o $(FLAGS)

clean:
	rm $(TARGET_1) $(PREF_DIF_OBJ)*.o $(B_TREE_OBJ)*.o $(PARS_OBJ)*.o
