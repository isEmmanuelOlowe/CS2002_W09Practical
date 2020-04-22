#include "collection.h"

/*
* Free a clause and all the units contianed within it.
*/
void freeClause(clause* expression) {
  clause* current = expression;
  //runs through entire linked list.
  while(current!=NULL) {
    clause* temp = current;
    current = current->next;
    free(temp->clauseName);
    free(temp);
  }
}

/*
* Frees a formula and all the clauses with that formula.
*/
void freeFormula(formula* expression) {
  formula* current = expression;
  //runs through the entire linked list.
  while(current!=NULL) {
    formula* temp = current;
    current = current->next;
    //frees the units contained within that clause.
    freeClause(temp->formulaName);
    free(temp);
  }
}

/*
* Compares 2 literals together to determine if there are the same.
*/
int contains(literal* expression1, literal* expression2) {
  if (strcmp(expression1->unitName, expression2->unitName) == 0) {
    if (expression1->type == expression2->type) {
      //if they are the same.
      return POSITIVE;
    }
    else {
      //if one is the negation of the other.
      return NEGATIVE;
    }
  }
  //If they are not the same.
  return - 1;
}

/*
* Dynamically creates space for a literal.
*/
literal* generateLiteral(char *name) {
  literal* expression = (literal *) malloc(sizeof(literal));
  //checks if the literal is negative.
  if (name[0] == '-'){
    //does not include the negative in the name literal.
    expression->unitName = name + 1;
    expression->type = NEGATIVE;
  }
  else {
    expression->unitName = name;
    expression->type = POSITIVE;
  }
  //returns the generated expression
  return expression;
}

/*
* Generates unit clauses from a line in the
*/
clause* generateClause(char *line) {
  //in the event there is a contradiction
  contradiction invalid = TRUE;
  //creates space to store the clause
  clause* base = (clause *) malloc(sizeof(clause));
  //creates space to store char
  char* temp = malloc(strlen(line) + 1);
  //copies the string to new line
  strcpy(temp,line);
  //tokenises the line spliting by white space.
  char* expression = strtok(temp, " \n\t\r");
  clause* current = base;
  current->clauseName = NULL;
  current->next = NULL;
  //loops unit a literal has been generated for each token.
  while (expression != NULL) {
    //If it runs atleast 1 time must be valid.
    invalid = FALSE;
    if (strcmp(expression, "\n") == 0) {
      invalid = TRUE;
      break;
    }
    //checks if it the head of the linked list.
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
  //checks if the
  if (invalid == TRUE) {
    return NULL;
  }
  //returns the created clause.
  return base;
}

/*
* Creates all the formulas which make up the stored clauses
*/
formula* createClauses() {
  //assumes there is a contradiction
  contradiction invalid = TRUE;
  formula* base = (formula *) malloc(sizeof(formula));
  formula* current = base;
  current->formulaName = NULL;
  char * string = NULL;
  unsigned long newsize = 0;
  while(getline(&string, &newsize, stdin) != -1) {
    //checks the first line is not empty
    if (invalid == TRUE && strcmp(string, "") == 0){
      break;
    }
    else {
      invalid = FALSE;
    }
    //checks if it is the head of the linked list.
    if (base->formulaName == NULL) {
     current->formulaName = generateClause(string);
     current->next = NULL;
    }
    else {
      //adds it to the next node along
      current->next = (formula *) malloc(sizeof(formula));
      current->next->formulaName = generateClause(string);
      current->next->next = NULL;
      current = current->next;
    }
   if (current->formulaName == NULL) {
     //breaks if invalid
     invalid = TRUE;
     break;
   }
  }
  //checks that the node was not invalid.
  if (invalid == TRUE) {
    //frees space created for base if the node was invalid.
    freeFormula(base);
    return NULL;
  }
  return base;
}

/*
* Generates a unit clauses from the formulas.
* Looks for clauses which don't have a next.
*/
monoClause* generateMonoClauses(formula* clauses) {
  //stores the current formula ndoe being loops over.
  formula* currentFormula = clauses;
  //stores the head of the linked list that will store the unit clauses found
  monoClause* base = (monoClause *) malloc(sizeof(monoClause));
  monoClause* currentClause = base;
  //initialies its members to NULL
  currentClause->unitClause = NULL;
  currentClause->next = NULL;
  while (currentFormula != NULL){
    // check if it's unit clause
    //by definition it will be the only literal in that clause.
    if (currentFormula->formulaName->next == NULL) {
      //checks if this is the head of the linked list.
      if(currentClause->unitClause == NULL) {
        //adds it to the head
        currentClause->unitClause = currentFormula->formulaName->clauseName;
      }
      else {
        //adds it to the next node.
        currentClause->next = (monoClause *) malloc(sizeof(monoClause));
        currentClause->next->unitClause = currentFormula->formulaName->clauseName;
        currentClause->next->next = NULL;
        currentClause = currentClause->next;
      }
    }
    //goes to the next node to loop.
    currentFormula = currentFormula->next;
  }

  //checsk atleast 1 item was added to the linked list.
  if (base-> unitClause == NULL){
    //if not frees the space created for base.
    free(base);
    return NULL;
  }
  return base;
}

//adds the mono clauses to a new mono clause in a sorted order.
monoClause* addSorted(monoClause* mono, literal* expression) {
  //checks if the current mono is null.
  if (mono == NULL) {
    mono = (monoClause *) malloc(sizeof(monoClause));
    mono->unitClause = expression;
    mono->next = NULL;
    return mono;
  }
  else if (strcmp(mono->unitClause->unitName, expression->unitName) > 0) {
    //swithces order of current mono and next.
    monoClause* newItem = (monoClause *) malloc(sizeof(monoClause));
    newItem->unitClause = expression;
    newItem->next = mono;
    return newItem;
  }
  else {
    //recursives runs on the next node.
    mono->next = addSorted(mono->next, expression);
    return mono;
  }
}
