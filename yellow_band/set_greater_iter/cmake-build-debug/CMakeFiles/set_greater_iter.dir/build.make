# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.1.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.1.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Coding\yellow_band\set_greater_iter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Coding\yellow_band\set_greater_iter\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/set_greater_iter.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/set_greater_iter.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/set_greater_iter.dir/flags.make

CMakeFiles/set_greater_iter.dir/main.cpp.obj: CMakeFiles/set_greater_iter.dir/flags.make
CMakeFiles/set_greater_iter.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\yellow_band\set_greater_iter\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/set_greater_iter.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\set_greater_iter.dir\main.cpp.obj -c D:\Coding\yellow_band\set_greater_iter\main.cpp

CMakeFiles/set_greater_iter.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/set_greater_iter.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\yellow_band\set_greater_iter\main.cpp > CMakeFiles\set_greater_iter.dir\main.cpp.i

CMakeFiles/set_greater_iter.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/set_greater_iter.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\yellow_band\set_greater_iter\main.cpp -o CMakeFiles\set_greater_iter.dir\main.cpp.s

# Object files for target set_greater_iter
set_greater_iter_OBJECTS = \
"CMakeFiles/set_greater_iter.dir/main.cpp.obj"

# External object files for target set_greater_iter
set_greater_iter_EXTERNAL_OBJECTS =

set_greater_iter.exe: CMakeFiles/set_greater_iter.dir/main.cpp.obj
set_greater_iter.exe: CMakeFiles/set_greater_iter.dir/build.make
set_greater_iter.exe: CMakeFiles/set_greater_iter.dir/linklibs.rsp
set_greater_iter.exe: CMakeFiles/set_greater_iter.dir/objects1.rsp
set_greater_iter.exe: CMakeFiles/set_greater_iter.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Coding\yellow_band\set_greater_iter\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable set_greater_iter.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\set_greater_iter.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/set_greater_iter.dir/build: set_greater_iter.exe

.PHONY : CMakeFiles/set_greater_iter.dir/build

CMakeFiles/set_greater_iter.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\set_greater_iter.dir\cmake_clean.cmake
.PHONY : CMakeFiles/set_greater_iter.dir/clean

CMakeFiles/set_greater_iter.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Coding\yellow_band\set_greater_iter D:\Coding\yellow_band\set_greater_iter D:\Coding\yellow_band\set_greater_iter\cmake-build-debug D:\Coding\yellow_band\set_greater_iter\cmake-build-debug D:\Coding\yellow_band\set_greater_iter\cmake-build-debug\CMakeFiles\set_greater_iter.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/set_greater_iter.dir/depend

