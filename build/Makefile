SUBDIRS   = ../Global ../Recursive_parser ../B_tree ../Differentiator
DOT = $(wildcard *.dot)
PNG = $(patsubst %.dot, %.png, $(DOT))
TXT = $(wildcard *.txt)
TEX = $(wildcard *.tex)
LIB = $(wildcard ../libs/*.a)

JUNK = $(DOT) $(PNG) $(TXT) $(TEX) $(LIB)

all:
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir; done

dot: $(PNG)

%.png: %.dot
	dot -Tpng $< -o $@ -Gdpi=100

clean:
	@rm $(JUNK); for dir in $(SUBDIRS); do $(MAKE) clean -C $$dir; done

