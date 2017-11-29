//
// Created by merlinvn@gmail.com on 24/12/16.
//

#include <iostream>
#include "Person.h"
#include <memory>
using namespace RawPointer;
size_t Person::ID = 0;
ObjectPoolRawPointer<Person> Person::objectPool(100000);

std::vector<size_t(*)(Person *)> Person::propertiesMap{
        [](Person *p) -> size_t { return p->getId(); },
        [](Person *p) -> size_t { return p->getAge(); },
        [](Person *p) -> size_t { return p->getAgeClass(); },
        [](Person *p) -> size_t { return p->getLocation(); },
        [](Person *p) -> size_t { return p->getHostState(); }
};

size_t Person::getId() const {
    return id;
}


Person::Person() : id{Person::ID++}, parasitePopulations{std::make_unique<ParasitePopulations>()} {
//    std::cout << "Person with id(" << id << ") created" << std::endl;
}

size_t Person::getAge() const {
    return age;
}

void Person::setAge(size_t age) {
    Person::age = age;
}

Person::~Person() {
//    std::cout << "Person with id(" << id << ") destructor" << std::endl;
}

void Person::init() {	
	parasitePopulations->init();
    setLocation(0);
    setAge(0);
    setAgeClass(0);
    setHostState(Person::HostState::Susceptible);
}

void Person::clean() {
    parasitePopulations->clean();
}


ObjectPoolRawPointer<Person>::Object Person::Acquire() {
	return objectPool.acquireObject();
}

void Person::Free(ObjectPoolRawPointer<Person>::Object o) {
	return objectPool.returnObject(o);
}

//void Person::Release(ObjectPool<Person>::Object &object) {
//    object.reset();
//}

size_t Person::getAgeClass() const {
    return ageClass;
}

void Person::setAgeClass(size_t ageClass) {
    Person::ageClass = ageClass;
}

size_t Person::getLocation() const {
    return location;
}

void Person::setLocation(size_t location) {
    Person::location = location;
}

Person::HostState Person::getHostState() const {
    return hostState;
}

void Person::setHostState(Person::HostState hostState) {
    Person::hostState = hostState;
}

size_t Person::getPropertyValue(Person::Property property) {
    return Person::propertiesMap[property](this);
}




