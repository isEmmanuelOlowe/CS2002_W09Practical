#include "collection.h"

/*
* Prints nothing as no unit clauses were found.
* Then Exits program
*/
void printEmpty() {
  printf("");
  exit(1);
}

/*
* Prints a dash in the event a contradiction is found.
* Then Exits Program
*/
void printContradiction(){
  printf("-");
  exit(1);
}

/*
* Prints a unit clause.
* Adds - if it is negative.
*/
void printUnit(literal* expression) {
  //Checks if it a positive or negative literal.
  if (expression->type == POSITIVE) {
    printf("%s", expression->unitName);
  }
  else {
    // Adds a dash if it is a negative literal.
    printf("-%s", expression->unitName);
  }
}


/**
* Prints all the found mono clauses which are obtainable through exhaustive unit propogation.
* Adds a space between them.
* No space is added at the end.
*/
void printFound(monoClause* foundClauses) {
  int first = TRUE;
  monoClause* current = foundClauses;
  //Since it is non-empty there must be atleast 1 unit clause present.
  //prints the remaining unit clauses obtianable.
  while(current != NULL) {
    //skips empty literals
    if (strcmp(current->unitClause->unitName, "") != 0){
      if (first == FALSE) {
        printf(" ");
      }
      else {
        first = FALSE;
      }
      printUnit(current->unitClause);
    }
    current = current->next;
  }
}
