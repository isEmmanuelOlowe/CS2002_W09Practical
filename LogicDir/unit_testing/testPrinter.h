//printer.h
#include "../collection.h"
#ifndef TESTPRINTER_H
#define TESTPRINTER_H

void printEmpty();
void printContradiction();
void printFound(monoClause* foundClauses);
void printUnit(literal* expression);

#endif
