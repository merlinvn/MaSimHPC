//
// Created by merlinvn@gmail.com on 27/12/16.
//

#include <iostream>
#include "SingleClonalParasitePopulation.h"

using namespace RawPointer;

ObjectPoolRawPointer<SingleClonalParasitePopulation> SingleClonalParasitePopulation::objectPool(100000);
size_t SingleClonalParasitePopulation::ID = 0;

SingleClonalParasitePopulation::SingleClonalParasitePopulation(): id(ID++) {
//    std::cout << "SCPP created" << std::endl;
}

SingleClonalParasitePopulation::~SingleClonalParasitePopulation() {
//    std::cout << "SCPP destroyed" << std::endl;
}

ObjectPoolRawPointer<SingleClonalParasitePopulation>::Object SingleClonalParasitePopulation::Acquire() {
    return objectPool.acquireObject();
}

void RawPointer::SingleClonalParasitePopulation::Free(ObjectPoolRawPointer<SingleClonalParasitePopulation>::Object o)
{
	return objectPool.returnObject(o);
}

void SingleClonalParasitePopulation::init() {

}

void SingleClonalParasitePopulation::clean() {

}
