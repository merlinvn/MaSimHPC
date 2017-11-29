//
// Created by merlinvn@gmail.com on 25/12/16.
//

#ifndef MODERNCPP_PARASITEPOPULATIONS_H
#define MODERNCPP_PARASITEPOPULATIONS_H

#include <vector>
#include <memory>
#include "../Core/ObjectPoolSmartPointer.h"
#include "../Core/IPoolableObject.h"
#include "SingleClonalParasitePopulation.h"

namespace SmartPointer {

	class ParasitePopulations : IPoolableObject {
		size_t id;

	public:
		static size_t ID;

		ParasitePopulations();

		ParasitePopulations(const ParasitePopulations &) = delete;

		ParasitePopulations &operator=(const ParasitePopulations &) = delete;

		virtual ~ParasitePopulations();

	public:
		void init() override;

		void clean() override;

	public:
		std::vector<ObjectPoolSmartPointer<SingleClonalParasitePopulation>::Object > mPopulations;

	};
}

#endif //MODERNCPP_PARASITEPOPULATIONS_H
