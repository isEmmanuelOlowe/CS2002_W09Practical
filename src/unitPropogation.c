#include "collection.h"
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>



void determineUnitClauses(int lines, char **expression) {
  formula* clauses = createClauses(lines, expression);
  if (clauses == NULL) {
    printContradiction();
  }

  monoClause* unitClauses = generateMonoClauses(clauses);
  if (unitClauses == NULL) {
    printEmpty();
  }

  monoClause* foundClauses = propogateOver(unitClauses, clauses);
  if (foundClauses == NULL) {
    printContradiction();
  }
  else {
    printFound(foundClauses);
  }
}

void printUnit(unit * expression) {
  if (expression->type == POSITIVE) {
    printf("%s", expression->uname);
  }
  else {
    printf("-%s", expression->uname);
  }
}

void printFound(monoClause* foundClauses) {
  monoClause* current = foundClauses;
  printUnit(current->mname);
  current->next;
  while(current != NULL) {
    printf(" ");
    printUnit(current->mname);
  }
}

void freeFormula(formula* expression) {
  formula* current = expression;
  while(current!=NULL) {
    formula* temp = current;
    current = current->next;
    freeClause(temp->fname);
    free(temp);
  }
}

int contains(unit* expression1, unit* expression2) {
  if (strcmp(expression1->uname, expression2->uname) == 0) {
    if (expression1->type == expression1->type) {
      return POSITIVE;
    }
    else {
      return NEGATIVE;
    }
  }
  return - 1;
}

void freeClause(clause* expression) {
  clause* current = expression;
  while(current!=NULL) {
    clause* temp = current;
    current = current->next;
    free(temp->cname);
    free(temp);
  }
}
clause* propogate(monoClause* mono, clause* expression) {
  clause* current = expression;
  clause* newClause = NULL;
  clause* newCurrent = NULL;
  while(current != NULL) {
    int state = contains(mono->mname, current->cname);
    if (state == POSITIVE) {
      freeClause(expression);
      return NULL;
    }
    else if (state == NEGATIVE) {
      newCurrent->next = current->next;
      free(current->cname);
      free(current);
      if (newClause->next == NULL) {
        monoClause* monoCurrent = mono;
        while(1){
          if (monoCurrent->next != NULL) {
            monoCurrent->next->mname = newClause->cname;
            newClause->cname = NULL;
            return newClause;
          }
          monoCurrent = monoCurrent->next;
        }
      }
      return newClause;
    }
    if (newClause == NULL){
      newClause = current;
      newCurrent = newClause;
    }
    else {
      newCurrent = current;
    }
  }
  return expression;
}

formula* unitPropogation(monoClause* mono, formula* clauses) {
  formula* currentFormula = clauses;
  formula* base = (formula *) malloc(sizeof(formula));
  formula* nextClauses = base;
  nextClauses-> fname = NULL;
  while(currentFormula != NULL) {
    clause* currentClause = currentFormula->fname;
    clause* newClause = propogate(mono, currentClause);
    if (newClause != NULL) {
      if (nextClauses->fname == NULL) {
        nextClauses->fname = newClause;
      }
      else {
        nextClauses->next = (formula *) malloc(sizeof(formula));
        nextClauses->next->expression = newClause;
        nextClauses = nextClauses->next;
      }
    }
    formula* temp = currentFormula;
    currentFormula = currentFormula->next;
    free(temp);
  }
  if (base->fname == NULL){
    free(base);
    return NULL;
  }
  return base;
}


monoClause* addSorted(monoClause* mono, unit* expression) {
  if (mono == NULL) {
    mono = (monoClause *) malloc(sizeof(monoClause));
    mono->mname = expression;
    return mono;
  }
  else if (strcmp(mono->mname, expression->uname) < 0) {
    monoClause* newItem = (monoClause *) malloc(sizeof(monoClause));
    newItem->mname = expression;
    newItem->next = mono;
    return newItem;
  }
  else {
    mono->next = addSorted(mono->next, expression);
  }
}

monoClause* propogateOver(monoClause* unitClauses, formula* clauses) {
  monoClause* foundClauses = (monoClause*) malloc(sizeof(monoClause));
  monoClause* current = unitClauses;
  monoClause* orderMono = NULL;
  formula* remainingClauses = clauses;
  while(current != NULL){
    remainingClauses = unitPropogation(current, remainingClauses);
    if (remainingClauses == NULL) {
      return NULL;
    }
    monoClause* temp = current;
    current = current->next;
    orderMono = addSorted(orderMono, current->mname);
    free(temp);
  }
  return orderMono;
}

void printEmpty() {
  printf("");
  exit(1);
}

monoClause* generateMonoClauses(formula* clauses) {
  formula* currentFormula = clauses;
  monoClause* base = (monoClause *) malloc(sizeof(monoClause));
  monoClause* currentClause = base;
  currentClause->mname = NULL;
  while (currentFormula!=NULL){
    if (currentFormula->fname->next == NULL) {
      if(currentClause->mname == NULL) {
        currentClause->mname = currentFormula->fname->next;
      }
      else {
        currentClause->next = (monoClause *) malloc(sizeof(monoClause));
        currentClause->next->mname = currentFormula->fname->next;
        currentClause = currentClause->next;
      }
    }
    currentFormula = currentFormula->next;
  }
  if (base-> mname == NULL){
    free(base);
    return NULL;
  }
  return base;
}

void printContradiction(){
  printf("-");
  exit(1);
}

//need to free dynamically allocated space
formula* createClauses(int lines, char **expression) {
  contradiction invalid = FALSE;
  formula* base;
  base = (formula *) malloc(sizeof(formula));
  formula* current = base;
  //ignores last line as it is empty
  for (int i = 1; i < lines - 1; i++) {
    if (current == NULL) {
      current = (formula *) malloc(sizeof(formula));
    }
   current->fname = generateClause(expression[i]);
   if (current->fname == NULL) {
     invalid = TRUE;
     break;
   }
   current = current->next;
  }
  if (invalid == TRUE) {
    return NULL;
  }
  return base;
}

//free dynamically allocated space.
clause* generateClause(char *line) {
  contradiction invalid = FALSE;
  clause* base;
  base = (clause *) malloc(sizeof(clause));
  char* expression = strtok(line, " \t");
  clause* current = base;
  current->cname = NULL;
  while (expression != NULL) {
    if (expression == "\n") {
      invalid = TRUE;
      break;
    }
    if (current->cname == NULL) {
      current->cname = generateLiteral(expression);
    }
    else {
      current->next = (clause *) malloc(sizeof(clause));
      current->next->cname = generateLiteral(expression);
      current = current->next;
    }
    expression = strtok(NULL, " \t");
  }
  if (invalid == TRUE) {
    return NULL;
  }
  return base;
}

unit* generateLiteral(char *name) {
  unit* expression = (unit *) malloc(sizeof(unit));
  if (name[0] == "-"){
    expression->uname = name + 1;
    expression->type = NEGATIVE;
  }
  else {
    expression->uname = name;
    expression->type = POSITIVE;
  }
  return expression;
}
