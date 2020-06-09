#ifndef COMPARATEURTRANSACTION_H
#define COMPARATEURTRANSACTION_H

#include "Transaction.h"

inline bool transactionsComparaisonPlusPetit(const Transaction* t1, const Transaction* t2) {
    return t1->getDate() < t2->getDate();
}

#endif // COMPARATEURTRANSACTION_H
