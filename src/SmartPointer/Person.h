//
// Created by merlinvn@gmail.com on 24/12/16.
//

#ifndef MODERNCPP_PERSON_H
#define MODERNCPP_PERSON_H

#include <memory>
#include <map>

#include "ParasitePopulations.h"
#include "../Core/ObjectPoolSmartPointer.h"
#include "../Core/Indexable.h"
#include "../Core/IPoolableObject.h"

#define MAXIMUM_ALLOWED_NUMBER_OF_INDEXERS 10


namespace SmartPointer {
	class Person : IPoolableObject, public Indexable {

	public:
		enum Property {
			Id,
			Age,
			AgeClass,
			Location,
			State
		};

		enum HostState {
			Susceptible,
			Exposed,
			Asymptomatic,
			Clinical,
			Dead,
			NumberOfStates
		};

	private:
		size_t id;
		size_t age;
		size_t ageClass;
		size_t location;
		Person::HostState hostState;
		

	public:
		static size_t ID;
		std::unique_ptr<ParasitePopulations> parasitePopulations;

	public:
		void init() override;

		void clean() override;

		size_t getAge() const;

		void setAge(size_t age);

		size_t getAgeClass() const;

		void setAgeClass(size_t ageClass);

		size_t getLocation() const;

		void setLocation(size_t location);

		HostState getHostState() const;

		void setHostState(Person::HostState hostState);

		size_t getId() const;

		size_t getPropertyValue(Person::Property property);

	public:
		Person();

		Person(const Person &) = delete;

		Person &operator=(const Person &) = delete;

		virtual ~Person();


	public:
		static ObjectPoolSmartPointer<Person> objectPool;

		static ObjectPoolSmartPointer<Person>::Object Acquire();

		static std::vector<size_t(*)(Person *)> propertiesMap;
	};
}

#endif //MODERNCPP_PERSON_H
