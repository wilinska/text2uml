%{
#include "generated_parser.hpp"
#include "parser.tab.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

extern void yyrestart(FILE *input_file);
extern void yy_switch_to_buffer(void* buffer);

using Token = generated_parser::Token;
using TokenType = generated_parser::TokenType;

%}
%option prefix="activity"
%%

"@startuml"                       { return STARTUML; }
"@enduml"                         { return ENDUML; }
"start"                           { generated_parser::AddToken(TokenType::START, ""); return START; }
"stop"                            { generated_parser::AddToken(TokenType::STOP, ""); return STOP; }
"end"                             { generated_parser::AddToken(TokenType::END, ""); return END; }
"if"                              { generated_parser::AddToken(TokenType::IF, ""); return IF; }
"is"                              { generated_parser::AddToken(TokenType::IS, ""); return IS; }
"equals"                          { generated_parser::AddToken(TokenType::IS, ""); return EQUALS; }
"then"                            { generated_parser::AddToken(TokenType::THEN, ""); return THEN; }
"else"                            { generated_parser::AddToken(TokenType::ELSE, ""); return ELSE; }
"elseif"                          { generated_parser::AddToken(TokenType::ELSEIF, ""); return ELSEIF; }
"endif"                           { generated_parser::AddToken(TokenType::ENDIF, ""); return ENDIF; }
"while"                           { generated_parser::AddToken(TokenType::WHILE, ""); return WHILE; }
"endwhile"                        { generated_parser::AddToken(TokenType::ENDWHILE, ""); return ENDWHILE; }
"detach"                          { generated_parser::AddToken(TokenType::DETACH, ""); return DETACH; }
"break"                           { generated_parser::AddToken(TokenType::BREAK, ""); return BREAK; }
"backward"                        { generated_parser::AddToken(TokenType::BACKWARD, ""); return BACKWARD; }
"switch"                          { generated_parser::AddToken(TokenType::SWITCH, ""); return SWITCH; }
"case"                            { generated_parser::AddToken(TokenType::CASE, ""); return CASE; }
"endswitch"                       { generated_parser::AddToken(TokenType::ENDSWITCH, ""); return ENDSWITCH; }
"repeat"                          { generated_parser::AddToken(TokenType::REPEAT, ""); return REPEAT; }
"kill"                            { generated_parser::AddToken(TokenType::KILL, ""); return KILL; }
"not"                             { generated_parser::AddToken(TokenType::NOT, ""); return NOT; }
"fork"                            { generated_parser::AddToken(TokenType::FORK, ""); return FORK; }
fork[ \t]+again                   { generated_parser::AddToken(TokenType::FORK_AGAIN, ""); return FORK_AGAIN; }
end[ \t]+fork                     { generated_parser::AddToken(TokenType::END_FORK, ""); return END_FORK; }
end[ \t]+merge                    { generated_parser::AddToken(TokenType::END_MERGE, ""); return END_MERGE; }
"split"                           { generated_parser::AddToken(TokenType::SPLIT, ""); return SPLIT; }
split[ \t]+again                  { generated_parser::AddToken(TokenType::SPLIT_AGAIN, ""); return SPLIT_AGAIN; }
end[ \t]+split                    { generated_parser::AddToken(TokenType::END_SPLIT, ""); return END_SPLIT; }
"group"                           { generated_parser::AddToken(TokenType::GROUP, ""); return GROUP; }
end[ \t]+group                    { generated_parser::AddToken(TokenType::END_GROUP, ""); return END_GROUP; }
"partition"                       { generated_parser::AddToken(TokenType::PARTITION, ""); return PARTITION; }
"merge"                           { generated_parser::AddToken(TokenType::MERGE, ""); return MERGE; }
[a-zA-Z][a-zA-Z0-9_]*             { activitylval.str = strdup(yytext); generated_parser::AddToken(TokenType::ID, yytext); return ID; }
\"[a-zA-Z][a-zA-Z0-9_\t]*\"       { activitylval.str = strdup(yytext); generated_parser::AddToken(TokenType::ID, yytext); return ID; }
:[^;]*;                           { activitylval.str = strdup(yytext); generated_parser::AddToken(TokenType::ACTIVITY_CONTENT, yytext); return ACTIVITY_CONTENT; }
(\([^)]*\))                       { activitylval.str = strdup(yytext); generated_parser::AddToken(TokenType::BRACE_CONTENT, yytext); return BRACE_CONTENT; }
\"[^\"]*\"                        { activitylval.str = strdup(yytext); generated_parser::AddToken(TokenType::QUOTED_NAME, yytext); return QUOTED_NAME; }
\|[a-zA-Z][a-zA-Z0-9_\t]*\|       { activitylval.str = strdup(yytext); generated_parser::AddToken(TokenType::SWIMLANE, yytext); return SWIMLANE; }
";"                               { generated_parser::AddToken(TokenType::SEMICOLON, NULL); return SEMICOLON; }
"{"                               { generated_parser::AddToken(TokenType::OPEN_CURLY_BRACKET, NULL); return OPEN_CURLY_BRACKET; }
"}"                               { generated_parser::AddToken(TokenType::CLOSE_CURLY_BRACKET, NULL); return CLOSE_CURLY_BRACKET; }
"->"                              { generated_parser::AddToken(TokenType::ARROW, NULL); return ARROW; }
\'[^\n]*\n                        {}
[\n]                              {}
[ \t]+                            {}
.                                 {}

%%

int yywrap() {
    return 1;
}

void yy_switch_to_buffer(void* buffer) {
    yyrestart((FILE*)buffer);
}
