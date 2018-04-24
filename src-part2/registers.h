#ifndef __REGISTERS_H
#define __REGISTERS_H

#include <stdint.h>

typedef union vm_register {
	uint64_t r64;
	uint32_t r32;
	uint16_t r16;
	uint8_t r8[2];
} vm_register;

extern vm_register registers[];

typedef enum
{
	IP, SP, FP,
	CSP,
	NUM_REGS
} registers_names;

#define ip (registers[IP].r16)
#define sp (registers[SP].r16)
#define fp (registers[FP].r16)

#define csp (registers[CSP].r16)

#endif // __REGISTERS_H
