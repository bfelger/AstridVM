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
		printf("PUSH[sp=%d] %d\n", sp, *(uint16_t*)(stack + sp - 2));
#endif
		break;

	case POP:
		pop_int();
#ifdef DEBUG
		printf("POP[sp=%d] %d\n", sp, *(uint16_t*)(stack + sp));
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
		printf("RETV %d\n", *(uint16_t*)(stack + sp));
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
	CALL, 24,
	POP,        // Pop what was on the stack before we called Func 1 (5)
	CALL, 36,
	POP,        // Pop the return value of Func 2 (75)
	HALT,
	PUSH, 55,   // Func 1
	PUSH, 65,
	POP,
	RETN,
	PUSH, 75,   // Func 2
	PUSH, 0,    // Setting up locals
	PUSH, 0,
	RETV, 0,    // Use the first local variable as the return value.
};

int main(int argc, char **argv)
{
	sp = 0;
	ip = 0;
	fp = 0;
	csp = 0;

	instructions = (unsigned char*)program;

	while (running)
	{
		eval(fetch_op());
	}
	
	return 0;
}
