#ifndef __GLOBALS_H
#define __GLOBALS_H

#include "types.h"

#define DEBUG

#define STACK_SIZE 1024*4
#define PROGRAM_SIZE 1024
#define CALLSTACK_SIZE 256

extern unsigned char stack[];
extern unsigned char *instructions;

typedef struct callstack_record
{
	OFFSET_TYPE _sp;
	OFFSET_TYPE _ip;
	OFFSET_TYPE _fp;
} callstack_record;

extern callstack_record callstack[];

void push_int(uint16_t val);
uint16_t pop_int();
uint16_t fetch_int();
OPCODE_TYPE fetch_op();

#endif
