//
// Created by merlinvn@gmail.com on 25/12/16.
//

#ifndef MODERNCPP_PARASITEPOPULATIONS_H
#define MODERNCPP_PARASITEPOPULATIONS_H

#include <vector>
#include <memory>
#include "Core/ObjectPool.h"
#include "SingleClonalParasitePopulation.h"


class ParasitePopulations : IPoolable {
    size_t id;

public:
    static size_t ID;

    ParasitePopulations();

    ParasitePopulations(const ParasitePopulations &) = delete;

    ParasitePopulations &operator=(const ParasitePopulations &)= delete;

    virtual ~ParasitePopulations();

public:
    void init() override;
//    void init2();

    void clean() override;

public:
    std::vector<ObjectPool<SingleClonalParasitePopulation>::Object > mPopulations;

};


#endif //MODERNCPP_PARASITEPOPULATIONS_H
