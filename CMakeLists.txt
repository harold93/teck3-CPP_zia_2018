project(zia)
cmake_minimum_required(VERSION 2.8.12)

if (WIN32)
#	do not touch please
	add_definitions("-std=c++17 -Wall -g3")
ELSE()
#	on LINUX
	add_definitions("-std=c++17 -Wall -Wextra -g3 -Wno-unused-but-set-variable") # -Wno-unused-result
ENDIF()

# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
	message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
	file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/v0.12/conan.cmake"
		"${CMAKE_BINARY_DIR}/conan.cmake")
endif()

# Setup conan
include(${CMAKE_BINARY_DIR}/conan.cmake)
conan_check()

conan_add_remote(NAME bincrafters INDEX 1
	URL https://api.bintray.com/conan/bincrafters/public-conan)
conan_add_remote(NAME conan-community INDEX 2
	URL https://api.bintray.com/conan/conan-community/conan)

set(CMAKE_BUILD_TYPE Release)
conan_cmake_run(CONANFILE conanfile.txt
	BASIC_SETUP
	BUILD missing)

conan_basic_setup()

# Variables (path, include, etc)
set(DIR src/)

# include Directories (for .hpp)
include_directories(
        ${CMAKE_SOURCE_DIR}/include
)

# Sources and Libraries
add_executable(zia
		${DIR}main.cpp
		src/components/server/Server.cpp
		src/components/server/Server.h
		src/components/server/TcpConnection.cpp
		src/components/server/TcpConnection.h)

target_link_libraries(zia ${CONAN_LIBS})

if (WIN32)
	set_target_properties(zia
				PROPERTIES
				CXX_STANDARD 17
	)
ENDIF()
