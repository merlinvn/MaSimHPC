//
// Created by merlinvn@gmail.com on 25/12/16.
//

#include <iostream>
#include "ParasitePopulations.h"
#include "SingleClonalParasitePopulation.h"
using namespace RawPointer;

size_t ParasitePopulations::ID = 0;



ParasitePopulations::ParasitePopulations(): id{ID++}, mPopulations{} {
//    std::cout << "ParasitePopulations Constructor" << std::endl;
}

ParasitePopulations::~ParasitePopulations() {
//    std::cout << "ParasitePopulations Destructor" << std::endl;
	clean();
}

void ParasitePopulations::init() {
 
}

void ParasitePopulations::clean() {
	for (int i = 0; i < mPopulations.size(); i++) {
		SingleClonalParasitePopulation::Free(mPopulations[i]);
	}

    mPopulations.clear();
}


