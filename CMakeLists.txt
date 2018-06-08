cmake_minimum_required(VERSION 3.1.0)

project(dedicatedslave)

if (NOT CONFIGURED_ONCE)
	IF(NOT CMAKE_BUILD_TYPE)
		SET(CMAKE_BUILD_TYPE "Release")
	ENDIF()

	set(CMAKE_INCLUDE_CURRENT_DIR OFF)
	#set(CMAKE_AUTOMOC ON)
	set(DEDICATEDSLAVE_ROOT_DIR ${CMAKE_SOURCE_DIR})

	set_property(GLOBAL PROPERTY CXX_STANDARD 14)
	set_property(GLOBAL PROPERTY CXX_STANDARD_REQUIRED ON)

	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++1y")
	SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++1y")

	IF(CMAKE_GENERATOR MATCHES "Ninja")
		SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fdiagnostics-color")
		SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fdiagnostics-color")
	ENDIF()

	SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Og -g3 -Wall -Wextra -Wformat -pedantic -Wdouble-promotion")
	SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g0 -w -Wl,-rpath,\"\\$$ORIGIN:\\$$ORIGIN/lib\"")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
	set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_RELEASE} -fprofile-arcs -ftest-coverage")

	#Define output directory
	IF(CMAKE_BUILD_TYPE MATCHES Debug)
		SET(LIBRARY_OUTPUT_PATH ${DEDICATEDSLAVE_ROOT_DIR}/out/dbg/bin)
		SET(EXECUTABLE_OUTPUT_PATH ${DEDICATEDSLAVE_ROOT_DIR}/out/dbg/bin)
		set(AUTOGEN_TARGETS_FOLDER ${DEDICATEDSLAVE_ROOT_DIR}/out/dbg/obj)
	else()
		SET(LIBRARY_OUTPUT_PATH ${DEDICATEDSLAVE_ROOT_DIR}/out/bin)
		SET(EXECUTABLE_OUTPUT_PATH ${DEDICATEDSLAVE_ROOT_DIR}/out/bin)
		set(AUTOGEN_TARGETS_FOLDER ${DEDICATEDSLAVE_ROOT_DIR}/out/obj)
	ENDIF()
endif()

option(DEDICATEDSLAVE_GUI "Build Graphical User Interface" ON)
option(DEDICATEDSLAVE_DOCS "Build Documentation" OFF)
option(DEDICATEDSLAVE_DOCS_AUTO "Automatically build documentation on 'all' target" ON)

file(GLOB_RECURSE DEDICATEDSLAVE_HEADERS ${DEDICATEDSLAVE_ROOT_DIR}/include/*.h)
include_directories(${DEDICATEDSLAVE_ROOT_DIR}/include)

find_package(Qt5Core REQUIRED)
set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")

find_package(Qt5Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
add_definitions(${Qt5Widgets_DEFINITIONS})

find_package(Qt5Network REQUIRED)
include_directories(${Qt5Network_INCLUDE_DIRS})
add_definitions(${Qt5Network_DEFINITIONS})

find_package(Qt5Sql REQUIRED)
include_directories(${Qt5Sql_INCLUDE_DIRS})
add_definitions(${Qt5Sql_DEFINITIONS})

qt5_wrap_cpp(DEDICATEDSLAVE_WRAP_SOURCE_LIB ${DEDICATEDSLAVE_HEADERS})

file(GLOB DEDICATEDSLAVE_SOURCE_LIB ${DEDICATEDSLAVE_ROOT_DIR}/src/*.cpp)
add_library(dedicatedslave-lib SHARED ${DEDICATEDSLAVE_SOURCE_LIB}
	${DEDICATEDSLAVE_HEADERS} ${DEDICATEDSLAVE_WRAP_SOURCE_LIB})

target_link_libraries(dedicatedslave-lib curl)
set_target_properties(dedicatedslave-lib PROPERTIES OUTPUT_NAME "dedicatedslave")

install(TARGETS dedicatedslave-lib DESTINATION lib)

file(GLOB DEDICATEDSLAVE_LIB_HEADERS ${DEDICATEDSLAVE_ROOT_DIR}/include/DedicatedSlave/*.*)
install(FILES ${DEDICATEDSLAVE_LIB_HEADERS} DESTINATION include/DedicatedSlave/)

file(GLOB_RECURSE DEDICATEDSLAVE_SOURCE_UI ${DEDICATEDSLAVE_ROOT_DIR}/src/ui/*.cpp)
file(GLOB_RECURSE DEDICATEDSLAVE_HEADERS_UI ${DEDICATEDSLAVE_ROOT_DIR}/src/ui/*.h)
#file(GLOB_RECURSE DEDICATEDSLAVE_RESOURCES_UI ${DEDICATEDSLAVE_ROOT_DIR}/rsrc/*.qrc)
file(GLOB_RECURSE DEDICATEDSLAVE_SOURCE_CLI ${DEDICATEDSLAVE_ROOT_DIR}/src/cli/*.cpp)
file(GLOB_RECURSE DEDICATEDSLAVE_HEADERS_CLI ${DEDICATEDSLAVE_ROOT_DIR}/src/cli/*.h)

qt5_add_resources(RES_DEDICATEDSLAVE_UI ${DEDICATEDSLAVE_RESOURCES_UI})
qt5_wrap_cpp(DEDICATEDSLAVE_WRAP_SOURCE_UI ${DEDICATEDSLAVE_HEADERS_UI})

add_executable(dedicatedslave-cli ${DEDICATEDSLAVE_SOURCE_CLI})
add_executable(dedicatedslave-gui ${DEDICATEDSLAVE_SOURCE_UI}
	${DEDICATEDSLAVE_WRAP_SOURCE_UI}
	${RES_DEDICATEDSLAVE_UI}
	${DEDICATEDSLAVE_HEADERS_UI})

qt5_use_modules(dedicatedslave-gui Widgets)

install(TARGETS dedicatedslave-cli DESTINATION bin)
install(TARGETS dedicatedslave-gui DESTINATION bin)

target_link_libraries(dedicatedslave-cli dedicatedslave-lib)
target_link_libraries(dedicatedslave-gui dedicatedslave-lib)
set_target_properties(dedicatedslave-cli PROPERTIES OUTPUT_NAME "dedicatedslave")
set_target_properties(dedicatedslave-gui PROPERTIES OUTPUT_NAME "dedicatedslave-gui")
