#include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(ConfigTest Config.h Config.cpp ConfigTest.cpp main.cpp)
target_link_libraries(ConfigTest 
	Catch2::Catch
)
target_compile_features(ConfigTest PRIVATE cxx_range_for)

install(TARGETS ConfigTest DESTINATION ${PROJECT_SOURCE_DIR}/bin)