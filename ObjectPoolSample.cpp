//
// Created by merlinvn@gmail.com on 27/12/16.
//

#include <iostream>
#include <cassert>
#include "Person.h"


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
            std::vector<std::shared_ptr<Person>> vPersons;
            for (int i = 0; i < numberOfPersonPerTimeStep; ++i) {
                vPersons.push_back(Person::Acquire());
                assert(vPersons.back()->getParasitePopulations().mPopulations.size() ==5);
            }
            vPersons.clear();
        }

    }
    std::cout << "" << std::endl;
    std::cout << Person::objectPool << std::endl;
    std::cout << "Object Pool time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << std::endl;


    //none pool
//    begin_time = clock();
//    {
//        for (int timeStep = 0; timeStep < total_time; ++timeStep) {
//            if (timeStep % 100 == 0) {
//                std::cout << "." << std::flush;
//            }
//            std::vector<std::shared_ptr<Person>> vPersons;
//            for (int i = 0; i < numberOfPersonPerTimeStep; ++i) {
//                auto p1 = std::make_shared<Person>();
////                p1->init2();
//                assert(p1->getParasitePopulations()->mPopulations.size() ==5);
//                vPersons.push_back(p1);
//            }
//            vPersons.clear();
//        }
//
//    }
//    std::cout << "" << std::endl;
//    std::cout << Person::objectPool << std::endl;
//    std::cout << "Non Object Pool time: " << float(clock() - begin_time) / CLOCKS_PER_SEC << std::endl;

    std::cout << "number of created Person:" << Person::ID << std::endl;
    std::cout << "number of created ParasitePopulation:" << ParasitePopulations::ID << std::endl;
    std::cout << "" << std::endl;

    return 0;
}