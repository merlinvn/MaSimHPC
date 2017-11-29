//
// Created by merlinvn@gmail.com on 25/12/16.
//

#include <iostream>
#include "ParasitePopulations.h"
#include "SingleClonalParasitePopulation.h"
using namespace SmartPointer;

size_t ParasitePopulations::ID = 0;



ParasitePopulations::ParasitePopulations(): id{ID++}, mPopulations{} {
//    std::cout << "ParasitePopulations Constructor" << std::endl;
}

ParasitePopulations::~ParasitePopulations() {
//    std::cout << "ParasitePopulations Destructor" << std::endl;

}

void ParasitePopulations::init() {
    
}

void ParasitePopulations::clean() {
    mPopulations.clear();
}

//void ParasitePopulations::init2() {
//    for (int i = 0; i < 5; ++i) {
//        mPopulations.push_back(std::make_shared<SingleClonalParasitePopulation>());
//    }
//}

