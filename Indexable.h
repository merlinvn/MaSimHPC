//
// Created by merlinvn@gmail.com on 05/01/17.
//

#ifndef MODERNCPP_IINDEXABLE_H
#define MODERNCPP_IINDEXABLE_H


#include <cstddef>
#include <array>
#include <iostream>

#define MAXIMUM_ALLOWED_NUMBER_OF_INDEXERS 10

class Indexable {
protected:
    std::array<size_t, MAXIMUM_ALLOWED_NUMBER_OF_INDEXERS> mPositionInDeepestNestedVector;
public:
    Indexable() : mPositionInDeepestNestedVector{} {}

    void setPositionInDeepestNestedVector(const size_t &pos, const size_t &id) {
        mPositionInDeepestNestedVector[id] = pos;
    };

    size_t getPositionInDeepestNestedVector(const size_t &id) const {
        return mPositionInDeepestNestedVector[id];
    };
};

#endif //MODERNCPP_IINDEXABLE_H
