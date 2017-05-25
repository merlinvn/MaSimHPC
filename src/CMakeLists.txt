set(SOURCE_FILES Core/ObjectPool.h Person.cpp ParasitePopulations.cpp SingleClonalParasitePopulation.cpp
    PersonIndexer.cpp)
add_library(MaSimCore ${SOURCE_FILES})
target_compile_features(MaSimCore PRIVATE cxx_range_for)
