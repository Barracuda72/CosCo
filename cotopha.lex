%{
#include <stdio.h>
#include "y.tab.h"

void yyerror(const char *s);

int yycharpos = 1;

#define YY_INPUT(buf, result, max_size) \
{ \
  int c = getc(yyin); \
  if (0) { \
    if (c != EOF) \
      putchar(c); \
  } \
  result = (c == EOF) ? YY_NULL : (buf[0] = c, 1);\
}

#define YY_USER_ACTION yycharpos += yyleng;

%}

%option case-insensitive
%option yylineno

white_space       [ \t]*
digit             [0-9]
alpha             [A-Za-z_]
alpha_num         ({alpha}|{digit})
hex_digit         [0-9A-Fa-f]
identifier        {alpha}{alpha_num}*
hex_integer       {hex_digit}{hex_digit}*H
unsigned_integer  {digit}+
exponent          e[+-]?{digit}+
i                 {unsigned_integer}
real              ({i}\.{i}?|{i}?\.{i}){exponent}?
string            \'([^'\n]|\'\'|\\\')*\'
string2           \"([^"\n]|\"\"|\\\")*\"
comment           ;[^\n]*

%%

DeclareType          return (TOK_DECLARETYPE);
Include              return (TOK_INCLUDE);
Structure            return (TOK_STRUCTURE);
EndStruct            return (TOK_ENDSTRUCT);
Function             return (TOK_FUNCTION);
EndFunc              return (TOK_ENDFUNC);
Return               return (TOK_RETURN);
EndIf                return (TOK_ENDIF);
ElseIf               return (TOK_ELSEIF);
If                   return (TOK_IF);
Else                 return (TOK_ELSE);
Repeat               return (TOK_REPEAT);
Until                return (TOK_UNTIL);
For                  return (TOK_FOR);
DownTo               return (TOK_DOWNTO); /* Not present */
To                   return (TOK_TO);
Next                 return (TOK_NEXT);
EndWhile             return (TOK_ENDWHILE);
While                return (TOK_WHILE);
Break                return (TOK_BREAK);
"&&"                 return (TOK_AND);
"||"                 return (TOK_OR);
Not                  return (TOK_NOT); /* Not present */
Begin                return (TOK_BEGIN);
End                  return (TOK_END);
Constant             return (TOK_CONSTANT);
ExternDef             return (TOK_EXTRNDEF);

@If                  return (TOK_M_IF);
@Else                return (TOK_M_ELSE);
@EndIf               return (TOK_M_ENDIF);
@IsDefined           return (TOK_M_ISDEFINED);

@Operate             return (TOK_ID_OPERATE); /* Special case */

":="                 return (TOK_ASSIGN);
"<="|"=<"            return (TOK_LEQ);
"=>"|">="            return (TOK_GEQ);
"!="                 return (TOK_NEQ);
"=="                 return (TOK_EQ);
"+="                 return (TOK_ADD_ASS);
"-="                 return (TOK_SUB_ASS);
"/="                 return (TOK_DIV_ASS);
"*="                 return (TOK_MUL_ASS);
"|="                 return (TOK_OR_ASS);
"&="                 return (TOK_AND_ASS);

".."                 return (TOK_DOUBLEDOT);
"::"                 return (TOK_QUADDOT);

{unsigned_integer}   yylval = strdup(yytext); return (TOK_UNSIGNED_INTEGER);
{real}/[^.]          yylval = strdup(yytext); return (TOK_FLOAT);
{hex_integer}        yylval = strdup(yytext); return (TOK_HEX_INTEGER);
{string}             yylval = strdup(yytext); return (TOK_CSTRING);
{string2}            yylval = strdup(yytext); return (TOK_CSTRING);

{identifier}         yylval = strdup(yytext); return (TOK_IDENTIFIER);

[|!&*/+%\-,^.:()\[\]><] return (yytext[0]);

{white_space}        /* Skip whitespaces */
{comment}            /* Skip comments */
\n                   yycharpos = 1;
.                    yyerror("Illegal input!");

%%

