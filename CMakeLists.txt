cmake_minimum_required(VERSION 3.15)

#! Check every comment after the "#!"

#! CHANGE YOUR PROJECT NAME
#  It is used as your project's main executable name. 
set(PROJECT_NAME my_paint)
project(${PROJECT_NAME} C CXX) # project(${PROJECT_NAME} C CXX ASM)

set(CMAKE_CXX_STANDARD 20)

##########################################################
# User configurable options of the template
##########################################################
# Note: symbols like WARNINGS_AS_ERRORS in configuration are intentionally variables
# and not CMake options --using options creates too many problems for students.

#! It is a good practice to set "WARNINGS_AS_ERRORS" ON,
#  but sometimes it creates too much trouble, so default is OFF.
set(WARNINGS_AS_ERRORS OFF)

#! Always use PVS Studio while developing.
set(ENABLE_PVS_STUDIO OFF)
set(CMAKE_AUTOMOC ON)
set (CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH};/usr/local/Qt-6.7.0/")
message("${CMAKE_PREFIX_PATH}")
#! Select appropriate sanitizers.
#  Definitely enable sanitizers while developing.
#  Disable it for the production builds and before submitting for grading.
#  Only one of the Memory (MSAN), Address (ASAN), or Thread (TSan)
#  sanitizers is applicable at the time -- the first defined.

#! UndefinedBehaviorSanitizer (UBSan).
#  Info: https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
set(ENABLE_UBSan OFF)
#! AddressSanitizer -- detects use after free or after scope exit,
#  memory overflows and leaks.
#  Info: https://github.com/google/sanitizers/wiki/AddressSanitizer
set(ENABLE_ASAN OFF)
#! ThreadSanitizer -- detects data races.
#  Info: https://clang.llvm.org/docs/ThreadSanitizer.html
set(ENABLE_TSan OFF)
#! MemorySanitizer -- detects uninitialized memory reads
#  Info: https://github.com/google/sanitizers/wiki/MemorySanitizer
set(ENABLE_MSAN OFF)

#! Be default -- build release version if not specified otherwise.
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif ()

# Warnings as errors should be imported here -- do not move this line
include(cmake/CompilerWarnings.cmake)

##########################################################
# Project files, packages, libraries and so on
##########################################################
find_package(Qt6 REQUIRED COMPONENTS Widgets Svg)
set (RESOURCE_FILE icons/resource.qrc)
#! Project main executable source compilation
file(GLOB_RECURSE PROJECT_INCLUDES include/*.h)

#! Put path to your project headers
set(CMAKE_AUTOMOC ON) 
set(CMAKE_AUTORCC ON) 
set(CMAKE_AUTOUIC ON)

add_executable(${PROJECT_NAME} src/main.cpp  ${PROJECT_INCLUDES}
src/MainWindow.cpp
src/Menu.cpp
src/ToolBar.cpp
src/Canvas.cpp
src/Button.cpp
src/Layer.cpp
${RESOURCE_FILE}
src/Tool.cpp
include/LayerBar.h
src/LayerBar.cpp
src/LayerWidget.cpp
include/LayerWidget.h
)


target_link_libraries(${PROJECT_NAME} Qt6::Widgets Qt6::Svg Qt6::Gui)
set_target_properties(${PROJECT_NAME} PROPERTIES
                WIN32_EXECUTABLE ON
                MACOSX_BUNDLE ON
)
#! Add external packages
# options_parser requires boost::program_options library
target_include_directories(${PROJECT_NAME} PRIVATE include)


##########################################################
# Fixed CMakeLists.txt part
##########################################################

INSTALL(PROGRAMS
		$<TARGET_FILE:${PROJECT_NAME}> # ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
		DESTINATION bin)

# Define ALL_TARGETS variable to use in PVS and Sanitizers
set(ALL_TARGETS ${PROJECT_NAME})

# Include CMake setup
include(cmake/main-config.cmake)
