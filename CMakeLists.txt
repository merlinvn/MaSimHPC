cmake_minimum_required(VERSION 3.2)
project(MaSimHpc)

set(EXT_PROJECTS_DIR ${PROJECT_SOURCE_DIR}/ext)
ADD_SUBDIRECTORY(${EXT_PROJECTS_DIR}/googletest)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

ADD_SUBDIRECTORY(src)

ADD_SUBDIRECTORY(test)

#set(SOURCE_FILES src/main.cpp)
#add_executable(ModernCpp ${SOURCE_FILES})
#
#add_executable(SmartPointer src/SmartPointer.cpp src/Person.cpp src/Person.h src/ParasitePopulations.cpp src/ParasitePopulations.h src/SingleClonalParasitePopulation.cpp)
#target_compile_features(SmartPointer PRIVATE cxx_range_for)
#
#add_executable(ObjectPoolSample src/Core/ObjectPool.h src/ObjectPoolSample.cpp src/Person.cpp src/ParasitePopulations.cpp src/SingleClonalParasitePopulation.cpp)
#target_compile_features(ObjectPoolSample PRIVATE cxx_range_for)
#
#add_executable(ObjectIndexerSample src/catch.h src/ObjectIndexerSample.cpp src/Person.cpp src/ParasitePopulations.cpp src/SingleClonalParasitePopulation.cpp test/PersonIndexTest.cpp src/PersonIndexer.h src/PersonIndexer.cpp src/IObjectIndexer.h src/Indexable.h)
#target_compile_features(ObjectIndexerSample PRIVATE cxx_range_for)