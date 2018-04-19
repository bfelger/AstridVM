%{
#include <stdio.h>

#include "output.h"
#include "identifiers.h"

// stuff from flex that bison needs to know about:
extern int yylex();
extern int yyparse();
extern FILE *yyin;
 
void yyerror(const char *s);
%}

%define parse.error verbose
%define parse.lac full

%locations

%union {
	int ival;
	float fval;
	char *sval;
}

%token HALT_OP NOP_OP CALL_OP RETN_OP RETV_OP PUSH_OP POP_OP JMPL_OP
%token IDENTIFIER
%token INT
%token DOT COLON

%type <sval> IDENTIFIER
%type <ival> INT int_operand

%%

instructions: instruction instructions
			| instruction
			;

instruction	: HALT_OP						{ print_HALT(); }
			| NOP_OP						{ print_NOP(); }
			| CALL_OP int_operand			{ print_CALL($2); }
			| RETN_OP						{ print_RETN(); }
			| RETV_OP int_operand			{ print_RETV($2); }
			| PUSH_OP int_operand			{ print_PUSH($2); }
			| POP_OP						{ print_POP(); }
			| JMPL_OP int_operand			{ printf("JMPL\n"); }
			| IDENTIFIER COLON				{ set_lookup_def_offset($1); }

int_operand	: INT							;
			| IDENTIFIER					{ add_lookup_entry($1); $$ = 0; }

%%

int main( int argc, char *argv[] )
{ 
	if (argc < 3)
	{
		printf("USAGE: astridasm <input> <output>\n");
		return 0;
	}

	yyin = fopen(argv[1], "r");
	if (!yyin) {
		printf("Can't open file: %s\n", argv[1]);
		return -1;
	}

	prep_out_buf();

	yyparse();

	resolve_lookups();

	for (int i = 0; i < out_buf_index; i+=2)
	{
		printf ("%04x ", (unsigned int) out_buf[i] | (unsigned int) out_buf[i + 1] << 8);
	}

	FILE* out = fopen(argv[2], "wb" );
	fwrite(out_buf, 1, out_buf_index, out);
	fclose(out);

	return 0;
}

