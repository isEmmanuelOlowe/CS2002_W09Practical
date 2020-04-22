#ifndef PROPOGATE_H
#define PROPOGATE_H

void determineUnitClauses();
void freeFormula(formula* expression);
int contains(literal* expression1, literal* expression2);
void freeClause(clause* expression);
clause* propogate(monoClause* mono, clause* expression);
formula* unitPropogation(monoClause* mono, formula* clauses);
monoClause* propogateOver(monoClause* unitClauses, formula* clauses);
#endif
