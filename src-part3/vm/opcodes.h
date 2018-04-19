#ifndef __OPCODES_H
#define __OPCODES_H

typedef enum
{
	HALT	= 0x0000,
	NOP		= 0x0001,
	PUSH	= 0x0002,		// Push onto stack. Operand is a literal integer.
	POP		= 0x0003,		// Remove integer from the top of the stack.
	CALL	= 0x0004,		// Call the address specified by the operand.
	RETN	= 0x0005,		// Return from the current procedure.
	RETV	= 0x0006,		// Same as RETV, but we take the value at the address
							// specified by the operand and push it to the stack
							// after returning.
	JMPL	= 0x0007,       // local jump; useful for providing space for local vars
	MAX
} opcodes;

#endif // __OPCODES_H
