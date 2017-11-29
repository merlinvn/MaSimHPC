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
				auto p = new Person();
				for (int j = 0; j < 5; ++j) {
					auto pp = new SingleClonalParasitePopulation();
					p->parasitePopulations->mPopulations.push_back(pp);
				}

				vPersons.push_back(p);
			}
		
			for (int i = 0; i < numberOfPersonPerTimeStep; ++i) {
				for (int j = 0; j < 5; ++j) {					
					delete vPersons[i]->parasitePopulations->mPopulations[j];
				}
				vPersons[i]->parasitePopulations->mPopulations.clear();
				delete vPersons[i];
			}
			vPersons.clear();

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