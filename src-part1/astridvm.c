#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "globals.h"
#include "opcodes.h"
#include "registers.h"

vm_register registers[NUM_REGS];

unsigned char stack[STACK_SIZE];
unsigned char *instructions = NULL;

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
		printf("PUSH[sp=%d] %d\n", sp, *(uint16_t*)(stack + sp - 2));
#endif
		break;

	case POP:
		pop_int();
#ifdef DEBUG
		printf("POP[sp=%d] %d\n", sp, *(uint16_t*)(stack + sp));
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

uint16_t program[] = {
	PUSH, 1,
	POP,
	PUSH, 5,
	PUSH, 6,
	POP,
	POP,
	HALT
};

int main(int argc, char **argv)
{
	sp = 0;
	ip = 0;
	fp = 0;

	instructions = (unsigned char*)program;

	while (running)
	{
		eval(fetch_op());
	}
	
	return 0;
}
