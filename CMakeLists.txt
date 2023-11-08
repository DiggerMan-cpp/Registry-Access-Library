cmake_minimum_required (VERSION 3.8)


project ("DiggerRegeditEdit")
add_library(${PROJECT_NAME} STATIC)
target_include_directories(${PROJECT_NAME} PRIVATE include)
target_sources(${PROJECT_NAME} PRIVATE
	src/Key.cpp
	src/Value.cpp
	src/ValueIterator.cpp
)