//collection.h
#ifndef COLLECTION_H
#define COLLECTION_H
#define NEGATIVE 0
#define POSITIVE 1
#define TRUE 1
#define FALSE 0
#define contradiction int
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

/*
* Stores a found literall and wether it is true or faslse.
*/
typedef struct _literal {
  //The name of the literals
  char* unitName;
  int type;
} literal;

/*
* Stores a found clause
*/
typedef struct _clause {
  //All the literals which make can be found by traversing the clause.
  literal* clauseName;
  struct _clause* next;
} clause;

/*
* Stores all the clauses that make up the formula which has been provided into program.
*/
typedef struct _formula {
  // stores the next clauses which make up the formula.
  //All clauses can be found by traversing this linked list.
  clause* formulaName;
  struct _formula* next;
} formula;

/*
* Stores all the unit clauses that make the program.
*/
typedef struct _monoClause {
  //the name of the unit clauses.
  literal* unitClause;
  struct _monoClause* next;
} monoClause;
#endif
