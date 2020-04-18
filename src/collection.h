//collection.h
#ifndef COLLECTION_H
#define COLLECTION_H
#define NEGATIVE 0
#define POSITIVE 1
#define contradiction int
#define TRUE 1
#define FALSE 0

typedef struct _unit {
  char* uname;
  int type;
} unit;

typedef struct _clause {
  unit* cname;
  _clause next = NULL;
} clause;

typedef struct _formula {
  clause* fname;
  _formula next = NULL;
} formula;

typedef struct _monoClause {
  unit* mname;
  monoClause* next = NULL;
} monoClause;
#endif
