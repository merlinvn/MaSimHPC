//
// Created by merlinvn@gmail.com on 27/12/16.
//

#include <iostream>
#include <cassert>
#include <ctime>
#include "RawPointer/Person.h"
using namespace RawPointer;

static const int numberOfPersonPerTimeStep = 10000;

static const int total_time = 11000;

int main() {
	std::cout << "Hello" << std::endl;

	clock_t begin_time = clock();
	{
		for (int timeStep = 0; timeStep < total_time; ++timeStep) {
			if (timeStep % 100 == 0) {
				std::cout << "." << std::flush;
			}
			std::vector<Person*> vPersons;
			for (int i = 0; i < numberOfPersonPerTimeStep; ++i) {
				auto p = Person::Acquire();
				for (int j = 0; j < 5; ++j) {
					auto pp = SingleClonalParasitePopulation::Acquire();
					p->parasitePopulations->mPopulations.push_back(pp);
				}

				vPersons.push_back(p);
				assert(vPersons.back()->parasitePopulations->mPopulations.size() == 5);
			}

			//std::cout << SingleClonalParasitePopulation::objectPool.mFreeList.size() << std::endl;
			assert(Person::objectPool.mFreeList.size() == 100000 - numberOfPersonPerTimeStep);
			assert(SingleClonalParasitePopulation::objectPool.mFreeList.size() == 100000 - numberOfPersonPerTimeStep * 5);

			for (int i = 0; i < numberOfPersonPerTimeStep; ++i) {
				Person::Free(vPersons[i]);
			}
			vPersons.clear();
			assert(SingleClonalParasitePopulation::objectPool.mFreeList.size() == 100000);
			assert(Person::objectPool.mFreeList.size() == 100000);

		}

	}
	std::cout << "" << std::endl;
	std::cout << Person::objectPool << std::endl;
	std::cout << "Object Pool time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << std::endl;

	std::cout << "number of created Person:" << Person::ID << std::endl;
	std::cout << "number of created SingleClonalParasitePopulation:" << SingleClonalParasitePopulation::ID << std::endl;
	std::cout << "" << std::endl;

	return 0;
}