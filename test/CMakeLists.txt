include_directories(../src)
add_executable(ObjectPoolSample ObjectPoolSample.cpp)
target_compile_features(ObjectPoolSample PRIVATE cxx_range_for)
target_link_libraries(ObjectPoolSample MaSimCore)

#set(SOURCE_FILES src/main.cpp)
#add_executable(ModernCpp ${SOURCE_FILES})
#
#add_executable(SmartPointer src/SmartPointer.cpp src/Person.cpp src/Person.h src/ParasitePopulations.cpp src/ParasitePopulations.h src/SingleClonalParasitePopulation.cpp)
#target_compile_features(SmartPointer PRIVATE cxx_range_for)
#
#add_executable(ObjectPoolSample src/Core/ObjectPool.h src/ObjectPoolSample.cpp src/Person.cpp src/ParasitePopulations.cpp src/SingleClonalParasitePopulation.cpp)
#target_compile_features(ObjectPoolSample PRIVATE cxx_range_for)
#

add_executable(ObjectIndexerSample catch.h ObjectIndexerSample.cpp PersonIndexTest.cpp)
target_compile_features(ObjectIndexerSample PRIVATE cxx_range_for)
target_link_libraries(ObjectIndexerSample MaSimCore)