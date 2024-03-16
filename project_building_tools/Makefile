SUBDIRS   = ../global ../recursive_parser ../b_tree ../differentiator
DOT = $(wildcard *.dot)
PNG = $(patsubst %.dot, %.png, $(DOT))
TXT = $(wildcard *.txt)
TEX = $(wildcard *.tex)

JUNK = $(DOT) $(PNG) $(TXT) $(TEX)

all:
	@for dir in $(SUBDIRS); do $(MAKE) -C $$dir; done

dot: $(PNG)

%.png: %.dot
	@dot -Tpng $< -o $@ $(FLAGS) -Gdpi=100

clean:
	@rm $(JUNK); for dir in $(SUBDIRS); do $(MAKE) clean -C $$dir; done

