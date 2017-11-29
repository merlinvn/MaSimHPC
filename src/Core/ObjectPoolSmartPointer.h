//
// Created by merlinvn@gmail.com on 27/12/16.
//

#ifndef MODERNCPP_ObjectPoolSmartPointer_H
#define MODERNCPP_ObjectPoolSmartPointer_H

#include <utility>
#include <cstddef>
#include <memory>
#include <queue>
#include <ostream>


//namespace std {
//   template<typename T, typename... Args>
//   std::unique_ptr<T> make_unique(Args &&... args) {
//       return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
//   }
//}


template<typename T>
class ObjectPoolSmartPointer {

public:
    ObjectPoolSmartPointer(size_t chunkSize = kDefaultChunkSize);

    //prevent assignment and pass by value
    ObjectPoolSmartPointer(const ObjectPoolSmartPointer<T> &src) = delete;

    ObjectPoolSmartPointer<T> &operator=(const ObjectPoolSmartPointer<T> &rhs) = delete;

    virtual ~ObjectPoolSmartPointer();

    //the type of smart pointer returned by acquireObject
    using Object = std::shared_ptr<T>;

    Object acquireObject();

    friend std::ostream &operator<<(std::ostream &os, const ObjectPoolSmartPointer<T> &op) {
        os << "Pool size: " << op.mFreeList.size();
        return os;
    }

    std::queue<std::unique_ptr<T>> mFreeList;
private:
    size_t mChunkSize;

    static const size_t kDefaultChunkSize = 10;

    void allocateChunk();
};

template<typename T>
ObjectPoolSmartPointer<T>::~ObjectPoolSmartPointer() {
	while (!mFreeList.empty()) {
		mFreeList.pop();
	}
}

template<typename T>
ObjectPoolSmartPointer<T>::ObjectPoolSmartPointer(size_t chunkSize) {
    if (chunkSize == 0) {
        throw std::invalid_argument("chunk size must be positive");
    }

    mChunkSize = chunkSize;
    allocateChunk();
}

template<typename T>
void ObjectPoolSmartPointer<T>::allocateChunk() {
    for (size_t i = 0; i < mChunkSize; ++i) {
        mFreeList.emplace(std::make_unique<T>());
    }
}

template<typename T>
typename ObjectPoolSmartPointer<T>::Object ObjectPoolSmartPointer<T>::acquireObject() {
    if (mFreeList.empty()) {
        allocateChunk();
    }

    //get free object from the queue to a local unique_ptr
    std::unique_ptr<T> obj(std::move(mFreeList.front()));
    mFreeList.pop();

    //convert the object pointer to an Object (shared pointer with custom deleter)
    Object smartObject(obj.release(), [this](T *t) {
        // The custom deleter doesn't actually deallocate the memory,
        // but simply puts the object back on the free list.
        t->clean();
        mFreeList.push(std::unique_ptr<T>(t));
    });

    smartObject->init();
    return smartObject;
}


#endif //MODERNCPP_ObjectPoolSmartPointer_H
