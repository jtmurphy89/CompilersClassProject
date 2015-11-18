#include "codegeneration.hpp"

// CodeGenerator Visitor Functions: These are the functions
// you will complete to generate the x86 assembly code. Not
// all functions must have code, many may be left empty.
//
// NOTE: You only need to complete code for expressions,
// assignments, returns, and local variable space allocation.
// Refer to project description for exact details.

void CodeGenerator::visitProgramNode(ProgramNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << ".globl Main_main" << std::endl;
    node->visit_children(this);
}

void CodeGenerator::visitClassNode(ClassNode* node) {
    // WRITEME: Replace with code if necessary
    currentClassName = node->identifier_1->name;
    currentClassInfo = (*classTable)[currentClassName];
    node->visit_children(this);

}

void CodeGenerator::visitMethodNode(MethodNode* node) {
    // WRITEME: Replace with code if necessary
    currentMethodName = node->identifier->name;
    currentMethodInfo = currentClassInfo.methods[currentMethodName];
    std::cout << currentClassName << "_" << currentMethodName << ":" << std::endl;
    
    // Prologue 
    std::cout << " push %ebp" << std::endl;
    std::cout << " mov %esp, %ebp" << std::endl;
    std::cout << " sub $" << currentMethodInfo.localsSize << ", %esp" << std::endl;
    std::cout << " push %ebx" << std::endl;
    std::cout << " push %edi" << std::endl;
    std::cout << " push %esi" << std::endl;

    node->visit_children(this);

    // Epilogue 
    std::cout << " pop %esi" << std::endl;
    std::cout << " pop %edi" << std::endl;
    std::cout << " pop %ebx" << std::endl;
    std::cout << " mov %ebp, %esp" << std::endl;
    std::cout << " pop %ebp" << std::endl;
    std::cout << " ret" << std::endl;

}

void CodeGenerator::visitMethodBodyNode(MethodBodyNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
}

void CodeGenerator::visitParameterNode(ParameterNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitDeclarationNode(DeclarationNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitReturnStatementNode(ReturnStatementNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### RETURN" << std::endl;
    node->visit_children(this);
    std::cout << " pop %eax" << std::endl;
}

void CodeGenerator::visitAssignmentNode(AssignmentNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### ASSIGNMENT" << std::endl;
    node->visit_children(this);
    int offset = currentMethodInfo.variables[node->identifier->name].offset;
    std::cout << " pop %eax" << std::endl;
    std::cout << " mov %eax, " << offset << "(%ebp)" << std::endl;
}

void CodeGenerator::visitCallNode(CallNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitIfElseNode(IfElseNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitForNode(ForNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitPrintNode(PrintNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitPlusNode(PlusNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### ADD" << std::endl;
    node->visit_children(this);
    std::cout << " pop %ebx" << std::endl;
    std::cout << " pop %eax" << std::endl;
    std::cout << " add %ebx, %eax" << std::endl;
    std::cout << " push %eax" << std::endl;
}

void CodeGenerator::visitMinusNode(MinusNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### MINUS" << std::endl;
    node->visit_children(this);
    std::cout << " pop %ebx" << std::endl;
    std::cout << " pop %eax" << std::endl;
    std::cout << " sub %ebx, %eax" << std::endl;
    std::cout << " push %eax" << std::endl;
}

void CodeGenerator::visitTimesNode(TimesNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### TIMES" << std::endl;
    node->visit_children(this);
    std::cout << " pop %ebx" << std::endl;
    std::cout << " pop %eax" << std::endl;
    std::cout << " imul %ebx, %eax" << std::endl;
    std::cout << " push %eax" << std::endl;
}

void CodeGenerator::visitDivideNode(DivideNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### DIVIDE" << std::endl;
    node->visit_children(this);
    std::cout << " pop %ebx" << std::endl;
    std::cout << " pop %eax" << std::endl;
    std::cout << " cdq" << std::endl;
    std::cout << " idiv %ebx" << std::endl;
    std::cout << " push %eax" << std::endl;
}

void CodeGenerator::visitLessNode(LessNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### LESSTHAN" << std::endl;
    node->visit_children(this);
    std::cout << " pop %ebx" << std::endl;
    std::cout << " pop %eax" << std::endl;
    std::cout << " cmp %ebx, %eax" << std::endl;
    std::cout << " jl LessThan" << std::endl;
    std::cout << " push $0" << std::endl;
    std::cout << " jmp RETURN" << std::endl;
    std::cout << " LessThan:" << std::endl;
    std::cout << " push $1" << std::endl;
    std::cout << " RETURN:" << std::endl;
}

void CodeGenerator::visitLessEqualNode(LessEqualNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### LESSTHANEQUAL" << std::endl;
    node->visit_children(this);
    std::cout << " pop %ebx" << std::endl;
    std::cout << " pop %eax" << std::endl;
    std::cout << " cmp %ebx, %eax" << std::endl;
    std::cout << " jle LEQ" << std::endl;
    std::cout << " push $0" << std::endl;
    std::cout << " jmp RETURN" << std::endl;
    std::cout << " LEQ:" << std::endl;
    std::cout << " push $1" << std::endl;
    std::cout << " RETURN:" << std::endl;
}

void CodeGenerator::visitEqualNode(EqualNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### LESSTHAN" << std::endl;
    node->visit_children(this);
    std::cout << " pop %ebx" << std::endl;
    std::cout << " pop %eax" << std::endl;
    std::cout << " cmp %ebx, %eax" << std::endl;
    std::cout << " je EQ" << std::endl;
    std::cout << " push $0" << std::endl;
    std::cout << " jmp RETURN" << std::endl;
    std::cout << " EQ:" << std::endl;
    std::cout << " push $1" << std::endl;
    std::cout << " RETURN:" << std::endl;
}

void CodeGenerator::visitAndNode(AndNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### AND" << std::endl;
    node->visit_children(this);
    std::cout << " pop %ebx" << std::endl;
    std::cout << " pop %eax" << std::endl;
    std::cout << " and %ebx, %eax" << std::endl;
    std::cout << " push %eax" << std::endl;
}

void CodeGenerator::visitOrNode(OrNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### OR" << std::endl;
    node->visit_children(this);
    std::cout << " pop %ebx" << std::endl;
    std::cout << " pop %eax" << std::endl;
    std::cout << " or %ebx, %eax" << std::endl;
    std::cout << " push %eax" << std::endl;
}

void CodeGenerator::visitNotNode(NotNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### NOT" << std::endl;
    node->visit_children(this);
    std::cout << " pop %eax" << std::endl;
    std::cout << " not %eax" << std::endl;
    std::cout << " push %eax" << std::endl;
}

void CodeGenerator::visitNegationNode(NegationNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### NEG" << std::endl;
    node->visit_children(this);
    std::cout << " pop %eax" << std::endl;
    std::cout << " neg %eax" << std::endl;
    std::cout << " push %eax" << std::endl;
}

void CodeGenerator::visitMethodCallNode(MethodCallNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitMemberAccessNode(MemberAccessNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitVariableNode(VariableNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### VARIABLE" << std::endl;
    int offset = currentMethodInfo.variables[node->identifier->name].offset;
    std::cout << " push " << offset << "(%ebp)" << std::endl;
}

void CodeGenerator::visitIntegerLiteralNode(IntegerLiteralNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
}

void CodeGenerator::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
}

void CodeGenerator::visitNewNode(NewNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitIntegerTypeNode(IntegerTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitBooleanTypeNode(BooleanTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitObjectTypeNode(ObjectTypeNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitNoneNode(NoneNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitIdentifierNode(IdentifierNode* node) {
    // WRITEME: Replace with code if necessary
}

void CodeGenerator::visitIntegerNode(IntegerNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### INTEGER" << std::endl;
    std::cout << " push $" << node->value << std::endl;
}
