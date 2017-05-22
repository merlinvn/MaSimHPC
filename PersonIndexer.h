//
// Created by merlinvn@gmail.com on 29/12/16.
//

#ifndef MODERNCPP_SINGLEARRAYPERSONINDEX_H
#define MODERNCPP_SINGLEARRAYPERSONINDEX_H

#include "IObjectIndexer.h"
#include "Person.h"
#include <iostream>

template<Person::Property ... Properties>
class PersonIndexer : IObjectIndexer<std::shared_ptr<Person>, Person::Property> {
    size_t id;
public:
    static size_t ID;

    size_t getId() const {
        return id;
    }

public:
    std::vector<Person::Property> mTrackingProperties;
    using PersonNestedVector =  multidimensional_vector<std::shared_ptr<Person>, sizeof...(Properties) + 1>;
    typename PersonNestedVector::type mPersons;


    PersonIndexer() : mTrackingProperties{Properties...} {
        id = PersonIndexer<>::ID++;
    }

    virtual ~PersonIndexer() {
        PersonIndexer<>::ID--;
    }

    //remove copy and assign operator
    PersonIndexer(const PersonIndexer &) = delete;

    PersonIndexer &operator=(const PersonIndexer &)= delete;

    void init(const std::initializer_list<int> &propertyInfo) {
        if (propertyInfo.size() != mTrackingProperties.size()) {
            throw std::invalid_argument("wrong number of property info");
        }
        mPersons = PersonNestedVector::create(propertyInfo.begin());
    }

public:

    void add(std::shared_ptr<Person> &person) override {
        PersonNestedVector::add(id, mPersons, mTrackingProperties, 0, person);
    }

    void remove(std::shared_ptr<Person> &person) override {
        PersonNestedVector::remove(id, mPersons, mTrackingProperties, 0, person);
    }

    void size() override {}

    void update() override {}

    void notify_change(std::shared_ptr<Person> &person, const Person::Property &property, int oldValue,
                       int newValue) override {}

};


template<Person::Property ... Properties>
size_t PersonIndexer<Properties...>::ID = 0;

#endif //MODERNCPP_SINGLEARRAYPERSONINDEX_H
