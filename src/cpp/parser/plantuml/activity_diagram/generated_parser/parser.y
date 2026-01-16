%define api.prefix {activity}
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <sstream>
#include <iostream>
#include <queue>
#include "generated_parser.hpp"


using Token = generated_parser::Token;
using TokenType = generated_parser::TokenType;

std::string RemoveLastChar(const std::string &str) {
  return str.substr(0, str.size() - 1);
}


void activityerror(const char *s);
extern int yylex();
extern FILE *activityin;
%}

%union {
char *str;
}

%token STARTUML ENDUML START STOP END IF DETACH BREAK THEN ELSE ELSEIF ENDIF KILL MERGE FORK WHILE ENDWHILE IS EQUALS COMMA DIAGRAM_TYPE SWITCH CASE REPEAT_WHILE REPEAT NOT ENDSWITCH BACKWARD
%token COLON SEMICOLON ARROW FORK_AGAIN END_FORK END_MERGE SPLIT SPLIT_AGAIN END_SPLIT
%token GROUP END_GROUP PARTITION OPEN_CURLY_BRACKET CLOSE_CURLY_BRACKET SWIMLANE
%token <str> ID ACTIVITY_CONTENT BRACE_CONTENT QUOTED_NAME

%%

diagram:
STARTUML ENDUML
| STARTUML statements ENDUML
| STARTUML SWIMLANE swim_statements ENDUML
;

statements:
statement
| statements statement
;

statement:
START
| STOP
| END
| DETACH
| ACTIVITY_CONTENT
| conditional_statement
| switch_case
| while_statement
| repeat_statement
| fork_statement
| split_statement
| group_statement
| partition_statement
| COMMA DIAGRAM_TYPE
;

swim_statements:
statements
| statements SWIMLANE swim_statements

then_statements:
statement
| then_statements statement
;

else_statements:
statement
| else_statements statement
;

if_stat:
IF BRACE_CONTENT eq BRACE_CONTENT
| IF BRACE_CONTENT
;

then_stat:
THEN BRACE_CONTENT
| THEN
;

else_stat:
ELSE BRACE_CONTENT
| ELSE
;

elseif_stat:
ELSEIF BRACE_CONTENT
| ELSEIF BRACE_CONTENT eq BRACE_CONTENT
;

conditional_statement:
if_stat then_stat then_statements else_stat else_statements ENDIF
| if_stat then_stat then_statements elseif_statements else_stat else_statements ENDIF
;

loop_statements_with_breaks:
statements
| statements BREAK
;

while_statement:
WHILE BRACE_CONTENT loop_statements_with_breaks endwhile_statement
| WHILE BRACE_CONTENT loop_statements_with_breaks BACKWARD statement endwhile_statement
| WHILE BRACE_CONTENT eq BRACE_CONTENT loop_statements_with_breaks endwhile_statement
| WHILE BRACE_CONTENT eq BRACE_CONTENT loop_statements_with_breaks BACKWARD statement endwhile_statement
;

repeat_statement:
REPEAT loop_statements_with_breaks REPEAT WHILE BRACE_CONTENT
| REPEAT loop_statements_with_breaks BACKWARD statement REPEAT WHILE BRACE_CONTENT
| REPEAT loop_statements_with_breaks REPEAT WHILE BRACE_CONTENT eq BRACE_CONTENT NOT BRACE_CONTENT
| REPEAT loop_statements_with_breaks BACKWARD statement REPEAT WHILE BRACE_CONTENT eq BRACE_CONTENT NOT BRACE_CONTENT

endwhile_statement:
ENDWHILE BRACE_CONTENT
| ENDWHILE
;

switch_case:
SWITCH BRACE_CONTENT case_statements ENDSWITCH
;

case_statements:
case_statement
| case_statement case_statements
;

case_statement:
CASE BRACE_CONTENT statements
;

eq:
IS
| EQUALS
;


elseif_statements:
elseif_statement
| elseif_statement elseif_statements
;

elseif_statement:
elseif_stat then_stat then_statements
| BRACE_CONTENT elseif_stat then_stat then_statements
;


fork_statement:
FORK statements fork_statements END_FORK
| FORK statements fork_statements END_MERGE
;

fork_statements:
FORK_AGAIN statements
| FORK_AGAIN statements fork_statements
;

split_statement:
SPLIT statements split_statements END_SPLIT
| SPLIT statements split_statements END_MERGE
;

split_statements:
SPLIT_AGAIN statements
| SPLIT_AGAIN statements split_statements
;

group_statement:
GROUP ID statements END_GROUP
;

partition_statement:
PARTITION ID OPEN_CURLY_BRACKET statements CLOSE_CURLY_BRACKET
;


%%

void activityerror(const char *s) {
fprintf(stderr, "Error: %s\n", s);
}

namespace generated_parser {

std::queue<Token> parse(const std::string& input) {
    ClearLogs();

    // Konwertuj std::stringbuf na FILE*
    FILE* file = fmemopen(const_cast<char*>(input.c_str()), input.size(), "r");
    if (!file) {
        perror("fmemopen");
        return {};
    }

    // Ustaw bufor jako wejście dla Flex
    activityin = file;

    int result = yyparse();
    if (result == 0) {
        std::cout << "Parsing successful!" << std::endl;
    } else {
        std::cerr << "Parsing failed!" << std::endl;
        auto logs = GetLogs();
        while (!logs.empty())
        {
          const auto token = logs.front();
          std::cerr << "Parsed token: " <<  token.type << " *" << token.name << "*" << std::endl;
          logs.pop();
        }
    }

    fclose(file); // Zamknij FILE*

    return GetLogs();
}

}