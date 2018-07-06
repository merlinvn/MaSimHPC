//
// Created by merlinvn@gmail.com on 31/12/16.
//

#include "catch/catch.hpp"
#include "SmartPointer/Person.h"
#include "PersonIndexer.h"

TEST_CASE("Create person index from template", "[PersonIndex]")
{

    SECTION("Single index will have 2-dimensional vector")
    {
        PersonIndexer<Person::AgeClass> pi;
        //
        REQUIRE(typeid(pi.mPersons).name() == typeid(std::vector<std::vector<std::shared_ptr<Person>>>).name());
    }
    SECTION("Double index will have 3-dimensional vector")
    {
        PersonIndexer<Person::AgeClass, Person::State> pi;
        REQUIRE(typeid(pi.mPersons).name() ==
                typeid(std::vector<std::vector<std::vector<std::shared_ptr<Person>>>>).name());
    }
}

TEST_CASE("Create person index from template will initialize with number of tracking properties", "[PersonIndex]")
{
    SECTION("Single index will track 1 property")
    {
        PersonIndexer<Person::AgeClass> pi;
        //
        REQUIRE(pi.mTrackingProperties.size() == 1);
        REQUIRE(pi.mTrackingProperties[0] == Person::AgeClass);
    }

    SECTION("Double index will track 2 properties")
    {
        PersonIndexer<Person::Location, Person::AgeClass> pi;
        //
        REQUIRE(pi.mTrackingProperties.size() == 2);
        REQUIRE(pi.mTrackingProperties[0] == Person::Location);
        REQUIRE(pi.mTrackingProperties[1] == Person::AgeClass);
    }
}

TEST_CASE("Init person index", "[PersonIndex]")
{
    SECTION("Single index with 4 tracking classes")
    {
        PersonIndexer<Person::AgeClass> pi;
        pi.init({4});
        REQUIRE(pi.mPersons.size() == 4);
    }

    SECTION("Double index with nested of 4 and 3 tracking classes")
    {
        PersonIndexer<Person::Location, Person::AgeClass> pi;
        pi.init({4, 3});
        REQUIRE(pi.mPersons.size() == 4);
        for (auto &item : pi.mPersons)
        {
            REQUIRE(item.size() == 3);
        }
    }
}

TEST_CASE("Re-Init person index clear content (return objects to pool)", "[PersonIndex]")
{

    SECTION("Single index with 4 tracking classes")
    {
        PersonIndexer<Person::AgeClass> pi;
        pi.init({4});
        REQUIRE(pi.mPersons.size() == 4);

        for (int i = 0; i < pi.mPersons.size(); ++i)
        {
            //add 100 persons to each age class
            auto &ac = pi.mPersons[i];
            for (int j = 0; j < 100; ++j)
            {
                auto p = Person::Acquire();
                ac.push_back(p);
                //   std::cout << "free list size: " << Person::objectPool.mFreeList.size() << std::endl;
            }
            REQUIRE(ac.size() == 100);
        }
        //        std::cout << "free list size: " << Person::objectPool.mFreeList.size() << std::endl;
        REQUIRE(Person::objectPool.mFreeList.size() == 100000 - 400);
        pi.init({5});
        REQUIRE(Person::objectPool.mFreeList.size() == 100000);
    }
    SECTION("Double indexes with nested 4 and 3 tracking classes")
    {
        PersonIndexer<Person::Location, Person::AgeClass> pi;

        //init with 4 locations and 3 age classes
        pi.init({4, 3});

        for (auto &location : pi.mPersons)
        {
            for (auto &ac : location)
            {
                for (int j = 0; j < 100; ++j)
                {
                    auto p = Person::Acquire();
                    ac.push_back(p);
                }
                REQUIRE(ac.size() == 100);
            }
        }

        REQUIRE(Person::objectPool.mFreeList.size() == 100000 - 100 * 12);

        //reinit will return object to pool
        pi.init({5, 2});
        REQUIRE(Person::objectPool.mFreeList.size() == 100000);
    }
}

TEST_CASE("Add Object to Indexer will add to the back of the deepest vector")
{
    SECTION("Single index with 4 tracking classes")
    {
        REQUIRE(Person::objectPool.mFreeList.size() == 100000);
        PersonIndexer<Person::AgeClass> pi;
        pi.init({4});

        auto p1 = Person::Acquire();
        pi.add(p1);
        REQUIRE(pi.mPersons[0].back() == p1);

        auto p2 = Person::Acquire();
        pi.add(p2);
        REQUIRE(pi.mPersons[0].back() == p2);
        REQUIRE(Person::objectPool.mFreeList.size() == 100000 - 2);
    }

    SECTION("Double indexes with nest of 4  and 3tracking classes")
    {
        REQUIRE(Person::objectPool.mFreeList.size() == 100000);
        PersonIndexer<Person::Location, Person::AgeClass> pi;
        pi.init({4, 3});

        auto p1 = Person::Acquire();
        pi.add(p1);
        REQUIRE(pi.mPersons[0][0].back() == p1);

        auto p2 = Person::Acquire();
        pi.add(p2);
        REQUIRE(pi.mPersons[0][0].back() == p2);
        REQUIRE(Person::objectPool.mFreeList.size() == 100000 - 2);
    }
}

TEST_CASE("Add Person add to proper nested vector")
{
    SECTION("Single index with 4 tracking classes")
    {
        REQUIRE(Person::objectPool.mFreeList.size() == 100000);
        PersonIndexer<Person::AgeClass> pi;
        pi.init({4});
        REQUIRE(pi.mPersons.size() == 4);

        auto p1 = Person::Acquire();
        p1->setAgeClass(3);
        pi.add(p1);

        REQUIRE(!pi.mPersons[3].empty());
        REQUIRE(pi.mPersons[3].back() == p1);
    }

    SECTION("Double index with 4 and 3 tracking classes")
    {
        REQUIRE(Person::objectPool.mFreeList.size() == 100000);
        PersonIndexer<Person::AgeClass, Person::State> pi;
        pi.init({4, 3});
        REQUIRE(pi.mPersons.size() == 4);

        auto p1 = Person::Acquire();
        p1->setAgeClass(3);
        p1->setHostState(Person::Exposed);
        pi.add(p1);

        REQUIRE(!pi.mPersons[3][Person::Exposed].empty());
        REQUIRE(pi.mPersons[3][Person::Exposed].back() == p1);
    }

    SECTION("Multiple indexes ")
    {
        REQUIRE(Person::objectPool.mFreeList.size() == 100000);
        PersonIndexer<Person::AgeClass> pi;
        pi.init({4});
        PersonIndexer<Person::AgeClass, Person::State> pi2;
        pi2.init({4, 3});

        REQUIRE(pi.mPersons.size() == 4);

        auto p1 = Person::Acquire();
        p1->setAgeClass(3);
        p1->setHostState(Person::Exposed);
        pi.add(p1);
        pi2.add(p1);

        REQUIRE(!pi.mPersons[3].empty());
        REQUIRE(pi.mPersons[3].back() == p1);

        REQUIRE(!pi2.mPersons[3][Person::Exposed].empty());
        REQUIRE(pi2.mPersons[3][Person::Exposed].back() == p1);
    }
}

TEST_CASE("Remove Person")
{
    SECTION("Single index with 4 tracking classes")
    {
        REQUIRE(Person::objectPool.mFreeList.size() == 100000);
        PersonIndexer<Person::AgeClass> pi;
        pi.init({4});
        REQUIRE(pi.mPersons.size() == 4);

        auto p1 = Person::Acquire();
        p1->setAgeClass(3);
        pi.add(p1);

        REQUIRE(!pi.mPersons[3].empty());
        REQUIRE(pi.mPersons[3].back() == p1);

        pi.remove(p1);

        REQUIRE(pi.mPersons[3].empty());
        REQUIRE(Person::objectPool.mFreeList.size() == 100000 - 1);
    }

    SECTION("Double index with 4 and 3 tracking classes")
    {
        REQUIRE(Person::objectPool.mFreeList.size() == 100000);
        PersonIndexer<Person::AgeClass, Person::State> pi;
        pi.init({4, 3});
        REQUIRE(pi.mPersons.size() == 4);

        auto p1 = Person::Acquire();
        p1->setAgeClass(3);
        p1->setHostState(Person::Exposed);
        pi.add(p1);

        REQUIRE(!pi.mPersons[3][Person::Exposed].empty());
        REQUIRE(pi.mPersons[3][Person::Exposed].back() == p1);

        pi.remove(p1);

        REQUIRE(pi.mPersons[3][Person::Exposed].empty());
        //        REQUIRE(pi.mPersons[3][Person::Exposed].back() == p1);

        REQUIRE(Person::objectPool.mFreeList.size() == 100000 - 1);
    }

    SECTION("Multiple objects Single index with 4 tracking classes")
    {
        REQUIRE(Person::objectPool.mFreeList.size() == 100000);
        PersonIndexer<Person::AgeClass> pi;
        pi.init({4});
        REQUIRE(pi.mPersons.size() == 4);

        auto p1 = Person::Acquire();
        p1->setAgeClass(3);
        pi.add(p1);

        auto p2 = Person::Acquire();
        p2->setAgeClass(3);
        pi.add(p2);

        REQUIRE(pi.mPersons[3].size() == 2);
        REQUIRE(pi.mPersons[3][0] == p1);
        REQUIRE(pi.mPersons[3].back() == p2);

        pi.remove(p1);

        REQUIRE(pi.mPersons[3].size() == 1);
        REQUIRE(pi.mPersons[3][0] == p2);

        REQUIRE(Person::objectPool.mFreeList.size() == 100000 - 2);
    }
}

TEST_CASE("Multiple Indexes")
{
    SECTION("3 indexes")
    {
        REQUIRE(Person::objectPool.mFreeList.size() == 100000);
        PersonIndexer<Person::AgeClass> pi1;
        pi1.init({4});
        REQUIRE(pi1.getId() == 0);

        PersonIndexer<Person::AgeClass, Person::State> pi2;
        pi2.init({4, 3});
        REQUIRE(pi2.getId() == 1);

        PersonIndexer<Person::Location, Person::AgeClass, Person::State> pi3;
        pi3.init({5, 4, 3});
        REQUIRE(pi3.getId() == 2);

        auto p1 = Person::Acquire();
        p1->setLocation(0);
        p1->setAgeClass(3);
        p1->setHostState(Person::Exposed);
        pi1.add(p1);
        pi2.add(p1);
        pi3.add(p1);

        REQUIRE(p1->getPositionInDeepestNestedVector(0) == 0);
        REQUIRE(p1->getPositionInDeepestNestedVector(1) == 0);
        REQUIRE(p1->getPositionInDeepestNestedVector(2) == 0);

        auto p2 = Person::Acquire();
        p2->setLocation(0);
        p2->setAgeClass(3);
        p2->setHostState(Person::Exposed);
        pi1.add(p2);
        pi2.add(p2);
        pi3.add(p2);

        REQUIRE(p2->getPositionInDeepestNestedVector(0) == 1);
        REQUIRE(p2->getPositionInDeepestNestedVector(1) == 1);
        REQUIRE(p2->getPositionInDeepestNestedVector(2) == 1);

        auto p3 = Person::Acquire();
        p3->setLocation(0);
        p3->setAgeClass(3);
        p3->setHostState(Person::Exposed);
        pi1.add(p3);
        pi2.add(p3);
        pi3.add(p3);

        REQUIRE(p3->getPositionInDeepestNestedVector(0) == 2);
        REQUIRE(p3->getPositionInDeepestNestedVector(1) == 2);
        REQUIRE(p3->getPositionInDeepestNestedVector(2) == 2);

        REQUIRE(p1->getPositionInDeepestNestedVector(0) == 0);

        pi1.remove(p1);
        REQUIRE(p2->getPositionInDeepestNestedVector(0) == 1);
        REQUIRE(p2->getPositionInDeepestNestedVector(1) == 1);
        REQUIRE(p2->getPositionInDeepestNestedVector(2) == 1);

        REQUIRE(p3->getPositionInDeepestNestedVector(0) == 0);
        REQUIRE(p3->getPositionInDeepestNestedVector(1) == 2);
        REQUIRE(p3->getPositionInDeepestNestedVector(2) == 2);

        //        REQUIRE(p1->getPositionInDeepestNestedVector(0) == SIZE_MAX);
        REQUIRE(p1->getPositionInDeepestNestedVector(1) == 0);
        REQUIRE(p1->getPositionInDeepestNestedVector(2) == 0);

        REQUIRE(pi1.mPersons[3].size() == 2);

        pi1.remove(p2);
        //        REQUIRE(p2->getPositionInDeepestNestedVector(0) == SIZE_MAX);
        REQUIRE(p2->getPositionInDeepestNestedVector(1) == 1);
        REQUIRE(p2->getPositionInDeepestNestedVector(2) == 1);

        REQUIRE(p3->getPositionInDeepestNestedVector(0) == 0);
        REQUIRE(p3->getPositionInDeepestNestedVector(1) == 2);
        REQUIRE(p3->getPositionInDeepestNestedVector(2) == 2);

        REQUIRE(pi1.mPersons[3].size() == 1);

        pi2.remove(p1);
        REQUIRE(pi2.mPersons[3][Person::Exposed].size() == 2);
        REQUIRE(p3->getPositionInDeepestNestedVector(1) == 0);
        //        REQUIRE(p1->getPositionInDeepestNestedVector(1) == SIZE_MAX);

        pi3.remove(p2);
        REQUIRE(pi3.mPersons[0][3][Person::Exposed].size() == 2);
        REQUIRE(p3->getPositionInDeepestNestedVector(2) == 1);
        //        REQUIRE(p2->getPositionInDeepestNestedVector(2) == SIZE_MAX);

        pi1.mPersons.clear();
        pi2.mPersons.clear();
        pi3.mPersons.clear();

        p1.reset();
        p2.reset();
        p3.reset();

        REQUIRE(Person::objectPool.mFreeList.size() == 100000);
    }
}
