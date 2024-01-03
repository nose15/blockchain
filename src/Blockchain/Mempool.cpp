//
// Created by lukol on 04.12.2023.
//

#include "Mempool.h"


Mempool::Mempool() = default;

void Mempool::addTransaction(Transaction &transaction)
{
    this->currentPool.push_back(transaction);
}

void Mempool::setPool(std::vector<Transaction> newPool)
{
    this->currentPool = newPool;
}