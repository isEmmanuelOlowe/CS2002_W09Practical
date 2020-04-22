//parser.h
#include "collection.h"
#ifndef PARSER_H
#define PARSER_H

formula* createClauses();
literal* generateLiteral(char *name);
monoClause* generateMonoClauses(formula* clauses);
monoClause* addSorted(monoClause* mono, literal* expression);
#endif
