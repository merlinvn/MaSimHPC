//
// Created by merlinvn@gmail.com on 27/12/16.
//

#include <iostream>
#include "SingleClonalParasitePopulation.h"
using namespace SmartPointer;
ObjectPoolSmartPointer<SingleClonalParasitePopulation> SingleClonalParasitePopulation::objectPool(100000);

size_t SingleClonalParasitePopulation::ID = 0;

SingleClonalParasitePopulation::SingleClonalParasitePopulation() : id{ ID++ } {
//    std::cout << "SCPP created" << std::endl;
}

SingleClonalParasitePopulation::~SingleClonalParasitePopulation() {
//    std::cout << "SCPP destroyed" << std::endl;
}

ObjectPoolSmartPointer<SingleClonalParasitePopulation>::Object SingleClonalParasitePopulation::Acquire() {
    return objectPool.acquireObject();
}

void SingleClonalParasitePopulation::init() {

}

void SingleClonalParasitePopulation::clean() {

}
