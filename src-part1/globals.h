#ifndef __GLOBALS_H
#define __GLOBALS_H

#include "types.h"

#define DEBUG

#define STACK_SIZE 1024*4
#define PROGRAM_SIZE 1024*4

extern unsigned char stack[];
extern unsigned char *instructions;

void push_int(uint16_t val);
uint16_t pop_int();
uint16_t fetch_int();
OPCODE_TYPE fetch_op();

#endif // __GLOBALS_H