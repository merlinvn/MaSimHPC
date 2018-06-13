include_directories(../../src)
add_executable(ObjectIndexerSample ../catch.h ObjectIndexerSample.cpp PersonIndexTest.cpp)
target_compile_features(ObjectIndexerSample PRIVATE cxx_range_for)
target_link_libraries(ObjectIndexerSample MaSimCore)