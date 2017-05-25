//
// Created by merlinvn@gmail.com on 27/12/16.
//

#ifndef MODERNCPP_SINGLECLONALPARASITEPOPULATION_H
#define MODERNCPP_SINGLECLONALPARASITEPOPULATION_H


#include "Core/ObjectPool.h"

class SingleClonalParasitePopulation : IPoolable {

public:
    virtual ~SingleClonalParasitePopulation();

public:
    SingleClonalParasitePopulation();

    SingleClonalParasitePopulation(const SingleClonalParasitePopulation &) = delete;

    SingleClonalParasitePopulation &operator=(const SingleClonalParasitePopulation &)= delete;

public:

    void init() override;

    void clean() override;

    static ObjectPool<SingleClonalParasitePopulation> objectPool;

    static ObjectPool<SingleClonalParasitePopulation>::Object Acquire();
};


#endif //MODERNCPP_SINGLECLONALPARASITEPOPULATION_H
