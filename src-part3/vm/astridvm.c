#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "globals.h"
#include "opcodes.h"
#include "registers.h"

union vm_register registers[NUM_REGS];

unsigned char stack[STACK_SIZE];
unsigned char *instructions = NULL;

callstack_record callstack[CALLSTACK_SIZE];

bool running = true;

void eval(OPCODE_TYPE opcode)
{
	switch (opcode)
	{
	case HALT:
		running = false;

#ifdef DEBUG
		printf("HALT\n");
#endif

		break;

	case PUSH:
		push_int(fetch_int());

#ifdef DEBUG
		printf("PUSH[sp=%d] %d\n", sp, *(uint16_t*)(stack+sp-2));
#endif

		break;

	case POP:
		pop_int();

#ifdef DEBUG
		printf("POP[sp=%d] %d\n", sp, *(uint16_t*)(stack+sp));
#endif

		break;

	case CALL:
		callstack[csp]._ip = ip;
		callstack[csp]._sp = sp;
		callstack[csp]._fp = fp;
		csp++;

		ip = fetch_int();
		fp = sp;          

#ifdef DEBUG
		printf("CALL %d\n", ip);
#endif

		break;

	case RETN:
		csp--;
		ip = callstack[csp]._ip;
		sp = callstack[csp]._sp;
		fp = callstack[csp]._fp;

#ifdef DEBUG
		printf("RETN\n");
#endif

		break;

	case RETV:
		csp--;
		sp = callstack[csp]._sp;

		push_int(*(uint16_t*)(stack + fp + fetch_int()));

		ip = callstack[csp]._ip;
		fp = callstack[csp]._fp;

#ifdef DEBUG
		printf("RETV %d\n", *(uint16_t*)(stack+sp));
#endif

		break;

	case JMPL:
		ip = fp + fetch_int();

#ifdef DEBUG
		printf("JMPL %d\n", ip - fp);
#endif

		break;

	}
}

void push_int(uint16_t val)
{
	*(uint16_t*)(stack + sp) = val;
	sp += 2;
}

uint16_t pop_int()
{
	sp -= 2;
	return *(uint16_t*)(stack + sp);
}

uint16_t fetch_int()
{
	ip += 2;
	return *(uint16_t*)(instructions + ip - 2);
}

OPCODE_TYPE fetch_op()
{
	ip += OPCODE_SIZE;
	return *(OPCODE_TYPE*)(instructions + ip - OPCODE_SIZE);
}

int main(int argc, char **argv)
{
	sp = 0;
	ip = 0;
	fp = 0;
	csp = 0;

	if (argc < 2)
	{
		printf("USAGE: astridvm <input filename>\n");
		return 0;
	}

	FILE *in = fopen(argv[1], "rb");

	fseek(in, 0, SEEK_END);
	long fsize = ftell(in);
	fseek(in, 0, SEEK_SET);  

	instructions = malloc(fsize + 1);
	fread(instructions, fsize, 1, in);
	fclose(in);


	while (running)
	{
		eval(fetch_op());
	}

	free(instructions);

	return 0;
}
