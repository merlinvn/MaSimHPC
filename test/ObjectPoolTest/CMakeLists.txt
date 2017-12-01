include_directories(../../src)
add_executable(ObjectPoolSmartPointer ObjectPoolSmartPointerTest.cpp)
target_compile_features(ObjectPoolSmartPointer PRIVATE cxx_range_for)
target_link_libraries(ObjectPoolSmartPointer MaSimCore)

include_directories(../../src)
add_executable(ObjectPoolRawPointer ObjectPoolRawPointerTest.cpp)
target_compile_features(ObjectPoolRawPointer PRIVATE cxx_range_for)
target_link_libraries(ObjectPoolRawPointer MaSimCore)

include_directories(../../src)
add_executable(NonObjectPool NonObjectPoolTest.cpp)
target_compile_features(NonObjectPool PRIVATE cxx_range_for)
target_link_libraries(NonObjectPool MaSimCore)


include_directories(${GTEST_INCLUDE_DIRS})
find_package(Threads)
include_directories(../../src)
add_executable(ObjectPoolTest ObjectPoolTest.cpp)
add_dependencies(ObjectPoolTest googletest MaSimCore)
target_compile_features(ObjectPoolTest PRIVATE cxx_range_for)
target_link_libraries(ObjectPoolTest MaSimCore
        ${GTEST_LIBS_DIR}/libgtest.a
        ${GTEST_LIBS_DIR}/libgtest_main.a
        ${CMAKE_THREAD_LIBS_INIT})