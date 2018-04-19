CC      = gcc
LEX		= flex
YACC	= bison
PROF    = -Wall -O2 -g
NOCRYPT =
C_FLAGS =  $(PROF) $(NOCRYPT)
L_FLAGS =  $(PROF) -lcrypt

O_FILES1 = vm/astridvm.o 

O_FILES2 = asm/astridasm.tab.o asm/astridasm.yy.o asm/output.o asm/identifiers.o

default: astridvm

asm/astridasm.tab.c asm/astridasm.tab.h: asm/astridasm.y
	$(YACC) -d -o asm/astridasm.tab.c asm/astridasm.y
	
asm/astridasm.yy.c: asm/astridasm.l asm/astridasm.tab.h
	$(LEX) -o asm/astridasm.yy.c asm/astridasm.l

.c.o: asm/*.h vm/*.h
	$(CC) -c $(C_FLAGS) -o $@ $<

astridvm: $(O_FILES1) $(O_FILES2)
	rm -f astridvm
	rm -f astridasm
	$(CC) $(L_FLAGS) -o astridvm $(O_FILES1)
	$(CC) $(L_FLAGS) -o astridasm $(O_FILES2) -lfl

clean:
	rm vm/*.o asm/*.o asm/astridasm.yy.c asm/astridasm.tab.c asm/astridasm.tab.h astridasm astridvm
