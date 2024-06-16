cmake_minimum_required(VERSION 3.28)

set(DIRECTORY Linear)

add_executable(${DIRECTORY}
	src/main.cpp
)

target_link_libraries(${DIRECTORY} PRIVATE glm::glm)