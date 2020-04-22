# W09 Practical Report

## Overview

The specification requires that exhaustive unit propagation is to be implemented in c. This means we perform unit propagation with the present unit clauses in the formula provided. Then if get more unit clauses from unit propagation we then use them to perform unit propagation again. This cycle is repeated unit no more unit clauses remain or a contradiction is found.

### Input Format

* Each line represents once clause
* Each literal in the clause is separated by a space
* Literal variable names consist of one or more characters
* if the literal is negative it shall begin with a “-”.
* Empty line represents a empty clause.

### Required Functionality

* A listing of all unit clauses obtainable by exhaustive unit propagation.
  * Appear in lexigraphical order
  * separated by space.
  * Each variable should be listed at most once.

### Assumption

* An empty line represents an empty clause only if it is not the last line as example input have next line at the end of file and are considered valid.
* If a given set of clauses doesn’t contain a unit clause then there are no unit clauses which can be obtained from unit propagation.  So nothing is printed and the program exits.
* Empty file is a contradiction as there is only the empty clause.

## Design

### Main

To keep the main file as simply as possible. A single method is called inside of it. `determineUnitClauses` then determines the number of unit clauses obtainable.

### The Collection

To be able to manipulate the data inputted by the file in an appropriate manner. Data structures which manipulate and store elements of the program were designed.

#### Literal (`literal`)

```c
typedef struct _literal {
  char* unitName;
  int type;
} literal;
```

The purpose of this data structure was to store every literal variable and its type. `unitname` is the variable name that has been assigned to the literal. `type` just indicates whether it was a negative literal or a positive literal e.g. did it start with a “-” when reading in the input.

 #### Clause (`clause`)

```c
typedef struct _clause {
  literal* clauseName;
  struct _clause* next;
} clause;
```

The purpose of this data structure was to store every literal contained in a clause. A linked List implementation was used as the number of clauses present is on known and varies between clauses. Each literal present in a clause can be found by traversing this structure.

#### Unit Clauses (`monoclause`)

```c
typedef struct _monoClause {
  //the name of the unit clauses.
  literal* unitClause;
  struct _monoClause* next;
} monoClause;
```

This structure has identical implementation as clause. The reason they are separate structures is so that the difference between a clause and a list of found unit clauses is easily identified. This makes the program much easier to read as it can now be easily identified what a structure contains.

#### formula (`formula`)

```c
typedef struct _formula {
  clause* formulaName;
  struct _formula* next;
} formula;
```

The purpose of this structure was to store all the clause present in a formula. The reason they are implemented as a linked list hold the same for above structure as their length is undetermined.

### Printer

The purpose of this file is to handle all printing operations. .eg. Printing Empty, Print Contradiction, Printing found unit clauses.

#### Collection Handler

The purpose of this collection was to handle the manipulation of the data structures created. From generating them to freeing them.

#### `generateClause`

The purpose of this method was to generate a linked list of unit literals present in a clause. This method makes use of the `strtok` library to tokenise the strings.

#### `createClauses`

reads the whole input and generates the formula which describes the input.

#### `generateMonoClauses`

finds all the units clauses in a formula.

#### `addSorted`

Adds all the unit clauses in a sorted order.

### Exhaustive Propagation

This purpose of this file was to handle all methods related and involving exhaustive unit propagation.

#### `propagate`

performs a single instance of unit propagation upon a provided clause. Returns NULL in event of a contradiction. e.g. a clause evaluating to false. Adds new unit clauses to list of unit clauses. The reason unit clauses are added here is because we know there is only one scenario in which unit clauses are made and it  is when the converse of a unit clauses if found and the needs to be removed then another unit clauses may be created in the process.

#### `unitPropagation`

Performs unit propagation on every clauses for a single unit clause.

#### `propagate`

Performs `unitPropagation` method for every unit clauses that has been obtained.

#### `determineUnitClauses`

Executes core logic of the program.

