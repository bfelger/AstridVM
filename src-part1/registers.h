#ifndef __REGISTERS_H
#define __REGISTERS_H

#include <stdint.h>

union vm_register {
	uint64_t r64;
	uint32_t r32;
	uint16_t r16;
	uint8_t r8[2];
};

extern union vm_register registers[];

typedef enum
{
	IP, SP, FP,
	NUM_REGS
} registers_names;

#define ip (registers[IP].r16)
#define sp (registers[SP].r16)
#define fp (registers[FP].r16)

#endif
