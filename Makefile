SOURCES=tree.c backend.c generator.c

ifeq ($(DEBUG),1)
  DBG=-t
  OPT=-DDEBUG
else
        DEBUG=
        OPT=
endif

all:
	yacc ${DBG} -d cotopha.y --verbose
	lex cotopha.lex
	cc ${OPT} -Wno-int-conversion -g lex.yy.c y.tab.c $(SOURCES) -o main 
