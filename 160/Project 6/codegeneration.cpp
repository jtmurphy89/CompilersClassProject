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
    std::cout << "#### PROGRAM" << std::endl;
    std::cout << " .data" << std::endl;
    std::cout << " printstr: .asciz \"%d\\n\"" << std::endl;
    std::cout << " .text" << std::endl;
    std::cout << ".globl Main_main" << std::endl;
    currentLabel = 0;
    node->visit_children(this);
    std::cout << "#### END PROGRAM" << std::endl;
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
    node->expression->accept(this);
    std::cout << " pop %eax" << std::endl;
    int localOffset = 0;
    if(currentClassInfo.members.count(node->identifier->name) == 1){
        std::cout << " mov 8(%ebp), %ebx" << std::endl; 
        localOffset = currentClassInfo.members[node->identifier->name].offset;
        std::cout << " mov %eax, " << localOffset << "(%ebx)" << std::endl;
    }
    else{
        localOffset = currentMethodInfo.variables[node->identifier->name].offset;
        std::cout << " mov %eax, " << localOffset << "(%ebp)" << std::endl;
    }
}

void CodeGenerator::visitCallNode(CallNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
}

void CodeGenerator::visitIfElseNode(IfElseNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### IFELSE" << std::endl;
    int label1 = nextLabel();
    int label2 = nextLabel();
    node->expression->accept(this);

    std::cout << "pop %eax" << std::endl;
    std::cout << "mov $0, %ebx" << std::endl;
    std::cout << "cmp %eax, %ebx" << std::endl;
    std::cout << "je Label_" << label1 << std::endl;
    for(std::list<StatementNode*>::iterator iter = node->statement_list_1->begin();
        iter != node->statement_list_1->end(); iter++)
        (*iter)->accept(this);
    std::cout << "jmp END_" << label2 << std::endl;
    std::cout << "Label_" << label1 << ":" << std::endl;
    if(node->statement_list_2 == NULL)
        std::cout << "jmp END_" << label2 << std::endl;
    else{
        for(std::list<StatementNode*>::iterator iter = node->statement_list_2->begin();
            iter != node->statement_list_2->end(); iter++)
            (*iter)->accept(this);
        }
    std::cout << "END_" << label2 << ":" << std::endl;


}

void CodeGenerator::visitForNode(ForNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### FOR" << std::endl;
    int label1 = nextLabel();
    int label2 = nextLabel();
    node->assignment_1->accept(this);
    std::cout << "Label_" << label1 << ":" << std::endl;
    node->expression->accept(this);
    std::cout << "pop %eax" << std::endl;
    std::cout << "mov $0, %ebx" << std::endl;
    std::cout << "cmp %eax, %ebx" << std::endl;
    std::cout << "je END_" << label2 << std::endl;
    if(node->statement_list != NULL){
        for(std::list<StatementNode*>::iterator iter = node->statement_list->begin();
            iter != node->statement_list->end(); iter++)
                (*iter)->accept(this);
    }
    node->assignment_2->accept(this);
    std::cout << "jmp Label_" << label1 << std::endl;

    std::cout << "END_" << label2 << ":" << std::endl;
}

void CodeGenerator::visitPrintNode(PrintNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### PRINT" << std::endl;
    node->visit_children(this);
    std::cout << " push $printstr" << std::endl;
    std::cout << " call printf" << std::endl;
    std::cout << "#### END PRINT" << std::endl;
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
    int label1 = nextLabel();
    int label2 = nextLabel();
    std::cout << "#### LESSTHAN" << std::endl;
    node->visit_children(this);
    std::cout << " pop %ebx" << std::endl;
    std::cout << " pop %eax" << std::endl;
    std::cout << " cmp %ebx, %eax" << std::endl;
    std::cout << " jl LessThan_" << label1 << std::endl;
    std::cout << " push $0" << std::endl;
    std::cout << " jmp RETURN_" << label2 << std::endl;
    std::cout << " LessThan_" << label1 << ":" << std::endl;
    std::cout << " push $1" << std::endl;
    std::cout << " RETURN_" << label2 << ":" << std::endl;
}

void CodeGenerator::visitLessEqualNode(LessEqualNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### LESSTHANEQUAL" << std::endl;
    int label1 = nextLabel();
    int label2 = nextLabel();
    node->visit_children(this);
    std::cout << " pop %ebx" << std::endl;
    std::cout << " pop %eax" << std::endl;
    std::cout << " cmp %ebx, %eax" << std::endl;
    std::cout << " jle LEQ_" << label1 << std::endl;
    std::cout << " push $0" << std::endl;
    std::cout << " jmp RETURN_" << label2 << std::endl;
    std::cout << " LEQ_" << label1 << ":" << std::endl;
    std::cout << " push $1" << std::endl;
    std::cout << " RETURN_" << label2 << ":" << std::endl;
}

void CodeGenerator::visitEqualNode(EqualNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### LESSTHAN" << std::endl;
    int label1 = nextLabel();
    int label2 = nextLabel();
    node->visit_children(this);
    std::cout << " pop %ebx" << std::endl;
    std::cout << " pop %eax" << std::endl;
    std::cout << " cmp %ebx, %eax" << std::endl;
    std::cout << " je EQ_" << label1 << std::endl;
    std::cout << " push $0" << std::endl;
    std::cout << " jmp RETURN_" << label2 << std::endl;
    std::cout << " EQ_" << label1 << ":" << std::endl;
    std::cout << " push $1" << std::endl;
    std::cout << " RETURN_" << label2 << ":" << std::endl;
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
    std::cout << " mov $1, %ebx" << std::endl;
    std::cout << " sub %eax, %ebx" << std::endl;
    std::cout << " push %ebx" << std::endl;
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
    std::list<std::string> superNames;
    std::string className = "";
    if(node->identifier_2 != NULL)
        className = node->identifier_2->name;
    while(className != ""){
        superNames.push_back(className);
        className = (*classTable)[className].superClassName;
    }
    std::string MethodName;
    std::string ClassName;
    ClassInfo* CorrectClassInfo; 
    std::string CorrectClassName; 
    std::string ObjName;
    if(node->identifier_2 == NULL){
        MethodName = node->identifier_1->name; 
        CorrectClassName = currentClassName;
        CorrectClassInfo = &currentClassInfo;
    }
    else{

        MethodName = node->identifier_2->name; 
        ObjName = node->identifier_1->name; 
        if(currentMethodInfo.variables.count(ObjName) == 1){
            CorrectClassName = (currentMethodInfo.variables[ObjName]).type.objectClassName;
            CorrectClassInfo = &(*classTable)[CorrectClassName];
        }
        else{
            CorrectClassName = (currentClassInfo.members[ObjName]).type.objectClassName;
            CorrectClassInfo = &(*classTable)[CorrectClassName];
        }
    }
    while(CorrectClassInfo->methods.count(MethodName) == 0){
        CorrectClassName = CorrectClassInfo->superClassName;
        CorrectClassInfo = &(*classTable)[CorrectClassName];
    }
    std::cout << "#### PRE-CALL" << std::endl;
    std::cout << " push %ecx" << std::endl;
    std::cout << " push %edx" << std::endl;
    int counter = 0;
    if(node->expression_list != NULL){
        for(std::list<ExpressionNode*>::reverse_iterator rit = node->expression_list->rbegin(); rit != node->expression_list->rend(); ++rit){
            (*rit)->accept(this);
            counter += 4; 
        }
    }
    if(node->identifier_2 == NULL){
        std::cout << " push 8(%ebp)" << std::endl;
        counter += 4; 
    }
    else {
        if(currentMethodInfo.variables.count(ObjName) == 1){
                int localOffset = (currentMethodInfo.variables[ObjName]).offset;
                std::cout << " push " << localOffset << "(%ebp)" << std::endl;
                counter += 4; 
        }
        else{
            std::cout << " mov 8(%ebp), %eax" << std::endl;
            int localOffset = (currentClassInfo.members[ObjName]).offset;
            std::cout << " push " << localOffset << "(%eax)" << std::endl;
            counter += 4;
        }
    }
    std::cout << "#### END PRE-CALL" << std::endl; 
    std::cout << " call " << CorrectClassName << "_" << MethodName << std::endl;
    std::cout << "#### POST-CALL" << std::endl;
    std::cout << " add $" << counter << ", %esp" << std::endl;
    std::cout << " pop %edx" << std::endl;
    std::cout << " pop %ecx" << std::endl; 
    if(((*CorrectClassInfo).methods[MethodName]).returnType.baseType != bt_none)
        std::cout << " push %eax" << std::endl;
}

void CodeGenerator::visitMemberAccessNode(MemberAccessNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### MEMBER ACCESS" << std::endl; 
    if(currentMethodInfo.variables.count(node->identifier_1->name) == 1){
        int localOffset = (currentMethodInfo.variables[node->identifier_1->name]).offset; 
        std::cout << " mov " << localOffset << "(%ebp), %eax" << std::endl;
        int localMemberOffset = ((*classTable)[(currentMethodInfo.variables[node->identifier_1->name]).type.objectClassName]).members[node->identifier_2->name].offset;
        std::cout << " push " << localMemberOffset << "(%eax)" << std::endl;
    }
    else{
        std::cout << " mov 8(%ebp), %eax" << std::endl;
        int localOffset = (currentClassInfo.members[node->identifier_1->name]).offset; 
        std::cout << " mov " << localOffset << "(%eax), %ebx" << std::endl;
        int localMemberOffset = ((*classTable)[(currentClassInfo.members[node->identifier_1->name]).type.objectClassName]).members[node->identifier_2->name].offset;
        std::cout << " push " << localMemberOffset << "(%ebx)" << std::endl;
    }
}

void CodeGenerator::visitVariableNode(VariableNode* node) {
    // WRITEME: Replace with code if necessary
    std::cout << "#### VARIABLE" << std::endl;
    int localOffset = 0;
    if(currentClassInfo.members.count(node->identifier->name) == 1){
        std::cout << " mov 8(%ebp), %ebx" << std::endl; 
        localOffset = currentClassInfo.members[node->identifier->name].offset;
        std::cout << " push " << localOffset << "(%ebx)" << std::endl;
    }
    else{
        localOffset = currentMethodInfo.variables[node->identifier->name].offset;
        std::cout << " push " << localOffset << "(%ebp)" << std::endl;
    }
    std::cout << "#### END VARIABLE" << std::endl;
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
    std::cout << "#### NEW" << std::endl;
    int MemSize = ((*classTable)[node->identifier->name]).membersSize;
    std::cout << " push $" << MemSize << std::endl;
    std::cout << " call malloc" << std::endl;
    std::cout << " add $4, %esp" << std::endl;
    if((*classTable)[node->identifier->name].methods.count(node->identifier->name) == 1){
        std::cout << "#### PRE-CALL" << std::endl;
        std::cout << " push %ecx" << std::endl;
        std::cout << " push %edx" << std::endl;
        int counter = 0;
        if(node->expression_list != NULL){
            for(std::list<ExpressionNode*>::reverse_iterator rit = node->expression_list->rbegin(); rit != node->expression_list->rend(); ++rit){
                (*rit)->accept(this);
                counter += 4; 
            }
        }
        std::cout << " push %eax" << std::endl;
        counter +=4;
        std::cout << "#### END PRE-CALL" << std::endl; 
        std::cout << " call " << node->identifier->name << "_" << node->identifier->name << std::endl;
        std::cout << "#### POST-CALL" << std::endl;
        std::cout << " add $" << counter << ", %esp" << std::endl;
        std::cout << " pop %edx" << std::endl;
        std::cout << " pop %ecx" << std::endl;
        std::cout << "#### END POST-CALL" << std::endl;
    }
    std::cout << " push %eax" << std::endl;
    std::cout << "#### END NEW" << std::endl;
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
