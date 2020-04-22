# W09 Practical Report

## Overview

The specification requires that exhaustive unit propagation is to be implemented in c. This means we perform unit propagation with the present unit clauses in the formula provided. Then if get more unit clauses from unit propagation we then use them to perform unit propagation again. This cycle is repeated unit no more unit clauses remain or a contradiction is found.

### Assumption

* An empty line represents an empty clause only if it is not the last line as example input have next line at the end of file and are considered valid.
* If a given set of clauses doesn’t contain a unit clause then there are no unit clauses which can be obtained from unit propagation.  So nothing is printed and the program exits.



## Design

### Main

To keep the main file as simply as possible. A single method is called inside of it. `determineUnitClauses` then determines the number of unit clauses obtainable.

### The Collection

To be able to manipulate the data inputted by the file in an appropriate manner. Data structures which