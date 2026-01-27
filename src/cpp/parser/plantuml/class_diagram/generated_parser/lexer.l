%{
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern void yyrestart(FILE *input_file);
extern void yy_switch_to_buffer(void* buffer);
%}

%x NOTE_STATE

%%

"@startuml"                            { return STARTUML; }
"@enduml"                              { return END_UML; }
"class"                                { return CLASS; }
"abstract"                             { return ABSTRACT; }
"abstract class"                       { return ABSTRACT_CLASS; }
"annotation"                           { return ANNOTATION; }
"circle"                               { return CIRCLE; }
"diamond"                              { return DIAMOND; }
"entity"                               { return ENTITY; }
"enum"                                 { return ENUM; }
"exception"                            { return EXCEPTION; }
"interface"                            { return INTERFACE; }
"metaclass"                            { return METACLASS; }
"protocol"                             { return PROTOCOL; }
"stereotype"                           { return STEREOTYPE; }
"struct"                               { return STRUCT; }
(?i:\[hidden\])                        { return DOWN; }
(?i:\[dotted\])                        { return DOWN; }
(?i:\[dashed\])                        { return DOWN; }
(?i:\[bold\])                         { return DOWN; }
(?i:\[plain\])                        { return DOWN; }
(?i:down)                        { return DOWN; }
(?i:up)                        { return UP; }
(?i:left)    { return LEFT; }
(?i:right)   { return RIGHT; }
^[[:blank:]]*(?i:note)          { BEGIN(NOTE_STATE); printf("START NOTE\n"); }

<NOTE_STATE>(?i:end[[:blank:]]+note) { BEGIN(INITIAL); printf("END NOTE\n"); }
<NOTE_STATE>[ \t\n]+            { /* ignoruj białe znaki wewnątrz */ }
<NOTE_STATE>.                   { /* ignoruj każdy inny znak wewnątrz */ }

^[[:blank:]]*([+\-#~][ \t]*)[a-zA-Z_][^\n\r\(\)]*\n    { yylval.str = strdup(yytext); return ATTRIBUTE; }
^[[:blank:]]*([+\-#~][ \t]*)[a-zA-Z_][a-zA-Z0-9_?]* { yylval.str = strdup(yytext); return START_IDENTIFIER; }

","                                    { return COMMA; }
":"                                    { return COLON; }
"|"                                    { return PIPE; }
"*"                                    { return STAR; }
"o"                                    { return O; }
"#"                                    { return HASH; }
"x"                                    { return X; }
"+"                                    { return PLUS; }
"^"                                    { return HAT; }
"-"                                    { return HYPHEN; }
"<"                                    { return L_ANGLE_BRACE; }
">"                                    { return R_ANGLE_BRACE; }
"["                                    { return L_SQUARE_BRACE; }
"]"                                    { return R_SQUARE_BRACE; }
"{"                                    { return L_CURLY_BRACE; }
"}"                                    { return R_CURLY_BRACE; }
"("                                    { return LBRACE; }
")"                                    { return RBRACE; }
"'"                                    { return QUOTE; }

"@position"                            { return AT_POSITION; }
"@position_fixed"                      { return AT_POSITION_FIXED; }
"@split_edge"                          { return SPLIT_EDGE; }
"@skip_layout"                         { return SKIP_LAYOUT; }
"@diagram_type"                        { return DIAGRAM_TYPE; }
"@layout_type"                         { return LAYOUT_TYPE; }
"@edge_type"                           { return EDGE_TYPE; }

\([ \t]*[-]?[0-9]*\.?[0-9]+[ \t]*,[ \t]*[-]?[0-9]*\.?[0-9]+[ \t]*\) { yylval.str = strdup(yytext); return POSITION_ARGS; }

[a-zA-Z_][a-zA-Z0-9_]*\n               { yylval.str = strdup(yytext); return LINE_LAST_IDENTIFIER; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.str = strdup(yytext); return IDENTIFIER; }
\"[^\"]*\" { yylval.str = strdup(yytext); return IDENTIFIER; }
\"[^\"]*\"\n { yylval.str = strdup(yytext); return LINE_LAST_IDENTIFIER; }

[ \t\n]+                               { /* Debugging whitespace is usually too noisy, but you can add it if needed: printf("WS\n"); */ }
.                                      { }

%%


int yywrap() {
    return 1;
}

void yy_switch_to_buffer(void* buffer) {
    // Flex expects FILE*, so you need to adapt here
    yyrestart((FILE*)buffer);
}
