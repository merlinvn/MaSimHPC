//
// Created by merlinvn@gmail.com on 27/12/16.
//

#ifndef MODERNCPP_SINGLECLONALPARASITEPOPULATION_H
#define MODERNCPP_SINGLECLONALPARASITEPOPULATION_H


#include "../Core/ObjectPoolRawPointer.h"
#include "../Core/IPoolableObject.h"

namespace RawPointer {
	class SingleClonalParasitePopulation : IPoolableObject {
		size_t id;
	public:
		static size_t ID;

	public:
		virtual ~SingleClonalParasitePopulation();

	public:
		SingleClonalParasitePopulation();

		SingleClonalParasitePopulation(const SingleClonalParasitePopulation &) = delete;

		SingleClonalParasitePopulation &operator=(const SingleClonalParasitePopulation &) = delete;

	public:

		void init() override;

		void clean() override;

		static ObjectPoolRawPointer<SingleClonalParasitePopulation> objectPool;

		static ObjectPoolRawPointer<SingleClonalParasitePopulation>::Object Acquire();
		static void Free(ObjectPoolRawPointer<SingleClonalParasitePopulation>::Object);
	};
}

#endif //MODERNCPP_SINGLECLONALPARASITEPOPULATION_H
