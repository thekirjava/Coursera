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
CMAKE_SOURCE_DIR = D:\Coding\yellow_band\all_permutations

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Coding\yellow_band\all_permutations\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/all_permutations.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/all_permutations.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/all_permutations.dir/flags.make

CMakeFiles/all_permutations.dir/main.cpp.obj: CMakeFiles/all_permutations.dir/flags.make
CMakeFiles/all_permutations.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\yellow_band\all_permutations\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/all_permutations.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\all_permutations.dir\main.cpp.obj -c D:\Coding\yellow_band\all_permutations\main.cpp

CMakeFiles/all_permutations.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/all_permutations.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\yellow_band\all_permutations\main.cpp > CMakeFiles\all_permutations.dir\main.cpp.i

CMakeFiles/all_permutations.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/all_permutations.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\yellow_band\all_permutations\main.cpp -o CMakeFiles\all_permutations.dir\main.cpp.s

# Object files for target all_permutations
all_permutations_OBJECTS = \
"CMakeFiles/all_permutations.dir/main.cpp.obj"

# External object files for target all_permutations
all_permutations_EXTERNAL_OBJECTS =

all_permutations.exe: CMakeFiles/all_permutations.dir/main.cpp.obj
all_permutations.exe: CMakeFiles/all_permutations.dir/build.make
all_permutations.exe: CMakeFiles/all_permutations.dir/linklibs.rsp
all_permutations.exe: CMakeFiles/all_permutations.dir/objects1.rsp
all_permutations.exe: CMakeFiles/all_permutations.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Coding\yellow_band\all_permutations\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable all_permutations.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\all_permutations.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/all_permutations.dir/build: all_permutations.exe

.PHONY : CMakeFiles/all_permutations.dir/build

CMakeFiles/all_permutations.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\all_permutations.dir\cmake_clean.cmake
.PHONY : CMakeFiles/all_permutations.dir/clean

CMakeFiles/all_permutations.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Coding\yellow_band\all_permutations D:\Coding\yellow_band\all_permutations D:\Coding\yellow_band\all_permutations\cmake-build-debug D:\Coding\yellow_band\all_permutations\cmake-build-debug D:\Coding\yellow_band\all_permutations\cmake-build-debug\CMakeFiles\all_permutations.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/all_permutations.dir/depend

