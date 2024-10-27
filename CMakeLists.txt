# ========================================================
# CMake Configuration for the Sortiva Project
# ========================================================

# Specify the minimum CMake version required
cmake_minimum_required(VERSION 3.22)

# Project name, languages, and version
project(sortiva
  LANGUAGES CXX
  VERSION 1.0.0
)

# ========================================================
# C++ Standard and General Settings
# ========================================================

set(CMAKE_CXX_STANDARD 20)                   # Use C++20
set(CMAKE_CXX_STANDARD_REQUIRED ON)          # Enforce C++20 standard
set(CMAKE_CXX_EXTENSIONS OFF)                # Disable compiler-specific extensions
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)        # Generate compile commands (useful for IDEs)
set(USE_FOLDERS ON)                          # Organize targets into folders (for IDEs)
set(BUILD_SHARED_LIBS OFF)                   # Build static libraries by default

# =======================================================
# Helper Functions: 
# 	Puts Targets into a Folder
#	Finds all files in a dir wich are defined file-types
# =======================================================
# This function puts targets into a specified folder.
# It checks if the target exists and gets the actual target (if it is aliased).
# It then sets the folder property for the target.

function(put_targets_into_folder)
    set(oneValueArgs FOLDER)
    set(multiValueArgs TARGETS)
    cmake_parse_arguments(ARGS "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    foreach(target ${ARGS_TARGETS})
        # Check if target exists
        if (NOT TARGET ${target})
            message(FATAL_ERROR "${target} target not found")
        endif()

        # Get the actual target (if it is aliased)
        get_target_property(actual_target ${target} ALIASED_TARGET)
        if (NOT actual_target)
            set(actual_target ${target})
        endif()

        # Set the folder property for the target
        set_target_properties(${actual_target} PROPERTIES FOLDER ${ARGS_FOLDER})
    endforeach()
endfunction()


function(find_files var_name path)
    set(sources)
    foreach(ext ${ARGN})
        file(GLOB_RECURSE files "${path}/*.${ext}")
        list(APPEND sources ${files})
    endforeach()
    set(${var_name} ${${var_name}} ${sources} PARENT_SCOPE)
endfunction()

# ========================================================
# FetchContent Setup
# ========================================================
# FetchContent allows us to retrieve external libraries (e.g., Sol2, Google Test) dynamically.

include(FetchContent)

# Set FetchContent to work offline if needed
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)	# Prevent automatic updates
set(FETCHCONTENT_QUIET OFF)					# Display download progress
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)		# Generate compile_commands.json

# ========================================================
# Options
# ========================================================

option(SVA_BUILD_TEST ON)					# Option for test to be build as well

# ========================================================
# External Dependencies
# ========================================================

# --- Add Sol2 (Lua C++ Binding Library)
FetchContent_Declare(
  sol2
  GIT_REPOSITORY https://github.com/ThePhD/sol2.git
  GIT_TAG v3.3.0
)
FetchContent_MakeAvailable(sol2)

# ========================================================
# Helper Function: Set Common Target Properties
# ========================================================
# This function defines common properties (such as libraries and include directories)
# that are shared among all targets.

function(set_common_properties target)
	target_link_libraries(${target} PRIVATE sol2::sol2)  # Link with Sol2
	target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)  # Include project headers
	target_sources(${target} PRIVATE ${SVA_COMMON_FILES})  # Include common files
endfunction()

# ========================================================
# GUI Setup
# ========================================================

set(GUI_TARGET_NAME "${PROJECT_NAME}")
# --- Create GUI Executable
  
find_files(SVA_GUI_FILES "./src/gui/" hpp cpp h c hxx cxx)
add_executable(${GUI_TARGET_NAME}
	src/main.cpp  # Entry point for the GUI application
	src/sva.hpp  # Header file for the console
	${SVA_GUI_FILES}
)
  
# ---------------
# RAYLIB
# ---------------
# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED

if (NOT raylib_FOUND) # If there's none, fetch and build raylib
	include(FetchContent)
	FetchContent_Declare(
		raylib
		DOWNLOAD_EXTRACT_TIMESTAMP OFF
		URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
	)
	FetchContent_GetProperties(raylib)
	if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
		set(FETCHCONTENT_QUIET NO)
		FetchContent_MakeAvailable(raylib)
		set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
	endif()
endif()

put_targets_into_folder(FOLDER "raylib" TARGETS raylib uninstall)

target_link_libraries(${GUI_TARGET_NAME} PRIVATE raylib)

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
	target_link_libraries(${PROJECT_NAME} "-framework IOKit")
	target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
	target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

# -------------------------------
# SFML (Not used anymore)
# -------------------------------
#
# --- Add SFML (Simple and Fast Multimedia Library)
# FetchContent_Declare(SFML
#   GIT_REPOSITORY https://github.com/SFML/SFML.git
#   GIT_TAG 2.6.x
#   GIT_SHALLOW ON
#   EXCLUDE_FROM_ALL
#   SYSTEM
# )
# FetchContent_MakeAvailable(SFML)
#
# target_link_libraries(${GUI_TARGET_NAME} PRIVATE sfml-graphics)  # Link SFML graphics library  
#
# --- Special handling for Windows: Copy OpenAL DLL (for sound support)
# if(WIN32)
#   add_custom_command(
#     TARGET ${GUI_TARGET_NAME}
#     COMMENT "Copy OpenAL DLL"
#     PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${GUI_TARGET_NAME}>
#     VERBATIM
#   )
# endif()
# // SFML is not used anymore
  
set_common_properties(${GUI_TARGET_NAME})

	
# ========================================================
# Test Setup (Only if SVA_BUILD_TEST is ON)
# ========================================================

if(${SVA_BUILD_TEST})
	# --- Add Google Test
	FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG release-1.12.1
	)
	set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)   # Prevent shared CRT issues on Windows
	FetchContent_MakeAvailable(googletest)
	
	# Enable testing support
	enable_testing()
	
	# --- Create Test Executable
	add_executable(
		sortiva_test
		tests/test_main.cpp          # Test entry point
		tests/test_sorting_functions.cpp
	)
	
	target_link_libraries(
		sortiva_test
		PRIVATE GTest::gtest_main    # Link Google Test framework
	)
	set_common_properties(sortiva_test)
	
	# --- Enable Google Test's test discovery feature
	include(GoogleTest)
	gtest_discover_tests(sortiva_test)
	
	# put google test targets into a folder
	put_targets_into_folder(
		FOLDER "gtest"
		TARGETS
		GTest::gtest_main 
		GTest::gmock_main 
		GTest::gmock 
		GTest::gtest
	)
endif()

