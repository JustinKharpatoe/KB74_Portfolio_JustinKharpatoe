#ifndef EVIDENCECOMPARATORS_H
#define EVIDENCECOMPARATORS_H

#include "nodes/evidence.h"


class ComparatorByOperator {
  public:
    bool operator() (evidence *a, evidence *b) {
      return a->getop() < b->getop();
    }
};

#endif // EVIDENCECOMPARATORS_H
