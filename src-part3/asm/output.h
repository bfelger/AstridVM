#include "astridasm.tab.h"

#ifndef __OUTPUT_H
#define __OUTPUT_H

#define OUT_BUF_SIZE 1024*4

extern char out_buf[];

extern uint16_t out_buf_index;

void prep_out_buf();

void print_opcode(uint16_t);
void print_integer(uint16_t);
void print_address(uint16_t, uint16_t);

void print_HALT();
void print_NOP();
void print_CALL(uint16_t);
void print_RETN();
void print_POP();
void print_integer(uint16_t);
void print_RETV(uint16_t);
void print_PUSH(uint16_t);
void print_JMPL(uint16_t);

#endif
