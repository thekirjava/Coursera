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
CMAKE_SOURCE_DIR = D:\Coding\red_band\refreshing

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Coding\red_band\refreshing\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/refreshing.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/refreshing.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/refreshing.dir/flags.make

CMakeFiles/refreshing.dir/main.cpp.obj: CMakeFiles/refreshing.dir/flags.make
CMakeFiles/refreshing.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\red_band\refreshing\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/refreshing.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\refreshing.dir\main.cpp.obj -c D:\Coding\red_band\refreshing\main.cpp

CMakeFiles/refreshing.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/refreshing.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\red_band\refreshing\main.cpp > CMakeFiles\refreshing.dir\main.cpp.i

CMakeFiles/refreshing.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/refreshing.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\red_band\refreshing\main.cpp -o CMakeFiles\refreshing.dir\main.cpp.s

# Object files for target refreshing
refreshing_OBJECTS = \
"CMakeFiles/refreshing.dir/main.cpp.obj"

# External object files for target refreshing
refreshing_EXTERNAL_OBJECTS =

refreshing.exe: CMakeFiles/refreshing.dir/main.cpp.obj
refreshing.exe: CMakeFiles/refreshing.dir/build.make
refreshing.exe: CMakeFiles/refreshing.dir/linklibs.rsp
refreshing.exe: CMakeFiles/refreshing.dir/objects1.rsp
refreshing.exe: CMakeFiles/refreshing.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Coding\red_band\refreshing\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable refreshing.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\refreshing.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/refreshing.dir/build: refreshing.exe

.PHONY : CMakeFiles/refreshing.dir/build

CMakeFiles/refreshing.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\refreshing.dir\cmake_clean.cmake
.PHONY : CMakeFiles/refreshing.dir/clean

CMakeFiles/refreshing.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Coding\red_band\refreshing D:\Coding\red_band\refreshing D:\Coding\red_band\refreshing\cmake-build-debug D:\Coding\red_band\refreshing\cmake-build-debug D:\Coding\red_band\refreshing\cmake-build-debug\CMakeFiles\refreshing.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/refreshing.dir/depend

