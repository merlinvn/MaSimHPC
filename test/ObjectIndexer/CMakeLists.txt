include_directories(../../src)
add_executable(ObjectIndexerSample ObjectIndexerSample.cpp PersonIndexTest.cpp)
target_compile_features(ObjectIndexerSample PRIVATE cxx_range_for)
target_link_libraries(ObjectIndexerSample MaSimCore
	 Catch2::Catch
)