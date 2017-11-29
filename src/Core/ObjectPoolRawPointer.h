//
// Created by merlinvn@gmail.com on 27/12/16.
//

#ifndef MODERNCPP_ObjectPoolRawPointer_H
#define MODERNCPP_ObjectPoolRawPointer_H

#include <utility>
#include <cstddef>
#include <memory>
#include <queue>
#include <iostream>
#include <ostream>
#include <assert.h>


//namespace std {
//   template<typename T, typename... Args>
//   std::unique_ptr<T> make_unique(Args &&... args) {
//       return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
//   }
//}


template<typename T>
class ObjectPoolRawPointer {

public:
	ObjectPoolRawPointer(size_t chunkSize = kDefaultChunkSize);

	//prevent assignment and pass by value
	ObjectPoolRawPointer(const ObjectPoolRawPointer<T> &src) = delete;

	ObjectPoolRawPointer<T> &operator=(const ObjectPoolRawPointer<T> &rhs) = delete;

	virtual ~ObjectPoolRawPointer();

	//the type of smart pointer returned by acquireObject
	using Object = T*;

	Object acquireObject();

	void returnObject(Object);

	friend std::ostream &operator<<(std::ostream &os, const ObjectPoolRawPointer<T> &op) {
		os << "Pool size: " << op.mFreeList.size();
		return os;
	}

	std::queue<Object> mFreeList;
private:
	size_t mChunkSize;

	static const size_t kDefaultChunkSize = 10;

	void allocateChunk();
};

template<typename T>
ObjectPoolRawPointer<T>::~ObjectPoolRawPointer() {
	while (!mFreeList.empty()) {
		delete mFreeList.front();
		mFreeList.pop();
	}
}

template<typename T>
ObjectPoolRawPointer<T>::ObjectPoolRawPointer(size_t chunkSize) {
	if (chunkSize == 0) {
		throw std::invalid_argument("chunk size must be positive");
	}

	mChunkSize = chunkSize;
	allocateChunk();
}

template<typename T>
void ObjectPoolRawPointer<T>::allocateChunk() {
	for (size_t i = 0; i < mChunkSize; ++i) {
		mFreeList.push(new T());
	}
}

template<typename T>
typename ObjectPoolRawPointer<T>::Object ObjectPoolRawPointer<T>::acquireObject() {
	if (mFreeList.empty()) {
		allocateChunk();
	}

	T* obj = mFreeList.front();
	mFreeList.pop();
	
	obj->init();
	return obj;
}

template<typename T>
void ObjectPoolRawPointer<T>::returnObject(Object o) {
	if (o == nullptr) {
		std::cout << typeid (T).name() << " Free failed!!!" << std::endl;
		assert(false);
	}
	o->clean();
	mFreeList.push(o);
}

#endif //MODERNCPP_ObjectPoolRawPointer_H
