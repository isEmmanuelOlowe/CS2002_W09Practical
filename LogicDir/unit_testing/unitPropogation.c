#include "collection.h"
#include "testHandler.h"
#include "testPrinter.h"
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>


void determineUnitClauses() {
  formula* clauses = createClauses();
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

void freeClause(clause* expression) {
  clause* current = expression;
  while(current!=NULL) {
    clause* temp = current;
    current = current->next;
    free(temp->clauseName);
    free(temp);
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

int contains(literal* expression1, literal* expression2) {
  if (strcmp(expression1->unitName, expression2->unitName) == 0) {
    if (expression1->type == expression2->type) {
      return POSITIVE;
    }
    else {
      return NEGATIVE;
    }
  }
  return - 1;
}

clause* propogate(monoClause* mono, clause* expression) {
  clause* current = expression;
  clause* newClause = NULL;
  clause* newCurrent = NULL;
  while(current != NULL) {
    int state;
    if (mono->unitClause!=NULL && current->clauseName != NULL) {
      state = contains(mono->unitClause, current->clauseName);
    }
    else {
      state = -1;
    }
    if (state == POSITIVE) {
      freeClause(expression->next);
      expression->clauseName = NULL;
      expression->next = NULL;
      return expression;
    }
    else if (state == NEGATIVE) {
      newClause = current->next;
      free(current->clauseName);
      free(current);
      if (newCurrent == NULL) {
        newCurrent = newClause;
      }
      else {
        newCurrent->next = newClause;
      }
      if (newCurrent != NULL) {
        if (newCurrent->next == NULL) {
          while(1) {
            if (mono->next == NULL) {
              mono->next = (monoClause *) malloc(sizeof(monoClause));
              mono->next->unitClause = newCurrent->clauseName;
              // free(newCurrent);
              // newCurrent = NULL;
              return newCurrent;
            }
            mono = mono->next;
          }
        }
      }
    }
    if (newCurrent == NULL){
      newCurrent = current;
    }
    else {
      newCurrent = current;
    }
    current = current->next;
  }
  return expression;
}

formula* unitPropogation(monoClause* mono, formula* clauses) {
  formula* currentFormula = clauses;
  formula* base = (formula *) malloc(sizeof(formula));
  formula* nextClauses = base;
  int invalid = NEGATIVE;
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
        nextClauses->next->fname = newClause;
        nextClauses = nextClauses->next;
      }
    }
    else {
      invalid = POSITIVE;
      break;
    }
    currentFormula = currentFormula->next;
  }
  if (invalid == POSITIVE){
    freeFormula(base);
    return NULL;
  }
  return base;
}

monoClause* propogateOver(monoClause* unitClauses, formula* clauses) {
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
    orderMono = addSorted(orderMono, current->unitClause);
    free(temp);
  }
  return orderMono;
}
