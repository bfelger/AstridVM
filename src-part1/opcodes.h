#ifndef __OPCODES_H
#define __OPCODES_H

typedef enum
{
	HALT	= 0x0000,
	NOP		= 0x0001,
	PUSH	= 0x0002,		// Push onto stack. Operand is a literal integer.
	POP		= 0x0003,		// Remove the top of the stack
	MAX
} opcodes;

#endif // __OPCODES_H
