%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <iostream>
    #include "ast.hpp"
    
    #define YYDEBUG 1
    int yylex(void);
    void yyerror(const char *);
    
    extern ASTNode* astRoot;
%}

%error-verbose

/* WRITEME: Copy your token and precedence specifiers from Project 3 here */

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

/* ALL TERMINALS */
%type <base_char_ptr> T_IDENTIFIER
%type <base_int> T_NUMBER

/* ALL NONTERMINALS */
%type <program_ptr> SS
%type <class_list_ptr> ClassI
%type <class_ptr> Class
%type <declaration_list_ptr> M
%type <method_list_ptr> MM
%type <declaration_ptr> MD 
%type <method_ptr> MMD
%type <type_ptr> Type 
%type <type_ptr> ReturnType
%type <parameter_list_ptr> As
%type <parameter_ptr> Argument 
%type <methodbody_ptr> Body
%type <declaration_list_ptr> BDS
%type <declaration_ptr> BD
%type <identifier_list_ptr> Is
%type <returnstatement_ptr> RS
%type <statement_list_ptr> Statements
%type <statement_ptr> Statement
%type <assignment_ptr> Assignment
%type <ifelse_ptr> IfElse
%type <for_ptr> ForLoop
%type <print_ptr> Print
%type <expression_ptr> Expression
%type <methodcall_ptr> MethodCall
%type <expression_list_ptr> Parameterss
%type <expression_list_ptr> Parameters 
%%


SS : ClassI Class {$$ = new ProgramNode($1); $1->push_back($2); astRoot = $$;}
      ;

ClassI : ClassI Class {$$ = $1; $1->push_back($2);}
        | {$$ = new std::list<ClassNode*>();}
        ;

Class : T_IDENTIFIER T_COLON T_IDENTIFIER T_OPENBRACE M MM T_CLOSEBRACE {$$ = new ClassNode(new IdentifierNode($1), new IdentifierNode($3), $5, $6);}
      | T_IDENTIFIER T_OPENBRACE M MM T_CLOSEBRACE {$$ = new ClassNode(new IdentifierNode($1), NULL, $3, $4);}
      ;

M : M MD {$$ = $1; $$->push_back($2);}
        | {$$ = new std::list<DeclarationNode*>();}
        ;

MM : MMD MM {$$ = $2; $$->push_front($1);}
        | {$$ = new std::list<MethodNode*>();}
        ;

MD : Type T_IDENTIFIER {$$ = new DeclarationNode($1, new std::list<IdentifierNode*>(1,new IdentifierNode($2)));}
                  ;

MMD : T_IDENTIFIER T_OPENPAREN As T_CLOSEPAREN  T_COLON ReturnType T_OPENBRACE Body T_CLOSEBRACE {$$ = new MethodNode(new IdentifierNode($1), $3, $6, $8);}
                  ;

Type : T_IDENTIFIER {$$ = new ObjectTypeNode(new IdentifierNode($1));}
     | T_INT {$$ = new IntegerTypeNode();}
     | T_BOOL {$$ = new BooleanTypeNode();}
     ;

ReturnType : Type {$$ = $1;}
           | T_NONE {$$ = new NoneNode();}
           ;

As : As T_COMMA Argument {$$ = $1; $$->push_back($3);}
          | Argument {$$ = new std::list<ParameterNode*>(); $$->push_back($1);}
          | {$$ = new std::list<ParameterNode*>();}
          ;

Argument : Type T_IDENTIFIER {$$ = new ParameterNode($1, new IdentifierNode($2));}
         ;

Body : BDS Statements RS {$$ = new MethodBodyNode($1,$2,$3);}
     ;

BDS : BDS BD {$$ = $1; $$->push_back($2);}
                 | {$$ = new std::list<DeclarationNode*>();}
                 ;

BD : Type Is {$$ = new DeclarationNode($1,$2);}
                ;

Is : T_IDENTIFIER {$$ = new std::list<IdentifierNode*>(); $$->push_back(new IdentifierNode($1));} 
            | Is T_COMMA T_IDENTIFIER {$$ = $1; $$->push_back(new IdentifierNode($3));}
            ;

RS : T_RETURN Expression {$$ = new ReturnStatementNode($2);}
                | {$$ = NULL;}
                ;

Statements : Statement Statements {$$ = $2; $2->push_front($1);}
          | {$$ = new std::list<StatementNode*>();}
          ;

Statement : Assignment {$$ = $1;}
          | MethodCall {$$ = new CallNode($1);}
          | IfElse {$$ = $1;}
          | ForLoop {$$ = $1;}
          | Print {$$ = $1;}
          ;

Assignment : T_IDENTIFIER T_EQUAL Expression {$$ = new AssignmentNode(new IdentifierNode($1), $3);}
           ;

IfElse : T_IF Expression T_OPENBRACE Statement Statements T_CLOSEBRACE {$5->push_front($4); $$ = new IfElseNode($2,$5, NULL);}
       | T_IF Expression T_OPENBRACE Statement Statements T_CLOSEBRACE T_ELSE T_OPENBRACE Statement Statements T_CLOSEBRACE {$5->push_front($4); $10->push_front($9); $$ = new IfElseNode($2, $5, $10); }
       ;



ForLoop : T_FOR Assignment T_SEMICOLON Expression T_SEMICOLON Assignment T_OPENBRACE Statement Statements T_CLOSEBRACE {$9->push_front($8); $$ = new ForNode($2, $4, $6, $9);}
        ;




Print : T_PRINT Expression {$$ = new PrintNode($2);}
      ;


Expression : Expression T_PLUS Expression {$$ = new PlusNode($1, $3);}
           | Expression T_MINUS Expression {$$ = new MinusNode($1,$3);}
           | Expression T_MULTIPLY Expression {$$ = new TimesNode($1,$3);}
           | Expression T_DIVIDE Expression {$$ = new DivideNode($1,$3);}
           | Expression T_LE Expression {$$ = new LessNode($1,$3);}
           | Expression T_LEQ Expression {$$ = new LessEqualNode($1,$3);}
           | Expression T_EQUALS Expression {$$ = new EqualNode($1,$3);}
           | Expression T_AND Expression {$$ = new AndNode($1,$3);}
           | Expression T_OR Expression {$$ = new OrNode($1,$3);}
           | T_NOT Expression {$$ = new NotNode($2);}
           | T_MINUS Expression %prec T_NOT {$$ = new NegationNode($2);}
           | T_IDENTIFIER {$$ = new VariableNode(new IdentifierNode($1));}
           | T_IDENTIFIER T_DOT T_IDENTIFIER {$$ = new MemberAccessNode(new IdentifierNode($1), new IdentifierNode($3));}
           | MethodCall {$$ = $1;}
           | T_OPENPAREN Expression T_CLOSEPAREN {$$ = $2;}
           | T_NUMBER {$$ = new IntegerLiteralNode(new IntegerNode($1));}
           | T_TRUE {$$ = new BooleanLiteralNode(new IntegerNode(1));}
           | T_FALSE {$$ = new BooleanLiteralNode(new IntegerNode(0));}
           | T_NEW T_IDENTIFIER {$$ = new NewNode(new IdentifierNode($2), NULL);}
           | T_NEW T_IDENTIFIER T_OPENPAREN Parameters T_CLOSEPAREN {$$ = new NewNode(new IdentifierNode($2), $4);}
           ;

MethodCall : T_IDENTIFIER T_OPENPAREN Parameters T_CLOSEPAREN {$$ = new MethodCallNode(new IdentifierNode($1), NULL, $3);}
           | T_IDENTIFIER T_DOT T_IDENTIFIER T_OPENPAREN Parameters T_CLOSEPAREN {$$ = new MethodCallNode(new IdentifierNode($1), new IdentifierNode($3), $5);}
           ;

Parameters : Parameterss {$$ = $1;}
           | {$$ = new std::list<ExpressionNode*>();}
           ;

Parameterss : Parameterss T_COMMA Expression {$$ = $1; $$->push_back($3);}
            | Expression {$$ = new std::list<ExpressionNode*>(); $$->push_back($1);}
            ;



%%

extern int yylineno;

void yyerror(const char *s) {
  fprintf(stderr, "%s at line %d\n", s, yylineno);
  exit(0);
}
