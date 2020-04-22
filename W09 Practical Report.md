# W09 Practical Report

## Overview

### Assumption

* An empty line represents an empty clause only if it is not the last line as example input have next line at the end of file and are considered valid.
* If a given set of clauses doesn’t contain a unit clause then there are no unit clauses which can be obtained from unit propagation. 



## Design

### Main

To keep the main file as simply as possible. A single method is called inside of it. `determineUnitClauses` then determines the number of unit clauses obtainable.

### The Collection

To be able to manipulate the data inputted by the file in an appropriate manner. Data structures which