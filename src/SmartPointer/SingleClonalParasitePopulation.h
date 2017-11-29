//
// Created by merlinvn@gmail.com on 27/12/16.
//

#ifndef MODERNCPP_SINGLECLONALPARASITEPOPULATION_H
#define MODERNCPP_SINGLECLONALPARASITEPOPULATION_H

#include "../Core/ObjectPoolSmartPointer.h"
#include "../Core/IPoolableObject.h"

namespace SmartPointer {

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

		static ObjectPoolSmartPointer<SingleClonalParasitePopulation> objectPool;

		static ObjectPoolSmartPointer<SingleClonalParasitePopulation>::Object Acquire();
	};
}

#endif //MODERNCPP_SINGLECLONALPARASITEPOPULATION_H
