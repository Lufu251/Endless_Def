cmake_minimum_required(VERSION 3.11)

project(Test)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(SFML_STATIC_LIBRARIES TRUE)
set(BUILD_SHARED_LIBS OFF)
if (MSVC)
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /DNDEBUG")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -ggdb" )
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native -DNDEBUG")
endif()

include(FetchContent)

include_directories(
		"${CMAKE_CURRENT_LIST_DIR}/include" 
		"${CMAKE_CURRENT_LIST_DIR}/include/world" 
		"${CMAKE_CURRENT_LIST_DIR}/include/lib" 
		"${CMAKE_CURRENT_LIST_DIR}/include/UI" 
		"${CMAKE_CURRENT_LIST_DIR}/include/components" 
		"${CMAKE_CURRENT_LIST_DIR}/include/entitys" 
		"${CMAKE_CURRENT_LIST_DIR}/include/states")

add_executable(test
	src/main.cpp
)

# --------------- SFML ---------------
FetchContent_Declare(
	SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

target_link_libraries(test
		sfml-graphics 
		sfml-audio 
		sfml-network 
		sfml-window 
		sfml-system
)

# --------------- Eigen ---------------
FetchContent_Declare(
	Eigen
	GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
	GIT_TAG master
	GIT_SHALLOW TRUE
	GIT_PROGRESS TRUE
)

set(EIGEN_BUILD_DOC OFF)
set(BUILD_TESTING OFF)
set(EIGEN_BUILD_PKGCONFIG OFF)

FetchContent_MakeAvailable(Eigen)

target_link_libraries(test
		 Eigen3::Eigen
)