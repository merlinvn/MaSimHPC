cmake_minimum_required(VERSION 3.6)
project(ModernCpp)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(ModernCpp ${SOURCE_FILES})

add_executable(SmartPointer SmartPointer.cpp Person.cpp Person.h ParasitePopulations.cpp ParasitePopulations.h SingleClonalParasitePopulation.cpp)


add_executable(ObjectPoolSample ObjectPoolSample.cpp Person.cpp ParasitePopulations.cpp SingleClonalParasitePopulation.cpp)
add_executable(ObjectIndexerSample ObjectIndexerSample.cpp Person.cpp ParasitePopulations.cpp SingleClonalParasitePopulation.cpp test/PersonIndexTest.cpp PersonIndexer.h PersonIndexer.cpp IObjectIndexer.h Indexable.h)