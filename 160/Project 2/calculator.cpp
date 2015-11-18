#include <iostream>
#include <string>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <typeinfo>
#include <ctype.h>


// This is the token type, and contains all possible tokens in our language.
typedef enum {
    T_PLUS,
    T_MINUS,
    T_MULTIPLY,
    T_POWER,
    T_DIVIDE,
    T_OPENPAREN,
    T_CLOSEPAREN,
    T_OPENBRACKET,
    T_CLOSEBRACKET,
    T_EQUALS,
    T_SEMICOLON,
    T_M,
    T_PRINT,
    T_NUMBER,
    T_EOF
} token;

// This function will convert a token to a string, for display.
std::string tokenToString(token toConvert) {
    switch (toConvert) {
        case T_PLUS:
            return std::string("+");
        case T_MINUS:
            return std::string("-");
        case T_MULTIPLY:
            return std::string("*");
        case T_POWER:
            return std::string("**");
        case T_DIVIDE:
            return std::string("/");
        case T_OPENPAREN:
            return std::string("(");
        case T_CLOSEPAREN:
            return std::string(")");
        case T_OPENBRACKET:
            return std::string("[");
        case T_CLOSEBRACKET:
            return std::string("]");
        case T_EQUALS:
            return std::string("=");
        case T_SEMICOLON:
            return std::string(";");
        case T_M:
            return std::string("M");
        case T_PRINT:
            return std::string("print");
        case T_NUMBER:
            return std::string("number");
        case T_EOF:
            return std::string("EOF");
    }
}

// Throw this error when the parser expects a given token from the scanner
// and the next token the scanner finds does not match.
void mismatchError(int line, token expected, token found) {
    std::cerr << "Parse error: expected " << tokenToString(expected) << " found " << tokenToString(found) << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when the parser encounters a token that is not valid
// at the beginning of a specific grammar rule.
void parseError(int line, token found) {
    std::cerr << "Parse error: found invalid token " << tokenToString(found) << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when an invalid character is found in the input, or
// if a bad character is found as part of a print token.
void scanError(int line, char badCharacter) {
    std::cerr << "Scan error: found invalid character " << badCharacter << " at line " << line << std::endl;
    exit(1);
}

// Throw this error when the index for memory is out of bounds (less
// than 0 or greater than 99). ONLY THROW IF evaluate flag is true.
void indexError(int line, int index) {
    std::cerr << "Semantic error: index " << index << " out of bounds at line " << line << std::endl;
    exit(1);
}

// Throw this error when a division by zero occurs. ONLY THROW IF evaluate flag is true.
void divideError(int line) {
    std::cerr << "Semantic error: division by zero at line " << line << std::endl;
    exit(1);
}

class Scanner {
    // You are allowed to private fields to the scanner, and this may be
    // necessary to complete your implementation. However, this is not
    // required as part of the project specification.
    int lineNum = 1;
    
public:
    token nextToken(); 
    void eatToken(token);
    int lineNumber();
    int getNumberValue();
    
    // You may need to write a constructor for the scanner. This is not
    // required by the project description, but you may need it to complete
    // your implementation.
    // WRITEME

};

token Scanner::nextToken() {
    // This is a placeholder token, you will need to replace this code
    // with code to return the correct next token.
    
    // WRITEME

    char ahead;
    char l[4] = {'r', 'i','n', 't'};
    char u[4] = {'R', 'I', 'N', 'T'};
    ahead = std::cin.peek();
    if(std::cin.eof())
        return T_EOF;

    while(isspace(ahead)){
        if(ahead == '\n')
            lineNum = lineNum + 1;
       std::cin.get(ahead);
       ahead = std::cin.peek();
       if(ahead == EOF || std::cin.eof())
        return T_EOF;
    }   

    switch(ahead){
        case '0':
            return T_NUMBER;
        case '1':
            return T_NUMBER;
        case '2':
            return T_NUMBER;
        case '3':
            return T_NUMBER;
        case '4':
            return T_NUMBER;
        case '5':
            return T_NUMBER;
        case '6':
            return T_NUMBER;
        case '7':
            return T_NUMBER;
        case '8':
            return T_NUMBER;
        case '9':
            return T_NUMBER;
        case '+':
            return T_PLUS;
        case '-':
            return T_MINUS;
        case '*':
            std::cin.seekg(1,std::ios::cur);
            ahead = std::cin.peek();
            std::cin.seekg(-1,std::ios::cur);
            if(ahead == '*')
                return T_POWER;
            else 
                return T_MULTIPLY;
        case '/':
            return T_DIVIDE;
        case '(':
            return T_OPENPAREN;
        case ')':
            return T_CLOSEPAREN;
        case '[':
            return T_OPENBRACKET;
        case ']':
            return T_CLOSEBRACKET;
        case '=':
            return T_EQUALS;
        case ';':
            return T_SEMICOLON;
        case 'm': case 'M':
            return T_M;
        case 'p':
            for(int i=0; i < 4; i++){
                std::cin.seekg(i+1, std::ios::cur);
                ahead = std::cin.peek();
                std::cin.seekg(-i-1, std::ios::cur);
                if(ahead != l[i])
                    scanError(lineNumber(), ahead);
            }
            return T_PRINT;
        case 'P':
            for(int i=0; i < 4; i++){
                std::cin.seekg(i+1, std::ios::cur);
                ahead = std::cin.peek();
                std::cin.seekg(-i-1, std::ios::cur);
                if(ahead != u[i])
                    scanError(lineNumber(), ahead);
            }
            return T_PRINT;
        default: 
            scanError(lineNumber(), ahead);
            break;
    }
}

void Scanner::eatToken(token toConsume) {
    // This function consumes the next token.
    
    // WRITEME
    std::string s = tokenToString(toConsume);
    token tokenFound = nextToken();
    if(toConsume != tokenFound)
        mismatchError(lineNumber(), toConsume, tokenFound);

    if(s.length() != 6){
        for(int i = 0; i < s.length(); i++)
            std::cin.get();
    }

    if(s.length() == 6){
        char ahead = std::cin.peek();
        while(ahead <= '9' && ahead >= '0'){
            std::cin.get();
            ahead = std::cin.peek();
        }
    }


}

int Scanner::lineNumber() {
    // This is also a placeholder, you will need to replace this code
    // with code to return the current line number (to be used for errors).
    
    // WRITEME
    return lineNum;
}

int Scanner::getNumberValue() {
    // This is also a placeholder, you will need to replace this code
    // with code to return the last number value that was scanned. This
    // will be used when evaluating expressions.
    
    // WRITEME
    return 0;
}

class Parser {
    // You are allowed to private fields to the parser, and this may be
    // necessary to complete your implementation. However, this is not
    // required as part of the project specification.
    
private:
    Scanner scanner;
    
    // This flag indicates whether we should perform evaluation and throw
    // out-of-bounds and divide-by-zero errors. ONLY evaluate and throw these
    // errors if this flag is set to TRUE.
    bool evaluate;
    
    // You will need to add more methods for handling nonterminal symbols here.
    void Start();
    void Statements();
    void StatementsI();
    void Statement();
    void Expression();
    void Expressionn();
    void ExpressionI();
    void Exxpression();
    void ExpressionII();
    void Exxxpression();
    void ExpressionIII();


public:
    void parse();
    Parser(bool evaluate) : evaluate(evaluate) {
        // You may need to complete a Parser constructor here
        // WRITEME
    }
};

void Parser::parse() {
    // This is the entry point for the parser, which simply starts parsing
    // the grammar by calling the function for the start symbol.
    Start();
}

void Parser::Start() {
   
    Statements();
    switch(scanner.nextToken()){
        case T_EOF:
            break;
        default: 
            parseError(scanner.lineNumber(), scanner.nextToken());
    }
}

void Parser::Statements() {

    Statement();
    StatementsI();
}

void Parser::StatementsI() {

    if(scanner.nextToken() == T_SEMICOLON){
        scanner.eatToken(T_SEMICOLON);
        Statement();
        StatementsI();
    }
    else{
        if(scanner.nextToken() != T_EOF)
            parseError(scanner.lineNumber(), scanner.nextToken());
    }
}
void Parser::Statement() {

    switch(scanner.nextToken()){
        case T_M: 
            scanner.eatToken(T_M);
            scanner.eatToken(T_OPENBRACKET);
            Expression();
            scanner.eatToken(T_CLOSEBRACKET);
            scanner.eatToken(T_EQUALS);
            Expression();
            break;
        case T_PRINT:
            scanner.eatToken(T_PRINT);
            Expression();
            break;
        default:
            parseError(scanner.lineNumber(), scanner.nextToken());
            break;
    }
}
void Parser::Expression() {

    ExpressionI();
    Expressionn();
}

void Parser::Expressionn() {

    switch(scanner.nextToken()){
        case T_PLUS:
            scanner.eatToken(T_PLUS);
            Expression();   
            break;
        case T_MINUS: 
            scanner.eatToken(T_MINUS);
            Expression();
            break;
        default:
            if(scanner.nextToken() != T_CLOSEBRACKET && scanner.nextToken() != T_CLOSEPAREN && scanner.nextToken() != T_SEMICOLON && scanner.nextToken() != T_EOF)
                parseError(scanner.lineNumber(), scanner.nextToken());
            break;
    }
}

void Parser::ExpressionI() {

    ExpressionII();
    Exxpression();
}

void Parser::Exxpression() {

    switch(scanner.nextToken()){
        case T_MULTIPLY:
            scanner.eatToken(T_MULTIPLY);
            ExpressionI();
            break;
        case T_DIVIDE:
            scanner.eatToken(T_DIVIDE);
            ExpressionI();
            break;
        default:
            if(scanner.nextToken() != T_CLOSEBRACKET && scanner.nextToken() != T_CLOSEPAREN && scanner.nextToken() != T_SEMICOLON && scanner.nextToken() != T_EOF && scanner.nextToken() != T_PLUS && scanner.nextToken() != T_MINUS)
                parseError(scanner.lineNumber(), scanner.nextToken());
            break;
    }
}

void Parser::ExpressionII() {

    ExpressionIII();
    Exxxpression();
}

void Parser::Exxxpression() {

    if(scanner.nextToken() == T_POWER){
        scanner.eatToken(T_POWER);
        ExpressionII();
    }
    else{
        if(scanner.nextToken() != T_MULTIPLY && scanner.nextToken() != T_DIVIDE && scanner.nextToken() != T_CLOSEBRACKET && scanner.nextToken() != T_CLOSEPAREN && scanner.nextToken() != T_SEMICOLON && scanner.nextToken() != T_EOF && scanner.nextToken() != T_PLUS && scanner.nextToken() != T_MINUS)
            parseError(scanner.lineNumber(), scanner.nextToken());
    }
}

void Parser::ExpressionIII() {

    switch(scanner.nextToken()){
        case T_OPENPAREN: 
            scanner.eatToken(T_OPENPAREN);
            Expression();
            scanner.eatToken(T_CLOSEPAREN);
            break;
        case T_M:
            scanner.eatToken(T_M);
            scanner.eatToken(T_OPENBRACKET);
            Expression();
            scanner.eatToken(T_CLOSEBRACKET);
            break;
        case T_NUMBER:
            scanner.eatToken(T_NUMBER);
            break;
        default: 
            parseError(scanner.lineNumber(), scanner.nextToken());
            break;
    }
}


int main(int argc, char* argv[]) {
    if (argc == 2 && (strcmp(argv[1], "-s") == 0)) {
        Scanner scanner;
        while (scanner.nextToken() != T_EOF) {
            std::cout << tokenToString(scanner.nextToken()) << " ";
            scanner.eatToken(scanner.nextToken());
        }
        std::cout<<std::endl;
    } else if (argc == 2 && (strcmp(argv[1], "-e") == 0)) {
        Parser parser(true);
        parser.parse();
    } else {
        Parser parser(false);
        parser.parse();
    }
    return 0;
}
