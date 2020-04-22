//parser.h
#include "collection.h"
#ifndef PARSER_H
#define PARSER_H

formula* createClauses();
monoClause* generateMonoClauses(formula* clauses);
monoClause* addSorted(monoClause*, literal* expression);
void freeClause(clause* expression);
void freeFormula(formula* expression);
void contains(ltieral* expression1, literal* expression2);
#endif
