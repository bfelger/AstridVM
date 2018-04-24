%{

#include <stdio.h>

#include "astridasm.tab.h"

%}

%option yylineno

%%

[ \t\n\r]       ;
";".*           ; // comment
"."             { return DOT; }
":"             { return COLON; }
HALT            { return HALT_OP; }
NOP             { return NOP_OP; }
CALL            { return CALL_OP; }
RETN            { return RETN_OP; }
RETV            { return RETV_OP; }
PUSH            { return PUSH_OP; }
POP             { return POP_OP; }
JMPL            { return JMPL_OP; }
"0x"[0-9a-fA-F]+        { yylval.ival = atoi(yytext); return INT; }
[0-9]+                  { yylval.ival = atoi(yytext); return INT; }
[a-zA-Z][a-zA-Z0-9]*    { yylval.sval = strdup(yytext); return IDENTIFIER; }

%%

void yyerror (const char *s) /* Called by yyparse on error */
{
    printf ("Line %d: %s\n%s\n", yylineno, yytext, s);
    return;
}
