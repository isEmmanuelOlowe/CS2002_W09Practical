#include "collection.h"

//
literal* generateLiteral(char *name) {
  literal* expression = (literal *) malloc(sizeof(unit));
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

//need to free dynamically allocated space
formula* createClauses() {
  contradiction invalid = FALSE;
  formula* base = (formula *) malloc(sizeof(formula));
  formula* current = base;
  current->fname = NULL;
  char * string = NULL;
  unsigned long newsize = 0;

  while(getline(&string, &newsize, stdin) != -1) {

    if (base->fname == NULL) {
     current->fname = generateClause(string);
     current->next = NULL;
    }
    else {
      current->next = (formula *) malloc(sizeof(formula));
      current->next->fname = generateClause(string);
      current->next->next = NULL;
      current = current->next;
    }
   if (current->fname == NULL) {
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

//free dynamically allocated space.
clause* generateClause(char *line) {
  contradiction invalid = FALSE;
  clause* base = (clause *) malloc(sizeof(clause));
  //makes a new string
  // char temp[strlen(line)];
  //this is correct way
  // strncpy(temp, line,strlen(line));
  // temp[strlen(line)] = '\0';
  // printf("temp is: %s\n", temp);
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

monoClause* generateMonoClauses(formula* clauses) {
  formula* currentFormula = clauses;
  monoClause* base = (monoClause *) malloc(sizeof(monoClause));
  monoClause* currentClause = base;
  currentClause->unitClause = NULL;
  currentClause->next = NULL;
  while (currentFormula != NULL){
    // check if it's monoclause
    if (currentFormula->fname->next == NULL) {      //check if it is the first to be added to mono clause linked list.
      if(currentClause->unitClause == NULL) {
        currentClause->unitClause = currentFormula->fname->clauseName;
        //currentFormula->fname = NULL;
      }
      else {
        currentClause->next = (monoClause *) malloc(sizeof(monoClause));
        currentClause->next->unitClause = currentFormula->fname->clauseName;
        currentClause->next->next = NULL;
        currentClause = currentClause->next;
      }
      //currentFormula->fname = NULL;
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
