
#ifndef __REGISTERS_H
#define __REGISTERS_H

#include <stdint.h>

union vm_register {
	uint64_t r64;
	uint32_t r32[2];
	uint16_t r16[4];
	uint8_t r[8];
};

extern union vm_register registers[];

typedef enum
{
	A, B, C, D, E, F,
	IP, SP, FP,
	CSP,
	NUM_REGS
} registers_names;

#define ax (registers[A].r16[3])
#define bx (registers[B].r16[3])
#define cx (registers[C].r16[3])
#define ex (registers[D].r16[3])
#define fx (registers[F].r16[3])
#define dx (registers[D].r16[3])

#define ip (registers[IP].r16[3])
#define sp (registers[SP].r16[3])
#define fp (registers[FP].r16[3])

#define csp (registers[CSP].r16[3])

#endif