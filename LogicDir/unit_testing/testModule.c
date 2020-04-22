#include "collection.h"
#include "testHandler.h"
#include "testPrinter.h"
#include "testPropogate.h"
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
int main(int argc, char* argv[]) {
  char* a = argv[0];
  if (argc == 1) {
    printEmpty();
  }
  else if (argc == 2) {
    printContradiction();
  }
  else if (argc == 3) {
    unit unit = {"a", NEGATIVE};
    printUnit(&unit);
  }
  else if (argc == 4){
    unit unit1 = {"a", POSITIVE};
    unit unit2 = {"b", NEGATIVE};
    unit unit3 = {"c", POSITIVE};
    monoClause mono1 = {&unit1, NULL};
    monoClause mono2 = {&unit2, &mono1};
    monoClause mono3 = {&unit3, &mono2};
    printFound(&mono3);
  }
  else if (argc == 5) {
    char name[] = {"hello"};
    literal* created = generateLiteral(name);
    printUnit(created);
  }
  else if (argc == 6) {
    //defining unit clauses
    unit unit1 = {"a", POSITIVE};
    unit unit2 = {"b", NEGATIVE};
    unit unit3 = {"c", POSITIVE};
    unit unit4 = {"d", NEGATIVE};
    unit unit5 = {"e", POSITIVE};
    unit unit6 = {"f", NEGATIVE};
    unit unit7 = {"g", NEGATIVE};
    unit unit8 = {"h", POSITIVE};
    //defining the clauses and their relationhips
    clause clause3 = {&unit3, NULL};
    clause clause2 = {&unit2, &clause3};
    clause clause1 = {&unit1, &clause2};
    //unit clauses
    clause clause4 = {&unit4, NULL};
    clause clause5 = {&unit5, NULL};
    //next clause
    clause clause7 = {&unit7, NULL};
    clause clause6 = {&unit6, &clause7};
    //unit clause
    clause clause8 = {&unit8, NULL};
    //defining the formulas
    formula formula5 = {&clause8, NULL};
    formula formula4 = {&clause6, &formula5};
    formula formula3 = {&clause5, &formula4};
    formula formula2 = {&clause4, &formula3};
    formula formula1 = {&clause1, &formula2};
    printFound(generateMonoClauses(&formula1));
  }
  else if (argc == 7) {
    unit unit1 = {"dog", POSITIVE};
    unit unit2 = {"cat", NEGATIVE};
    unit unit3 = {"horse", POSITIVE};
    printFound(addSorted(addSorted(addSorted(NULL, &unit3), &unit2), &unit1));
  }
  else if (argc == 8) {
    literal* unit1 = (unit *) malloc(sizeof(unit));
    unit1->unitName = "EEE";
    unit1->type = POSITIVE;
    literal* unit2 = (unit *) malloc(sizeof(unit));
    unit2->unitName = "FFF";
    unit2->type = NEGATIVE;
    literal* unit3 = (unit *) malloc(sizeof(unit));
    unit3->unitName = "GGG";
    unit3->type = POSITIVE;
    clause* clause1 = (clause *) malloc(sizeof(clause));
    clause* clause2 = (clause *) malloc(sizeof(clause));
    clause* clause3 = (clause *) malloc(sizeof(clause));
    clause1->clauseName = unit1;
    clause1->next = clause2;
    clause2->clauseName = unit2;
    clause2->next = clause3;
    clause3->clauseName = unit3;
    clause3->next = NULL;
    printf("before: %s\n", clause1->clauseName->unitName);
    freeClause(clause1);
    printf("after: %s\n", clause1->clauseName->unitName);
  }
  else if (argc == 9) {
    literal* unit1 = (unit *) malloc(sizeof(unit));
    unit1->unitName = "GG NO RE";
    unit1->type = POSITIVE;
    literal* unit2 = (unit *) malloc(sizeof(unit));
    unit2->unitName = "FFF";
    unit2->type = NEGATIVE;
    literal* unit3 = (unit *) malloc(sizeof(unit));
    unit3->unitName = "GGG";
    unit3->type = POSITIVE;
    clause* clause1 = (clause *) malloc(sizeof(clause));
    clause* clause2 = (clause *) malloc(sizeof(clause));
    clause* clause3 = (clause *) malloc(sizeof(clause));
    clause1->clauseName = unit1;
    clause1->next = NULL;
    clause2->clauseName = unit2;
    clause2->next = NULL;
    clause3->clauseName = unit3;
    clause3->next = NULL;
    formula* formula1 = (formula *) malloc(sizeof(formula));
    formula* formula2 = (formula *) malloc(sizeof(formula));
    formula* formula3 = (formula *) malloc(sizeof(formula));
    formula1->fname = clause1;
    formula1->next = formula2;
    formula2->fname = clause2;
    formula2->next = formula3;
    formula3->fname = clause3;
    formula3->next = NULL;
    printf("before: %s\n", formula1->fname->clauseName->unitName);
    freeFormula(formula1);
    printf("after: %s\n", formula1->fname->clauseName->unitName);
  }
  else if (argc == 10) {
    unit unit1 = {"DOG", POSITIVE};
    unit unit2 = {"DOG", NEGATIVE};
    printf("%d", contains(&unit1, &unit2));
  }
  else if (argc == 11) {
    literal* unit1 = (unit *) malloc(sizeof(unit));
    literal* unit2 = (unit *) malloc(sizeof(unit));
    literal* unit3 = (unit *) malloc(sizeof(unit));
    literal* unit4 = (unit *) malloc(sizeof(unit));

    unit1->unitName = "a";
    unit1->type = POSITIVE;
    unit2->unitName = "b";
    unit2->type = NEGATIVE;
    unit3->unitName = "c";
    unit3->type= POSITIVE;
    unit4->unitName = "a";
    unit4->type = NEGATIVE;

    monoClause mono1 = {unit4, NULL};

    clause* clause1 = (clause *) malloc(sizeof(clause));
    clause* clause2 = (clause *) malloc(sizeof(clause));
    clause* clause3 = (clause *) malloc(sizeof(clause));

    //defining the clauses and their relationhips
    clause1->clauseName = unit1;
    clause1->next = clause2;
    clause2->clauseName = unit2;
    clause2->next = clause3;
    clause3->clauseName = unit3;
    clause3->next = NULL;

    if(propogate(&mono1, clause1) == NULL) {
      printf("correct\n");
    }
    else {
      printf("STILL CORRECT\n");
    }
  }
  else if (argc == 12) {
    //UnitPropogation
    
  }
  return 0;
}
