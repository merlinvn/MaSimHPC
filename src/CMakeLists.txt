set(SOURCE_FILES Core/IPoolableObject.h 
Core/ObjectPoolSmartPointer.h 
Core/ObjectPoolRawPointer.h 
SmartPointer/Person.cpp 
SmartPointer/ParasitePopulations.cpp 
SmartPointer/SingleClonalParasitePopulation.cpp
RawPointer/Person.cpp 
RawPointer/ParasitePopulations.cpp 
RawPointer/SingleClonalParasitePopulation.cpp
PersonIndexer.cpp)

add_library(MaSimCore ${SOURCE_FILES})
target_compile_features(MaSimCore PRIVATE cxx_range_for)
