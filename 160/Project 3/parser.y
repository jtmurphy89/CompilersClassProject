%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>
    #define YYDEBUG 1

    int yylex(void);
    void yyerror(const char *);
%}

%error-verbose

/* WRITEME: List all your tokens here */

%token T_NUMBER
%left T_OR
%left T_AND
%left T_LE T_LEQ T_EQUALS
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE
%right T_NOT 
%token T_FOR
%token T_EQUAL
%token T_NOT
%token T_IDENTIFIER
%token T_TRUE
%token T_FALSE
%token T_NEW
%token T_PRINT
%token T_IF
%token T_ELSE
%token T_INT
%token T_BOOL
%token T_NONE
%token T_COLON
%token T_RETURN
%token T_OPENBRACE
%token T_CLOSEBRACE
%token T_OPENBRACKET
%token T_CLOSEBRACKET
%token T_OPENPAREN
%token T_CLOSEPAREN
%token T_SEMICOLON
%token T_COMMA
%token T_DOT

%%

/* WRITEME: This rule is a placeholder, since Bison requires
            at least one rule to run successfully. Replace
            this with your appropriate start rules. */
S : ClassI Class
      ;

ClassI : ClassI Class
        | 
        ;

Class : T_IDENTIFIER T_COLON T_IDENTIFIER T_OPENBRACE M MM T_CLOSEBRACE
      | T_IDENTIFIER T_OPENBRACE M MM T_CLOSEBRACE
      ;

M : M MD
        | 
        ;

MM : MMD MM
        |
        ;

MD : Type T_IDENTIFIER
                  ;

MMD : T_IDENTIFIER T_OPENPAREN As T_CLOSEPAREN  T_COLON ReturnType T_OPENBRACE Body T_CLOSEBRACE
                  ;

Type : T_IDENTIFIER
     | T_INT
     | T_BOOL
     ;

ReturnType : Type 
           | T_NONE
           ;

As : As T_COMMA Argument
          | Argument
          |
          ;

Argument : Type T_IDENTIFIER
         ;

Body : BDS Statements RS
     ;

BDS : BDS BD
                 | 
                 ;

BD : Type Is
                ;

Is : T_IDENTIFIER
            | Is T_COMMA T_IDENTIFIER
            ;
RS : T_RETURN Expression 
                |
                ;


Statements : Statement Statements
          | 
          ;







Statement : Assignment 
          | MethodCall
          | IfElse
          | ForLoop 
          | Print
          ;




Assignment : T_IDENTIFIER T_EQUAL Expression
           ;




IfElse : T_IF Expression T_OPENBRACE Statement Statements T_CLOSEBRACE
       | T_IF Expression T_OPENBRACE Statement Statements T_CLOSEBRACE T_ELSE T_OPENBRACE Statement Statements T_CLOSEBRACE
       ;



ForLoop : T_FOR Assignment T_SEMICOLON Expression T_SEMICOLON Assignment T_OPENBRACE Statement Statements T_CLOSEBRACE
        ;




Print : T_PRINT Expression
      ;


Expression : Expression T_PLUS Expression
           | Expression T_MINUS Expression
           | Expression T_MULTIPLY Expression
           | Expression T_DIVIDE Expression 
           | Expression T_LE Expression 
           | Expression T_LEQ Expression
           | Expression T_EQUALS Expression
           | Expression T_AND Expression
           | Expression T_OR Expression
           | T_NOT Expression
           | T_MINUS Expression %prec T_NOT
           | T_IDENTIFIER
           | T_IDENTIFIER T_DOT T_IDENTIFIER
           | MethodCall
           | T_OPENPAREN Expression T_CLOSEPAREN
           | T_NUMBER
           | T_TRUE
           | T_FALSE
           | T_NEW T_IDENTIFIER
           | T_NEW T_IDENTIFIER T_OPENPAREN Parameters T_CLOSEPAREN
           ;

MethodCall : T_IDENTIFIER T_OPENPAREN Parameters T_CLOSEPAREN
           | T_IDENTIFIER T_DOT T_IDENTIFIER T_OPENPAREN Parameters T_CLOSEPAREN
           ;

Parameters : Parameterss
           | 
           ;

Parameterss : Parameterss T_COMMA Expression
            | Expression
            ;



%%

extern int yylineno;

void yyerror(const char *s) {
  fprintf(stderr, "%s at line %d\n", s, yylineno);
  exit(0);
}
