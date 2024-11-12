GCC = gcc
FLAGS = -c

PROGS = modularMem_Rodriguez01

modularMem_Rodriguez01:
		$(GCC) $(FLAGS) dinamiclib.c
		$(GCC) dinamiclib.o $@.c -o $@
		
clear:
		$(RM) $(PROGS) *.o