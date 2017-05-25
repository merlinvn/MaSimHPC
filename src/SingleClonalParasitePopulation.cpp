//
// Created by merlinvn@gmail.com on 27/12/16.
//

#include <iostream>
#include "SingleClonalParasitePopulation.h"

ObjectPool<SingleClonalParasitePopulation> SingleClonalParasitePopulation::objectPool(1000);

SingleClonalParasitePopulation::SingleClonalParasitePopulation() {
//    std::cout << "SCPP created" << std::endl;
}

SingleClonalParasitePopulation::~SingleClonalParasitePopulation() {
//    std::cout << "SCPP destroyed" << std::endl;
}

ObjectPool<SingleClonalParasitePopulation>::Object SingleClonalParasitePopulation::Acquire() {
    return objectPool.acquireObject();
}

void SingleClonalParasitePopulation::init() {

}

void SingleClonalParasitePopulation::clean() {

}
