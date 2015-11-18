#include "symbol.hpp"

// Symbol Visitor Functions: These are the functions you will
// complete to build the symbol table. Not all functions must
// have code, many may be left empty.

void Symbol::visitProgramNode(ProgramNode* node) {
    // WRITEME: Replace with code if necessary
    this->classTable = new ClassTable;
    node->visit_children(this);

}

void Symbol::visitClassNode(ClassNode* node) {
    // WRITEME: Replace with code if necessary
    std::list<std::string> superNames;
    std::string className = "";
    if(node->identifier_2 != NULL)
        className = node->identifier_2->name;
    while(className != ""){
        superNames.push_front(className);
        className = (*classTable)[className].superClassName;
    }
    ClassInfo* newClassInfo = new ClassInfo;
    currentLocalOffset = 1;
    currentMemberOffset = 0;
    for(std::list<std::string>::iterator iter = superNames.begin();
        iter != superNames.end(); iter++){
        VariableTable m = (*classTable)[*iter].members;
        for(VariableTable::iterator it = m.begin(); it != m.end(); it++){
            VariableInfo* newVarInfo = new VariableInfo();
            newVarInfo->type = (it->second).type;
            newVarInfo->offset = currentMemberOffset;
            newVarInfo->size = (it->second).size;
            newClassInfo->membersSize += 4;
            currentMemberOffset += 4;
            (newClassInfo->members)[it->first] = (*newVarInfo);
        }
    }
    this->currentMethodTable = &(newClassInfo->methods);
    this->currentVariableTable = &(newClassInfo->members);
    node->visit_children(this);
    if(node->identifier_2 != NULL)
        newClassInfo->superClassName = node->identifier_2->name;
    else 
        newClassInfo->superClassName = "";
    newClassInfo->membersSize = currentMemberOffset;
    (*classTable)[node->identifier_1->name] = *newClassInfo;
}

void Symbol::visitMethodNode(MethodNode* node) {
    // WRITEME: Replace with code if necessary
    MethodInfo* newMethodInfo = new MethodInfo;
    this->currentVariableTable = &(newMethodInfo->variables);
    currentLocalOffset = -4;
    currentParameterOffset = 12;
    node->visit_children(this);
    newMethodInfo->localsSize = -(currentLocalOffset + 4); //ASK, BITCH!!
    newMethodInfo->returnType.baseType = node->type->basetype;
    newMethodInfo->returnType.objectClassName = "";
    if(newMethodInfo->returnType.baseType == bt_object)
        newMethodInfo->returnType.objectClassName = ((ObjectTypeNode*)(node->type))->identifier->name;
    (*currentMethodTable)[node->identifier->name] = *newMethodInfo;
    currentLocalOffset = 1;
}

void Symbol::visitMethodBodyNode(MethodBodyNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);
}

void Symbol::visitParameterNode(ParameterNode* node) {
    // WRITEME: Replace with code if necessary
    VariableInfo* newVariableInfo = new VariableInfo;
    node->visit_children(this);
    newVariableInfo->offset = currentParameterOffset;
    currentParameterOffset += 4;
    newVariableInfo->size = 4;
    newVariableInfo->type.baseType = node->type->basetype;
    newVariableInfo->type.objectClassName = "";
    if(newVariableInfo->type.baseType == bt_object)
        newVariableInfo->type.objectClassName = ((ObjectTypeNode*)(node->type))->identifier->name;
    (*currentVariableTable)[node->identifier->name] = *newVariableInfo;


}

void Symbol::visitDeclarationNode(DeclarationNode* node) {
    // WRITEME: Replace with code if necessary
    node->visit_children(this);


    if(currentLocalOffset < 1){
        for(std::list<IdentifierNode*>::iterator iter = node->identifier_list->begin();
        iter != node->identifier_list->end(); iter++){
            VariableInfo* newVariableInfo = new VariableInfo;
            newVariableInfo->size = 4;
            newVariableInfo->offset = currentLocalOffset;
            currentLocalOffset -= 4;
            newVariableInfo->type.baseType = node->type->basetype;
            newVariableInfo->type.objectClassName = "";
            if(newVariableInfo->type.baseType == bt_object)
                newVariableInfo->type.objectClassName = ((ObjectTypeNode*)(node->type))->identifier->name;
            (*currentVariableTable)[(*iter)->name] = *newVariableInfo;
        }
    }

    else{
        for(std::list<IdentifierNode*>::iterator iter = node->identifier_list->begin();
        iter != node->identifier_list->end(); iter++){
            VariableInfo* newVariableInfo = new VariableInfo;
            newVariableInfo->size = 4;
            newVariableInfo->offset = currentMemberOffset;
            currentMemberOffset += 4;
            newVariableInfo->type.baseType = node->type->basetype;
            newVariableInfo->type.objectClassName = "";
            if(newVariableInfo->type.baseType == bt_object)
                newVariableInfo->type.objectClassName = ((ObjectTypeNode*)(node->type))->identifier->name;
            (*currentVariableTable)[(*iter)->name] = *newVariableInfo;
        }        
    }
}

void Symbol::visitReturnStatementNode(ReturnStatementNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitAssignmentNode(AssignmentNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitCallNode(CallNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIfElseNode(IfElseNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitForNode(ForNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitPrintNode(PrintNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitPlusNode(PlusNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitMinusNode(MinusNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitTimesNode(TimesNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitDivideNode(DivideNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitLessNode(LessNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitLessEqualNode(LessEqualNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitEqualNode(EqualNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitAndNode(AndNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitOrNode(OrNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitNotNode(NotNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitNegationNode(NegationNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitMethodCallNode(MethodCallNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitMemberAccessNode(MemberAccessNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitVariableNode(VariableNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIntegerLiteralNode(IntegerLiteralNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitBooleanLiteralNode(BooleanLiteralNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitNewNode(NewNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIntegerTypeNode(IntegerTypeNode* node) {
    // WRITEME: Replace with code if necessary
    node->basetype = bt_integer;
}

void Symbol::visitBooleanTypeNode(BooleanTypeNode* node) {
    // WRITEME: Replace with code if necessary
    node->basetype = bt_boolean;
}

void Symbol::visitObjectTypeNode(ObjectTypeNode* node) {
    // WRITEME: Replace with code if necessary
    node->basetype = bt_object;
}

void Symbol::visitNoneNode(NoneNode* node) {
    // WRITEME: Replace with code if necessary
    node->basetype = bt_none;
}

void Symbol::visitIdentifierNode(IdentifierNode* node) {
    // WRITEME: Replace with code if necessary
}

void Symbol::visitIntegerNode(IntegerNode* node) {
    // WRITEME: Replace with code if necessary
}
