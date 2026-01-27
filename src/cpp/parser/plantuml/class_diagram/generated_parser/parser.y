%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <sstream>
#include <iostream>
#include <stack>
#include "generated_parser.hpp"
#include <regex>
#include <algorithm>

using Token = class_diagram::generated_parser::Token;
using TokenType = class_diagram::generated_parser::TokenType;

namespace {

std::string CleanQuotedString(std::string text) {
    if (text.empty()) return text;

    if (text.size() >= 2 && text.front() == '"' && text.back() == '"') {
        text = text.substr(1, text.size() - 2);
    }
    else {
        return text;
    }

    static const std::regex whitespace_to_space_regex("[\\t\\n\\r]+");
    text = std::regex_replace(text, whitespace_to_space_regex, " ");

    static const std::regex multiple_spaces_regex(" +");
    text = std::regex_replace(text, multiple_spaces_regex, " ");

    text.erase(0, text.find_first_not_of(" "));
    size_t last = text.find_last_not_of(" ");
    if (last != std::string::npos) {
        text.erase(last + 1);
    }

    return text;
}

std::string RemoveLastChar(const std::string &str) {
    if (str[str.size() - 1] != '\n') {
        return str;
    }
  return CleanQuotedString(str.substr(0, str.size() - 1));
}

} // namespace
std::stack<Token> logs;

void yyerror(const char *s);
extern int yylex();
extern char* yytext;
extern FILE *yyin;
extern void yyrestart(FILE* input_file);
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
%token HYPHEN DOWN UP LEFT RIGHT
%token L_ANGLE_BRACE R_ANGLE_BRACE
%token L_SQUARE_BRACE R_SQUARE_BRACE
%token L_CURLY_BRACE R_CURLY_BRACE
%token LBRACE RBRACE
%token COMMA
%token QUOTE
%token AT_POSITION AT_POSITION_FIXED SPLIT_EDGE SKIP_LAYOUT DIAGRAM_TYPE LAYOUT_TYPE EDGE_TYPE
%token <str> IDENTIFIER LINE_LAST_IDENTIFIER POSITION POSITION_FIXED POSITION_ARGS START_IDENTIFIER ATTRIBUTE
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
    |
    QUOTE ignored
    ;

ignored:
    LINE_LAST_IDENTIFIER
    {
        free($1);
    }
    | %empty
    | IDENTIFIER ignored
    {
        free($1);
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
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string($2))});
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
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string($2))});
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
    ATTRIBUTE
    {
        logs.push(Token{TokenType::ATTRIBUTE, RemoveLastChar(std::string($1))});
        free($1);
    }
    |
    START_IDENTIFIER LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::ATTRIBUTE, std::string($1) + " " + RemoveLastChar(std::string($2))});
        free($1);
        free($2);
    }
    | HYPHEN IDENTIFIER LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::ATTRIBUTE, "- " + std::string($2) + " " + RemoveLastChar(std::string($3))});
        free($2);
        free($3);
    }
    | HYPHEN LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::ATTRIBUTE, "- " + RemoveLastChar(std::string($2))});
        free($2);
    }
    | PLUS IDENTIFIER LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::ATTRIBUTE, "+ " + CleanQuotedString(std::string($2)) + " " + RemoveLastChar(std::string($3))});
        free($2);
        free($3);
    }
    | PLUS LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::ATTRIBUTE, "+ " + RemoveLastChar(std::string($2))});
        free($2);
    }
    | HASH IDENTIFIER LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::ATTRIBUTE, "# " + CleanQuotedString(std::string($2)) + " " + RemoveLastChar(std::string($3))});
        free($2);
        free($3);
    }
    | HASH LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::ATTRIBUTE, "# " + RemoveLastChar(std::string($2))});
        free($2);
    }
    | IDENTIFIER LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::ATTRIBUTE, CleanQuotedString(std::string($1)) + " " + RemoveLastChar(std::string($2))});
        free($1);
        free($2);
    }
    | LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::ATTRIBUTE, RemoveLastChar(std::string($1))});
        free($1);
    }
    ;

method:
    START_IDENTIFIER IDENTIFIER LBRACE RBRACE
    {
        logs.push(Token{TokenType::METHOD, std::string($1) + " " + CleanQuotedString(std::string($2))});
        free($1);
        free($2);
    }
    |
    START_IDENTIFIER LBRACE RBRACE
    {
        logs.push(Token{TokenType::METHOD, std::string($1)});
        free($1);
    }
    | START_IDENTIFIER LBRACE method_arguments RBRACE
    {
        logs.push(Token{TokenType::METHOD, std::string($1)});
        free($1);
    }
    | START_IDENTIFIER IDENTIFIER LBRACE method_arguments RBRACE
    {
        logs.push(Token{TokenType::METHOD, std::string($1) + " " + CleanQuotedString(std::string($2))});
        free($1);
        free($2);
    }
    |
    HYPHEN IDENTIFIER IDENTIFIER LBRACE RBRACE
    {
        logs.push(Token{TokenType::METHOD, "- " + CleanQuotedString(std::string($2)) + " " + CleanQuotedString(std::string($3))});
        free($2);
        free($3);
    }
    |
    HYPHEN IDENTIFIER LBRACE RBRACE
    {
        logs.push(Token{TokenType::METHOD, "- " + CleanQuotedString(std::string($2))});
        free($2);
    }
    |
    HYPHEN IDENTIFIER LBRACE method_arguments RBRACE
    {
        logs.push(Token{TokenType::METHOD, "- " + CleanQuotedString(std::string($2))});
        free($2);
    }
    |
    HYPHEN IDENTIFIER IDENTIFIER LBRACE method_arguments RBRACE
    {
        logs.push(Token{TokenType::METHOD, "- " + CleanQuotedString(std::string($2)) + " " + CleanQuotedString(std::string($3))});
        free($2);
        free($3);
    }
    |
    PLUS IDENTIFIER IDENTIFIER LBRACE RBRACE
    {
        logs.push(Token{TokenType::METHOD, "+ " + CleanQuotedString(std::string($2)) + " " + CleanQuotedString(std::string($3))});
        free($2);
        free($3);
    }
    |
    PLUS IDENTIFIER LBRACE RBRACE
    {
        logs.push(Token{TokenType::METHOD, "+ " + CleanQuotedString(std::string($2))});
        free($2);
    }
    |
    PLUS IDENTIFIER LBRACE method_arguments RBRACE
    {
        logs.push(Token{TokenType::METHOD, "+ " + CleanQuotedString(std::string($2))});
        free($2);
    }
    |
    PLUS IDENTIFIER IDENTIFIER LBRACE method_arguments RBRACE
    {
        logs.push(Token{TokenType::METHOD, "+ " + CleanQuotedString(std::string($2)) + " " + CleanQuotedString(std::string($3))});
        free($2);
        free($3);
    }
    |
    HASH IDENTIFIER IDENTIFIER LBRACE RBRACE
    {
        logs.push(Token{TokenType::METHOD, "# " + CleanQuotedString(std::string($2)) + " " + CleanQuotedString(std::string($3))});
        free($2);
        free($3);
    }
    |
    HASH IDENTIFIER LBRACE RBRACE
    {
        logs.push(Token{TokenType::METHOD, "# " + CleanQuotedString(std::string($2))});
        free($2);
    }
    |
    HASH IDENTIFIER LBRACE method_arguments RBRACE
    {
        logs.push(Token{TokenType::METHOD, "# " + CleanQuotedString(std::string($2))});
        free($2);
    }
    |
    HASH IDENTIFIER IDENTIFIER LBRACE method_arguments RBRACE
    {
        logs.push(Token{TokenType::METHOD, "# " + CleanQuotedString(std::string($2)) + " " + CleanQuotedString(std::string($3))});
        free($2);
        free($3);
    }
    |
    IDENTIFIER IDENTIFIER LBRACE RBRACE
    {
        logs.push(Token{TokenType::METHOD, CleanQuotedString(std::string($1)) + " " + CleanQuotedString(std::string($2))});
        free($1);
        free($2);
    }
    |
    IDENTIFIER LBRACE RBRACE
    {
        logs.push(Token{TokenType::METHOD, CleanQuotedString(std::string($1))});
        free($1);
    }
    | IDENTIFIER LBRACE method_arguments RBRACE
    {
        logs.push(Token{TokenType::METHOD, CleanQuotedString(std::string($1))});
        free($1);
    }
    | IDENTIFIER IDENTIFIER LBRACE method_arguments RBRACE
    {
        logs.push(Token{TokenType::METHOD, CleanQuotedString(std::string($1)) + " " + CleanQuotedString(std::string($2))});
        free($1);
        free($2);
    }
    ;

method_arguments:
    method_arguments COMMA IDENTIFIER IDENTIFIER
    {
        logs.push(Token{TokenType::METHOD_ARGUMENT, CleanQuotedString(std::string($3)) + " " + CleanQuotedString(std::string($4))});
        free($3);
        free($4);
    }
    |
    method_arguments COMMA IDENTIFIER
    {
        logs.push(Token{TokenType::METHOD_ARGUMENT, CleanQuotedString(std::string($3))});
        free($3);
    }
    | IDENTIFIER IDENTIFIER
    {
        logs.push(Token{TokenType::METHOD_ARGUMENT, CleanQuotedString(std::string($1)) + " " + CleanQuotedString(std::string($2))});
        free($1);
        free($2);
    }
    | IDENTIFIER
    {
        logs.push(Token{TokenType::METHOD_ARGUMENT, CleanQuotedString(std::string($1))});
        free($1);
    }
    ;

hyphen_with_direction:
    HYPHEN
    | HYPHEN LEFT
    | HYPHEN RIGHT
    | HYPHEN UP
    | HYPHEN DOWN
    ;

relationship:
    IDENTIFIER hyphen_with_direction HYPHEN LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string($1))});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string($4))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free($1);
        free($4);
    }
    | IDENTIFIER hyphen_with_direction HYPHEN right_connection LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string($1))});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string($5))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free($1);
        free($5);
    }
    | IDENTIFIER left_connection hyphen_with_direction HYPHEN LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string($1))});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string($5))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        free($1);
        free($5);
    }
    | IDENTIFIER left_connection hyphen_with_direction HYPHEN right_connection LINE_LAST_IDENTIFIER
    {
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string($1))});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string($6))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        free($1);
        free($6);
    }
    |
    IDENTIFIER hyphen_with_direction HYPHEN IDENTIFIER skip_layoutt
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string($1))});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string($4))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free($1);
        free($4);
    }
    | IDENTIFIER hyphen_with_direction HYPHEN right_connection IDENTIFIER skip_layoutt
    {
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string($1))});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string($5))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free($1);
        free($5);
    }
    | IDENTIFIER left_connection hyphen_with_direction HYPHEN IDENTIFIER skip_layoutt
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string($1))});
        logs.push(Token{TokenType::NODE_NAME, RemoveLastChar(std::string($5))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        free($1);
        free($5);
    }
    | IDENTIFIER left_connection hyphen_with_direction HYPHEN right_connection IDENTIFIER skip_layoutt
    {
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string($1))});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string($6))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        free($1);
        free($6);
    }
    ;

relationship_with_label:
    IDENTIFIER hyphen_with_direction HYPHEN IDENTIFIER COLON label
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        logs.push(Token{TokenType::LABEL, std::string("")});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string($1))});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string($4))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free($1);
        free($4);
    }
    | IDENTIFIER hyphen_with_direction HYPHEN right_connection IDENTIFIER COLON label
    {
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string($1))});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string($5))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        free($1);
        free($5);
    }
    | IDENTIFIER left_connection hyphen_with_direction HYPHEN IDENTIFIER COLON label
    {
        logs.push(Token{TokenType::ARROW_HEAD, std::string("None")});
        logs.push(Token{TokenType::LABEL, std::string("")});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string($1))});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string($5))});
        logs.push(Token{TokenType::LINE, std::string("Hyphen")});
        free($1);
        free($5);
    }
    | IDENTIFIER left_connection hyphen_with_direction HYPHEN right_connection IDENTIFIER COLON label
    {
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string($1))});
        logs.push(Token{TokenType::NODE_NAME, CleanQuotedString(std::string($6))});
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
        logs.push(Token{TokenType::LABEL, CleanQuotedString(std::string($1))});
        free($1);
    }
    |
    IDENTIFIER QUOTE SKIP_LAYOUT
    {
        logs.push(Token{TokenType::LABEL, CleanQuotedString(std::string($1))});
        logs.push(Token{TokenType::SKIP_LAYOUT, std::string("")});
        free($1);
    }
    |
    IDENTIFIER QUOTE SPLIT_EDGE
    {
        logs.push(Token{TokenType::SPLIT_EDGE, "None"});
        logs.push(Token{TokenType::LABEL, CleanQuotedString(std::string($1))});
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
  class_diagram::generated_parser::FillLastError("Error: " + std::string(s) + " Field: " + std::string(yytext));
fprintf(stderr, "Error: %s. Field: %s\n", s, yytext);
}

namespace class_diagram {
namespace generated_parser {

void clearLogs() {
   std::stack<Token> empty;
   logs.swap(empty);
}


std::pair<std::string, std::stack<Token>> parse_class_diagram(const std::string& input) {
    clearLogs();

    // Convert std::stringbuf to FILE*
    FILE* file = fmemopen(const_cast<char*>(input.c_str()), input.size(), "r");
    if (!file) {
        perror("fmemopen");
        return {};
    }

    // Set buffer as input for Flex
    yyrestart(file);
    std::string result_string{};

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
        result_string += GetLastError() + "\n";
    }

    fclose(file); // Zamknij FILE*

    return std::make_pair(result_string, logs);
}

}}
