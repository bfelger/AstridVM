
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "globals.h"
#include "output.h"
#include "identifiers.h"
#include "../vm/opcodes.h"

char out_buf[OUT_BUF_SIZE];

uint16_t out_buf_index;

void prep_out_buf()
{
	out_buf_index = 0;
	prep_lookup_entries();
}

void print_opcode(uint16_t opcode)
{
	*(uint16_t*)(out_buf + out_buf_index) = opcode;
	out_buf_index += 2;
}

void print_offset(uint16_t offset)
{
	*(uint16_t*)(out_buf + out_buf_index) = offset;
	out_buf_index += 2;
}

void print_integer(uint16_t integer)
{
	*(uint16_t*)(out_buf + out_buf_index) = integer;
	out_buf_index += 2;
}

void print_address(uint16_t ref_offset, uint16_t offset)
{
	*(uint16_t*)(out_buf + ref_offset) = offset;
}

void print_HALT()
{
#ifdef DEBUG
	printf("HALT\n");
#endif
	
	print_opcode(HALT);
}

void print_NOP()
{
#ifdef DEBUG
	printf("NOP\n");
#endif

	print_opcode(NOP);
}

void print_RETN()
{
#ifdef DEBUG
	printf("RETN\n");
#endif

	print_opcode(RETN);
}

void print_CALL(uint16_t offset)
{
#ifdef DEBUG
	printf("CALL(%d)\n", offset);
#endif

	print_opcode(CALL);
	print_offset(offset);
}

void print_POP()
{
#ifdef DEBUG
	printf("POP\n");
#endif

	print_opcode(POP);
}

void print_RETV(uint16_t integer)
{
#ifdef DEBUG
	printf("RETV(%d)\n", integer);
#endif

	print_opcode(RETV);
	print_integer(integer);
}

void print_PUSH(uint16_t integer)
{
#ifdef DEBUG
	printf("PUSH(%d)\n", integer);
#endif

	print_opcode(PUSH);
	print_integer(integer);
}

void print_JMPL(uint16_t integer)
{
#ifdef DEBUG
	printf("LMPL(%d)\n", integer);
#endif

	print_opcode(JMPL);
	print_integer(integer);
}