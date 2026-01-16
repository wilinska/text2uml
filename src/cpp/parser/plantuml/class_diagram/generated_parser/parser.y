%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <sstream>
#include <iostream>
#include <stack>
#include "generated_parser.hpp"

using Token = class_diagram::generated_parser::Token;
using TokenType = class_diagram::generated_parser::TokenType;

namespace {
std::string RemoveLastChar(const std::string &str) {
    if (str[str.size() - 1] != '\n') {
        return str;
    }
  return str.substr(0, str.size() - 1);
}
}
std::stack<Token> logs;

void yyerror(const char *s);
extern int yylex();
extern FILE *yyin;
%}

%union {
    char *str;
}

%token STARTUML END_UML
%token CLASS ABSTRACT ABSTRACT_CLASS ANNOTATION CIRCLE DIAMOND ENTITY ENUM EXCEPTION INTERFACE METACLASS PROTOCOL STEREOTYPE STRUCT
%token COLON
%token PIPE
%token STAR
%token O
%token HASH
%token X
%token PLUS
%token HAT
%token HYPHEN
%token L_ANGLE_BRACE R_ANGLE_BRACE
%token L_SQUARE_BRACE R_SQUARE_BRACE
%token L_CURLY_BRACE R_CURLY_BRACE
%token LBRACE RBRACE
%token COMMA
%token QUOTE
%token AT_POSITION AT_POSITION_FIXED SPLIT_EDGE SKIP_LAYOUT DIAGRAM_TYPE LAYOUT_TYPE EDGE_TYPE
%token <str> IDENTIFIER LINE_LAST_IDENTIFIER POSITION POSITION_FIXED POSITION_ARGS
%%

diagram:
    STARTUML components END_UML
    ;

components:
    components component
    | component
    ;

component:
    node_definition
    | relationship_with_label
    | relationship
    | command_line
    ;

command_line:
    QUOTE DIAGRAM_TYPE LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::DIAGRAM_TYPE, RemoveLastChar(std::string($3))});
        free($3);
    }
    |
    QUOTE LAYOUT_TYPE LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::LAYOUT_TYPE, RemoveLastChar(std::string($3))});
        free($3);
    }
    |
    QUOTE EDGE_TYPE LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::EDGE_TYPE, RemoveLastChar(std::string($3))});
        free($3);
    }
    ;

node_definition:
    node_type LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string($2))});
        free($2);
    }
    | node_type IDENTIFIER L_CURLY_BRACE node_body R_CURLY_BRACE
    {
        logs.push(Token{TokenType::NODE_NAME, std::string($2)});
        free($2);
    }
    | node_type LINE_LAST_IDENTIFIER L_CURLY_BRACE node_body R_CURLY_BRACE
    {
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string($2))});
        free($2);
    }
    | node_type LINE_LAST_IDENTIFIER L_CURLY_BRACE R_CURLY_BRACE
    {
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string($2))});
        free($2);
    }
    | node_type IDENTIFIER L_CURLY_BRACE R_CURLY_BRACE
    {
        logs.push(Token{TokenType::NODE_NAME, std::string($2)});
        free($2);
    }
    ;

node_type:
    CLASS
    {
        logs.push(Token{TokenType::NODE_TYPE, "Class"});
    }
    | ABSTRACT
    {
        logs.push(Token{TokenType::NODE_TYPE, "Abstract"});
    }
    | ABSTRACT_CLASS
    {
        logs.push(Token{TokenType::NODE_TYPE, "Abstract"});
    }
    | ANNOTATION
    {
        logs.push(Token{TokenType::NODE_TYPE, "Annotation"});
    }
    | CIRCLE
    {
        logs.push(Token{TokenType::NODE_TYPE, "Circle"});
    }
    | LBRACE RBRACE
    {
        logs.push(Token{TokenType::NODE_TYPE, "CIRCLE"});
    }
    | DIAMOND
    {
        logs.push(Token{TokenType::NODE_TYPE, "Diamond"});
    }
    | L_ANGLE_BRACE R_ANGLE_BRACE
    {
        logs.push(Token{TokenType::NODE_TYPE, "Diamond"});
    }
    | ENTITY
    {
        logs.push(Token{TokenType::NODE_TYPE, "Entity"});
    }
    | ENUM
    {
        logs.push(Token{TokenType::NODE_TYPE, "Enum"});
    }
    | EXCEPTION
    {
        logs.push(Token{TokenType::NODE_TYPE, "Exception"});
    }
    | INTERFACE
    {
        logs.push(Token{TokenType::NODE_TYPE, "Interface"});
    }
    | METACLASS
    {
        logs.push(Token{TokenType::NODE_TYPE, "Metaclass"});
    }
    | PROTOCOL
    {
        logs.push(Token{TokenType::NODE_TYPE, "Protocol"});
    }
    | STEREOTYPE
    {
        logs.push(Token{TokenType::NODE_TYPE, "Stereotype"});
    }
    | STRUCT
    {
        logs.push(Token{TokenType::NODE_TYPE, "Struct"});
    }
    ;

node_body:
    node_body node_element
    | node_element
    ;

node_element:
    QUOTE extensions
    | attribute
    | method
    ;


extensions:
    extensions extension
    | extension
    ;

extension:
    position
    | position_fixed
    | SKIP_LAYOUT {
        logs.push(Token{TokenType::SKIP_LAYOUT, std::string("")});
    }

position:
    AT_POSITION POSITION_ARGS
    {
        logs.push(Token{TokenType::POSITION, std::string($2)});
        free($2);
    }
    ;

position_fixed:
    AT_POSITION_FIXED POSITION_ARGS
    {
        logs.push(Token{TokenType::POSITION_FIXED, std::string($2)});
        free($2);
    }
    ;

skip_layoutt:
    QUOTE SKIP_LAYOUT
    {
        logs.push(Token{TokenType::SKIP_LAYOUT, std::string("")});
    }
    | %empty
    ;

attribute:
    IDENTIFIER LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::ATTRIBUTE, std::string($1) + " " + RemoveLastChar(std::string($2))});
        free($1);
    }
    | LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::ATTRIBUTE, RemoveLastChar(std::string($1))});
        free($1);
    }
    ;

method:
    IDENTIFIER IDENTIFIER LBRACE RBRACE
    {
        logs.push(Token{TokenType::METHOD, std::string($1) + " " + std::string($2)});
        free($1);
        free($2);
    }
    |
    IDENTIFIER LBRACE RBRACE
    {
        logs.push(Token{TokenType::METHOD, std::string($1)});
        free($1);
    }
    | IDENTIFIER LBRACE method_arguments RBRACE
    {
        logs.push(Token{TokenType::METHOD, std::string($1)});
        free($1);
    }
    | IDENTIFIER IDENTIFIER LBRACE method_arguments RBRACE
    {
        logs.push(Token{TokenType::METHOD, std::string($1) + " " + std::string($2)});
        free($1);
        free($2);
    }
    ;

method_arguments:
    method_arguments COMMA IDENTIFIER IDENTIFIER
    {
        logs.push(Token{TokenType::METHOD_ARGUMENT, std::string($3) + " " + std::string($4)});
        free($3);
        free($4);
    }
    |
    method_arguments COMMA IDENTIFIER
    {
        logs.push(Token{TokenType::METHOD_ARGUMENT, std::string($3)});
        free($3);
    }
    | IDENTIFIER IDENTIFIER
    {
        logs.push(Token{TokenType::METHOD_ARGUMENT, std::string($1) + " " + std::string($2)});
        free($1);
        free($2);
    }
    | IDENTIFIER
    {
        logs.push(Token{TokenType::METHOD_ARGUMENT, std::string($1)});
        free($1);
    }
    ;

relationship:
    IDENTIFIER HYPHEN HYPHEN LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        logs.push(Token{TokenType::NODE_NAME, std::string($1)});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string($4))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free($1);
        free($4);
    }
    | IDENTIFIER HYPHEN HYPHEN right_connection LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::NODE_NAME, std::string($1)});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string($5))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free($1);
        free($5);
    }
    | IDENTIFIER left_connection HYPHEN HYPHEN LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::NODE_NAME, std::string($1)});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string($5))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free($1);
        free($5);
    }
    | IDENTIFIER left_connection HYPHEN HYPHEN right_connection LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::NODE_NAME, std::string($1)});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string($6))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        free($1);
        free($6);
    }
    |
    IDENTIFIER HYPHEN HYPHEN IDENTIFIER skip_layoutt
    {
        logs.push(Token{TokenType::NODE_NAME, std::string($1)});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string($4))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free($1);
        free($4);
    }
    | IDENTIFIER HYPHEN HYPHEN right_connection IDENTIFIER skip_layoutt
    {
        logs.push(Token{TokenType::NODE_NAME, std::string($1)});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string($5))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free($1);
        free($5);
    }
    | IDENTIFIER left_connection HYPHEN HYPHEN IDENTIFIER skip_layoutt
    {
        logs.push(Token{TokenType::NODE_NAME, std::string($1)});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string($5))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free($1);
        free($5);
    }
    | IDENTIFIER left_connection HYPHEN HYPHEN right_connection IDENTIFIER skip_layoutt
    {
        logs.push(Token{TokenType::NODE_NAME, std::string($1)});
        logs.push(Token{TokenType::NODE_NAME, std::string($6)});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        free($1);
        free($6);
    }
    ;

relationship_with_label:
    IDENTIFIER HYPHEN HYPHEN IDENTIFIER COLON label
    {
        logs.push(Token{TokenType::NODE_NAME, std::string($1)});
        logs.push(Token{TokenType::NODE_NAME, std::string($4)});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free($1);
        free($4);
    }
    | IDENTIFIER HYPHEN HYPHEN right_connection IDENTIFIER COLON label
    {
        logs.push(Token{TokenType::NODE_NAME, std::string($1)});
        logs.push(Token{TokenType::NODE_NAME, std::string($5)});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free($1);
        free($5);
    }
    | IDENTIFIER left_connection HYPHEN HYPHEN IDENTIFIER COLON label
    {
        logs.push(Token{TokenType::NODE_NAME, std::string($1)});
        logs.push(Token{TokenType::NODE_NAME, std::string($5)});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free($1);
        free($5);
    }
    | IDENTIFIER left_connection HYPHEN HYPHEN right_connection IDENTIFIER COLON label
    {
        logs.push(Token{TokenType::NODE_NAME, std::string($1)});
        logs.push(Token{TokenType::NODE_NAME, std::string($6)});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        free($1);
        free($6);
    }
    ;


left_connection:
    L_ANGLE_BRACE PIPE
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("OpenArrow")});
    }
    | L_ANGLE_BRACE
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("Arrow")});
    }
    | R_CURLY_BRACE
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("ThreeLines")});
    }
    | connection
    ;

right_connection:
    R_ANGLE_BRACE PIPE
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("Arrow")});
    }
    | R_ANGLE_BRACE
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("Arrow")});
    }
    | L_CURLY_BRACE
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("ThreeLines")});
    }
    | connection
    ;

connection:
    STAR
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("Rhomb")});
    }
    | O
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("OpenRhomb")});
    }
    | HASH
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("Square")});
    }
    | X
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("X")});
    }
    | PLUS
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("Circle")});
    }
    | HAT
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("OpenArrow")});
    }
    ;

label:
    IDENTIFIER
    {
        logs.push(Token{TokenType::LABEL, std::string($1)});
        free($1);
    }
    |
    IDENTIFIER QUOTE SKIP_LAYOUT
    {
        logs.push(Token{TokenType::LABEL, std::string($1)});
        logs.push(Token{TokenType::SKIP_LAYOUT, std::string("")});
        free($1);
    }
    |
    IDENTIFIER QUOTE SPLIT_EDGE
    {
        logs.push(Token{TokenType::SPLIT_EDGE, "None"});
        logs.push(Token{TokenType::LABEL, std::string($1)});
        free($1);
    }
    | LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::LABEL, RemoveLastChar(std::string($1))});
        free($1);
    }
    | LINE_LAST_IDENTIFIER QUOTE SKIP_LAYOUT
    {
        logs.push(Token{TokenType::LABEL, RemoveLastChar(std::string($1))});
        logs.push(Token{TokenType::SKIP_LAYOUT, std::string("")});
        free($1);
    }
    ;

%%

void yyerror(const char *s) {
}

namespace class_diagram {
namespace generated_parser {

void clearLogs() {
   std::stack<Token> empty;
   logs.swap(empty);
}

std::stack<Token> parse_class_diagram(const std::string& input) {
    clearLogs();

    // Konwertuj std::stringbuf na FILE*
    FILE* file = fmemopen(const_cast<char*>(input.c_str()), input.size(), "r");
    if (!file) {
        perror("fmemopen");
        return {};
    }

    // Ustaw bufor jako wejście dla Flex
    yyin = file;

    int result = yyparse();
    if (result == 0) {
        std::cout << "Parsing successful!" << std::endl;
    } else {
        std::cerr << "Parsing failed!" << std::endl;
        while (!logs.empty())
        {
          const auto token = logs.top();
          std::cerr << "Detected token: " << token.type << " " << token.name << std::endl;
          logs.pop();
        }
    }

    fclose(file); // Zamknij FILE*

    return logs;
}

}}
