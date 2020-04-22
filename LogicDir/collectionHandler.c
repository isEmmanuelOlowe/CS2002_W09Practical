#include "collection.h"

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
    freeClause(temp->formulaName);
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

literal* generateLiteral(char *name) {
  literal* expression = (literal *) malloc(sizeof(literal));
  if (name[0] == '-'){
    expression->unitName = name + 1;
    expression->type = NEGATIVE;
  }
  else {
    expression->unitName = name;
    expression->type = POSITIVE;
  }
  return expression;
}

clause* generateClause(char *line) {
  contradiction invalid = FALSE;
  clause* base = (clause *) malloc(sizeof(clause));
  char* temp = malloc(strlen(line) + 1);
  if (temp == NULL) exit(0);
  strcpy(temp,line);
  char* expression = strtok(temp, " \n\t\r");
  clause* current = base;
  current->clauseName = NULL;
  current->next = NULL;
  while (expression != NULL) {
    if (strcmp(expression, "\n") == 0) {
      invalid = TRUE;
      break;
    }
    if (current->clauseName == NULL) {
      current->clauseName = generateLiteral(expression);
    }
    else {
      current->next = (clause *) malloc(sizeof(clause));
      current->next->clauseName = generateLiteral(expression);
      current->next->next = NULL;
      current = current->next;
    }
    expression = strtok(NULL, " \n\t\r");
  }
  if (invalid == TRUE) {
    return NULL;
  }
  return base;
}

//need to free dynamically allocated space
formula* createClauses() {
  contradiction invalid = FALSE;
  formula* base = (formula *) malloc(sizeof(formula));
  formula* current = base;
  current->formulaName = NULL;
  char * string = NULL;
  unsigned long newsize = 0;

  while(getline(&string, &newsize, stdin) != -1) {

    if (base->formulaName == NULL) {
     current->formulaName = generateClause(string);
     current->next = NULL;
    }
    else {
      current->next = (formula *) malloc(sizeof(formula));
      current->next->formulaName = generateClause(string);
      current->next->next = NULL;
      current = current->next;
    }
   if (current->formulaName == NULL) {
     invalid = TRUE;
     break;
   }
  }
  if (invalid == TRUE) {
    freeFormula(base);
    return NULL;
  }
  return base;
}

monoClause* generateMonoClauses(formula* clauses) {
  formula* currentFormula = clauses;
  monoClause* base = (monoClause *) malloc(sizeof(monoClause));
  monoClause* currentClause = base;
  currentClause->unitClause = NULL;
  currentClause->next = NULL;
  while (currentFormula != NULL){
    // check if it's monoclause
    if (currentFormula->formulaName->next == NULL) {      //check if it is the first to be added to mono clause linked list.
      if(currentClause->unitClause == NULL) {
        currentClause->unitClause = currentFormula->formulaName->clauseName;
      }
      else {
        currentClause->next = (monoClause *) malloc(sizeof(monoClause));
        currentClause->next->unitClause = currentFormula->formulaName->clauseName;
        currentClause->next->next = NULL;
        currentClause = currentClause->next;
      }
    }
    currentFormula = currentFormula->next;
  }

  if (base-> unitClause == NULL){
    free(base);
    return NULL;
  }
  return base;
}

monoClause* addSorted(monoClause* mono, literal* expression) {
  if (mono == NULL) {
    mono = (monoClause *) malloc(sizeof(monoClause));
    mono->unitClause = expression;
    mono->next = NULL;
    return mono;
  }
  else if (strcmp(mono->unitClause->unitName, expression->unitName) > 0) {
    monoClause* newItem = (monoClause *) malloc(sizeof(monoClause));
    newItem->unitClause = expression;
    newItem->next = mono;
    return newItem;
  }
  else {
    mono->next = addSorted(mono->next, expression);
    return mono;
  }
}
