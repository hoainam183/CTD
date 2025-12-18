/* 
 * @copyright (c) 2008, Hedspi, Hanoi University of Technology
 * @author Huu-Duc Nguyen
 * @version 1.0
 */

#include <stdlib.h>
#include <string.h>
#include "semantics.h"
#include "error.h"

extern SymTab* symtab;
extern Token* currentToken;

Object* lookupObject(char *name) {
  // Search in current scope and outer scopes
  Scope* scope = symtab->currentScope;
  Object* obj;
  
  while (scope != NULL) {
    obj = findObject(scope->objList, name);
    if (obj != NULL) return obj;
    scope = scope->outer;
  }
  
  // Search in global object list (predefined functions/procedures)
  obj = findObject(symtab->globalObjectList, name);
  return obj;
}

void checkFreshIdent(char *name) {
  // Check if identifier already declared in current scope
  if (findObject(symtab->currentScope->objList, name) != NULL) {
    error(ERR_DUPLICATE_IDENT, currentToken->lineNo, currentToken->colNo);
  }
}

Object* checkDeclaredIdent(char* name) {
  // Check if identifier is declared
  Object* obj = lookupObject(name);
  if (obj == NULL) {
    error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
  }
  return obj;
}

Object* checkDeclaredConstant(char* name) {
  // Check if identifier is declared as a constant
  Object* obj = lookupObject(name);
  if (obj == NULL) {
    error(ERR_UNDECLARED_CONSTANT, currentToken->lineNo, currentToken->colNo);
  } else if (obj->kind != OBJ_CONSTANT) {
    error(ERR_INVALID_CONSTANT, currentToken->lineNo, currentToken->colNo);
  }
  return obj;
}

Object* checkDeclaredType(char* name) {
  // Check if identifier is declared as a type
  Object* obj = lookupObject(name);
  if (obj == NULL) {
    error(ERR_UNDECLARED_TYPE, currentToken->lineNo, currentToken->colNo);
  } else if (obj->kind != OBJ_TYPE) {
    error(ERR_INVALID_TYPE, currentToken->lineNo, currentToken->colNo);
  }
  return obj;
}

Object* checkDeclaredVariable(char* name) {
  // Check if identifier is declared as a variable
  Object* obj = lookupObject(name);
  if (obj == NULL) {
    error(ERR_UNDECLARED_VARIABLE, currentToken->lineNo, currentToken->colNo);
  } else if (obj->kind != OBJ_VARIABLE) {
    error(ERR_INVALID_VARIABLE, currentToken->lineNo, currentToken->colNo);
  }
  return obj;
}

Object* checkDeclaredFunction(char* name) {
  // Check if identifier is declared as a function
  Object* obj = lookupObject(name);
  if (obj == NULL) {
    error(ERR_UNDECLARED_FUNCTION, currentToken->lineNo, currentToken->colNo);
  } else if (obj->kind != OBJ_FUNCTION) {
    error(ERR_INVALID_FUNCTION, currentToken->lineNo, currentToken->colNo);
  }
  return obj;
}

Object* checkDeclaredProcedure(char* name) {
  // Check if identifier is declared as a procedure
  Object* obj = lookupObject(name);
  if (obj == NULL) {
    error(ERR_UNDECLARED_PROCEDURE, currentToken->lineNo, currentToken->colNo);
  } else if (obj->kind != OBJ_PROCEDURE) {
    error(ERR_INVALID_PROCEDURE, currentToken->lineNo, currentToken->colNo);
  }
  return obj;
}

Object* checkDeclaredLValueIdent(char* name) {
  // Check if identifier is declared and can be assigned (variable, function, or parameter)
  Object* obj = lookupObject(name);
  if (obj == NULL) {
    error(ERR_UNDECLARED_IDENT, currentToken->lineNo, currentToken->colNo);
  } else if (obj->kind != OBJ_VARIABLE && obj->kind != OBJ_FUNCTION && obj->kind != OBJ_PARAMETER) {
    error(ERR_INVALID_LVALUE, currentToken->lineNo, currentToken->colNo);
  }
  return obj;
}

