#include "collection.h"
#include "handler.h"
#include "printer.h"

/*
* performs a single instance of unit propagation.
*/
clause* propagate(monoClause* mono, clause* expression) {
  //Gets the head of the clauses to loop of every unit it contains.
  clause* current = expression;
  //stores the next of a clause in the event that an individual negative unit is found and needs to be removed.
  clause* newClause = NULL;
  //stores the head of a clause in the event that an individual negative unit is found and needs to be removed.
  clause* newCurrent = NULL;
  //Loops unit no clauses units are remaining.
  while(current != NULL) {
    //stores the result of checking if there are the same literal and what type they are.
    int state;
    //quick fix
    //some lines have been cleared as propagation on them is done.
    if ( mono->unitClause != NULL && current->clauseName != NULL) {
      state = contains(mono->unitClause, current->clauseName);
    }
    else {
      // these lines are now ignored.
      state = - 1;
    }
    //In the event that they are identical.
    //ALl items are cleared as they do not provide to the truth value.
    if (state == POSITIVE) {
      //loops over to ensure it doesn't remove it self from the clause.
      while(expression != NULL) {
        clause* temp = expression->next;
        //checks that the it doesn't free itself.
        if (expression->clauseName != mono->unitClause) {
          //free all other clauses
          free(expression->clauseName);
          free(expression);
        }
        else {
          //free the clauses that stores it.
          free(expression);
        }
        //goes to the next one
        expression = temp;
      }
      //creates an empty clause to return.
      clause* empty = (clause *) malloc(sizeof(clause));
      empty -> clauseName = NULL;
      empty -> next = NULL;
      return empty;
    }
    //in the event that a negative literal is found and has to be removed
    else if (state == NEGATIVE) {
      //gets the next of the current clause
      //possible could be NULL.
      newClause = current->next;
      //frees both current and the next
      free(current->clauseName);
      free(current);
      //Check if the head is NULL
      if (newCurrent == NULL) {
        //sets the next of the removed clause to be the head of the linked list.
        newCurrent = newClause;
      }
      else {
        //adds it to the end of the linked list.
        newCurrent->next = newClause;
      }

      //checks the linked list is not empty
      if (newCurrent != NULL) {
        //checks there is only 1 item in the linked list.
        if (newCurrent->next == NULL) {
          //loops until we get to the end of mono linked list.
          while(1) {
            //finds the last item because the end is not null
            if (mono->next == NULL) {
              //adds the character to the end.
              mono ->next = (monoClause*) malloc(sizeof(monoClause));
              mono->next->unitClause = newCurrent->clauseName;
              mono->next->next = NULL;
              break;
            }
            //goe to the next node.
            mono = mono->next;
          }
        }
      }
      //returns the head of the next clause.
      return newCurrent;
    }
    //checks if a node has been found before current
    if (newCurrent == NULL){
      newCurrent = current;
    }
    else {
      //changes the previous node found to the current.
      newCurrent = current;
    }
    //updates the current node.
    current = current->next;
  }
  return expression;
}

formula* unitPropagation(monoClause* mono, formula* clauses) {
  //For storing the current formula
  formula* currentFormula = clauses;
  //Stores the head of the new formula that will be returned.
  formula* base = (formula *) malloc(sizeof(formula));
  //stores the current clause that propagation has been ran on.
  formula* nextClauses = base;
  //Determins if contradiction has been found.
  int invalid = NEGATIVE;
  //intialising it so it is empty.
  nextClauses-> formulaName = NULL;
  //Loops over every clause that propogation is ran on.
  while(currentFormula != NULL) {
    //gets the clause from formula
    clause* currentClause = currentFormula->formulaName;
    //this gets the updated clause from propogate after unit propagation is ran on it.
    clause* newClause = propagate(mono, currentClause);
    //if unit propagation returns null then there was a contradiction.
    if (newClause != NULL) {
      //checks if the head has anything it and if not adds it to the head of linked list.
      if (base->formulaName == NULL) {
        //adds it to the head of the linked list.
        base->formulaName = newClause;
      }
      else {
        //This then creates space for the next item in the linked list.
        nextClauses->next = (formula *) malloc(sizeof(formula));
        //This then adds the new clause to the next item in the linked list.
        nextClauses->next->formulaName = newClause;
        nextClauses->next->next = NULL;
        //moves to the next node in the lisked list.
        nextClauses = nextClauses->next;
      }
    }
    else {
      //invalid since contradiction was found.
      invalid = POSITIVE;
      break;
    }
    //goes to next node in linked list.
    currentFormula = currentFormula->next;
  }
  //prints it was invalid
  if (invalid == POSITIVE) {
    freeFormula(base);
    return NULL;
  }
  //returns the base.
  return base;
}

monoClause* propagateOver(monoClause* unitClauses, formula* clauses) {
  //stores the first unit clauses to be remove with propagation
  monoClause* current = unitClauses;
  //stores the order linked list of mono clauses
  monoClause* orderMono = NULL;
  //stores the reminaing clauses for which unit propogation must be ran on.
  formula* remainingClauses = clauses;
  //runs untill no unit clauses are left.
  while(current != NULL){
    //gets the remaining clauses which unit progation must be ran on.
    remainingClauses = unitPropagation(current, remainingClauses);
    //remaining clauses returns null if a contradiction if found.
    if (remainingClauses == NULL) {
      return NULL;
    }
    //adds the ordered mono together in a sorted order.
    orderMono = addSorted(orderMono, current->unitClause);
    //Gets the current monoclause to be freeded later
    monoClause* temp = current;
    //goes to the next mono clause
    current = current->next;
    //free the mono clause
    free(temp);
  }
  //return the ordered linked list
  return orderMono;
}

/*
* Determins the total number of unit clauses obtainable through unit propagation.
*/
void determineUnitClauses() {

  //prints contradiction in the event an empty line was found.
  formula* clauses = createClauses();
  if (clauses == NULL) {
    printContradiction();
  }

  //prints empty if no unit clauses were found.
  monoClause* unitClauses = generateMonoClauses(clauses);
  if (unitClauses == NULL) {
    printEmpty();
  }

  //prints the found clauses or prints contradiction if one was found.
  monoClause* foundClauses = propagateOver(unitClauses, clauses);
  if (foundClauses == NULL) {
    printContradiction();
  }
  else {
    printFound(foundClauses);
  }
}