%option yylineno
%pointer

%{
    #include <stdlib.h>
    #include <errno.h>
    #include <limits.h>
    #include "ast.hpp"
    #include "parser.hpp"
    #include <string.h>
    void yyerror(const char *);
%}



%x comment

%%

"/*"         BEGIN(comment);
     
         <comment>[^*\n]*        /* eat anything that's not a '*' */
         <comment>"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s */
         <comment>\n             
         <comment>"*"+"/"        BEGIN(INITIAL);


 <INITIAL>{

and {return T_AND;} 
or {return T_OR;}
for {return T_FOR;}
not {return T_NOT;}
true {return T_TRUE;}
false {return T_FALSE;}
new {return T_NEW;}
print {return T_PRINT;}
if {return T_IF;}
else {return T_ELSE;}
int {return T_INT;}
bool {return T_BOOL;}
none {return T_NONE;}
return {return T_RETURN;}
"{" {return T_OPENBRACE;}
"}" {return T_CLOSEBRACE;}
"(" {return T_OPENPAREN;}
")" {return T_CLOSEPAREN;}
";" {return T_SEMICOLON;}
"," {return T_COMMA;}
":" {return T_COLON;}
"." {return T_DOT;}
"+" {return T_PLUS;}
"-" {return T_MINUS;}
"*" {return T_MULTIPLY;}
"/" {return T_DIVIDE;}
"<" {return T_LE;}
"<=" {return T_LEQ;}
"==" {return T_EQUALS;}
"=" {return T_EQUAL;}
[ \t\r] ;
[\n] ;
[a-zA-Z][a-zA-Z0-9]* {yylval.base_char_ptr = strdup(yytext); return T_IDENTIFIER;}
0|[1-9][0-9]* {yylval.base_int = atoi(yytext);return T_NUMBER;}

.                 { yyerror("invalid character"); }

}


%%

int yywrap(void) {
  return 1;
}

