PATH_DIF_OBJ    = ../obj/differentiator_obj/
PATH_DIF_SRC    = ./src/

DIF_SRC = $(wildcard $(PATH_DIF_SRC)*.cpp)
DIF_OBJ = $(patsubst $(PATH_DIF_SRC)%.cpp, $(PATH_DIF_OBJ)%.o, $(DIF_SRC))

PATH_GLOBAL_OBJ = ../obj/global_obj/
PATH_GLOBAL_SRC     = ../global/src/
GLOBAL_SRC = $(wildcard $(PATH_GLOBAL_SRC)*.cpp)
GLOBAL_OBJ = $(patsubst $(PATH_GLOBAL_SRC)%.cpp, $(PATH_GLOBAL_OBJ)%.o, $(GLOBAL_SRC))

TARGET = ../executables/dif.out

CC = g++

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

Include = -I../b_tree/include/ -I./include/ -I./src/dsl/ -I../recursive_parser/include/ -I../global/include/

$(TARGET): $(DIF_OBJ)
	@ $(CC) $(LINK_FLAGS) $^ $(GLOBAL_OBJ) -o $@ -L../libs -lb_tree -lrecursive_parser

$(PATH_DIF_OBJ)%.o: $(PATH_DIF_SRC)%.cpp
	@ $(CC) -c $< -o $@ $(FLAGS) $(Include)

clean:
	@rm $(TARGET) $(PATH_DIF_OBJ)*.o
