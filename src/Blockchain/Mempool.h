//
// Created by lukol on 04.12.2023.
//

#include <vector>
#include "Transaction.h"

#ifndef BLOCKCHAIN_MEMPOOL_H
#define BLOCKCHAIN_MEMPOOL_H


class Mempool {
private:
    std::vector<Transaction> currentPool;
public:
    Mempool();
    void setPool(std::vector<Transaction>);
    std::vector<Transaction> getPool;
    void addTransaction(Transaction&);
    void removeTransaction(Transaction&);
};


#endif //BLOCKCHAIN_MEMPOOL_H
