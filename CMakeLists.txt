cmake_minimum_required(VERSION 3.1.0) # Set the minimum required version of cmake
project(dedicatedslave) # Set a name, version, and enable languages

if (NOT CONFIGURED_ONCE)
	IF(NOT CMAKE_BUILD_TYPE)
		SET(CMAKE_BUILD_TYPE "Release")
	ENDIF()
	set(CMAKE_INCLUDE_CURRENT_DIR OFF)
	#set(CMAKE_AUTOMOC ON) # Instruct CMake to run moc automatically when needed.
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

option(DEDICATEDSLAVE_GUI "Build Graphical User Interface" ON) # Provides options that the user can optionally select.
option(DEDICATEDSLAVE_DOCS "Build Documentation" OFF) # Provides options that the user can optionally select.
option(DEDICATEDSLAVE_DOCS_AUTO "Automatically build documentation on 'all' target" ON) # Provides options that the user can optionally select.

file(GLOB_RECURSE DEDICATEDSLAVE_HEADERS ${DEDICATEDSLAVE_ROOT_DIR}/include/*.h)
include_directories(${DEDICATEDSLAVE_ROOT_DIR}/include)

find_package(Qt5Core REQUIRED)
set_target_properties(Qt5::Core PROPERTIES MAP_IMPORTED_CONFIG_COVERAGE "RELEASE")
find_package(Qt5Widgets REQUIRED)
include_directories(${Qt5Widgets_INCLUDE_DIRS}) # Add the include directories for the Qt 5 Widgets module to the compile lines.
add_definitions(${Qt5Widgets_DEFINITIONS})
find_package(Qt5Network REQUIRED)
include_directories(${Qt5Network_INCLUDE_DIRS})
add_definitions(${Qt5Network_DEFINITIONS})
find_package(Qt5Sql REQUIRED)
include_directories(${Qt5Sql_INCLUDE_DIRS})
add_definitions(${Qt5Sql_DEFINITIONS})
qt5_wrap_cpp(DEDICATEDSLAVE_WRAP_SOURCE_LIB ${DEDICATEDSLAVE_HEADERS})

file(GLOB DEDICATEDSLAVE_SOURCE_LIB
	${DEDICATEDSLAVE_ROOT_DIR}/src/*.cpp)
add_library(dedicatedslave-lib SHARED
	${DEDICATEDSLAVE_SOURCE_LIB}
	${DEDICATEDSLAVE_HEADERS}
	${DEDICATEDSLAVE_WRAP_SOURCE_LIB})

target_link_libraries(dedicatedslave-lib curl)
set_target_properties(dedicatedslave-lib PROPERTIES OUTPUT_NAME "dedicatedslave")

install(TARGETS dedicatedslave-lib DESTINATION lib)

file(GLOB DEDICATEDSLAVE_LIB_HEADERS ${DEDICATEDSLAVE_ROOT_DIR}/include/DedicatedSlave/*.*)
install(FILES ${DEDICATEDSLAVE_LIB_HEADERS} DESTINATION include/DedicatedSlave/)

file(GLOB_RECURSE DEDICATEDSLAVE_SOURCE_UI ${DEDICATEDSLAVE_ROOT_DIR}/src/ui/*.cpp)
file(GLOB_RECURSE DEDICATEDSLAVE_HEADERS_UI ${DEDICATEDSLAVE_ROOT_DIR}/src/ui/*.h)
file(GLOB_RECURSE DEDICATEDSLAVE_RESOURCES_UI ${DEDICATEDSLAVE_ROOT_DIR}/rsrc/*.qrc)
file(GLOB_RECURSE DEDICATEDSLAVE_SOURCE_CLI ${DEDICATEDSLAVE_ROOT_DIR}/src/cli/*.cpp)
file(GLOB_RECURSE DEDICATEDSLAVE_HEADERS_CLI ${DEDICATEDSLAVE_ROOT_DIR}/src/cli/*.h)

qt5_add_resources(RES_DEDICATEDSLAVE_UI ${DEDICATEDSLAVE_RESOURCES_UI})
qt5_wrap_cpp(DEDICATEDSLAVE_WRAP_SOURCE_UI ${DEDICATEDSLAVE_HEADERS_UI})
add_executable(dedicatedslave-cli
    ${DEDICATEDSLAVE_SOURCE_CLI}) # Tell CMake to create the executables
add_executable(dedicatedslave-gui
	${DEDICATEDSLAVE_SOURCE_UI}
	${DEDICATEDSLAVE_WRAP_SOURCE_UI}
	${RES_DEDICATEDSLAVE_UI}
	${DEDICATEDSLAVE_HEADERS_UI}) # Tell CMake to create the executables
#qt5_use_modules(dedicatedslave-gui Widgets) # ArchLinux Qt5.11 Obsolete
target_link_libraries(dedicatedslave-gui Qt5::Widgets)
install(TARGETS dedicatedslave-cli DESTINATION bin) # Install Targets
install(TARGETS dedicatedslave-gui DESTINATION bin) # Install Targets
target_link_libraries(dedicatedslave-cli dedicatedslave-lib) # Specify libraries or flags to use when linking a given target and/or its dependents.
target_link_libraries(dedicatedslave-gui dedicatedslave-lib) # Specify libraries or flags to use when linking a given target and/or its dependents.
set_target_properties(dedicatedslave-cli PROPERTIES OUTPUT_NAME "dedicatedslave") # Targets can have properties that affect how they are built.
set_target_properties(dedicatedslave-gui PROPERTIES OUTPUT_NAME "dedicatedslave-gui") # Targets can have properties that affect how they are built.
