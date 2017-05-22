//
// Created by merlinvn@gmail.com on 24/12/16.
//

#include <iostream>
#include <assert.h>
#include "Person.h"

int main(){

    Person p{};
    std::cout << "Hello P with id " << p.getId() << std::endl;


    Person p2;
    std::cout << "Hello P2 with id " << p2.getId() << std::endl;
    assert(&p.getParasitePopulations() == &p. getParasitePopulations());



    std::cout << "size_t size: " << sizeof(size_t) << std::endl;
    std::cout << "Person size: " << sizeof(p) << std::endl;

    std::shared_ptr<Person> spPerson{std::make_shared<Person>()};

    std::cout << "Shared pointer size: " << sizeof(spPerson) << std::endl;

    std::unique_ptr<Person> unPerson{std::make_unique<Person>()};
    std::cout << "Unique pointer size: " << sizeof(spPerson) << std::endl;
    return 0;
}