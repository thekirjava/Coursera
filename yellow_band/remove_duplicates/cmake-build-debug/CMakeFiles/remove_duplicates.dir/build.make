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
CMAKE_SOURCE_DIR = D:\Coding\yellow_band\remove_duplicates

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Coding\yellow_band\remove_duplicates\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/remove_duplicates.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/remove_duplicates.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/remove_duplicates.dir/flags.make

CMakeFiles/remove_duplicates.dir/main.cpp.obj: CMakeFiles/remove_duplicates.dir/flags.make
CMakeFiles/remove_duplicates.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\yellow_band\remove_duplicates\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/remove_duplicates.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\remove_duplicates.dir\main.cpp.obj -c D:\Coding\yellow_band\remove_duplicates\main.cpp

CMakeFiles/remove_duplicates.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/remove_duplicates.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\yellow_band\remove_duplicates\main.cpp > CMakeFiles\remove_duplicates.dir\main.cpp.i

CMakeFiles/remove_duplicates.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/remove_duplicates.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\yellow_band\remove_duplicates\main.cpp -o CMakeFiles\remove_duplicates.dir\main.cpp.s

# Object files for target remove_duplicates
remove_duplicates_OBJECTS = \
"CMakeFiles/remove_duplicates.dir/main.cpp.obj"

# External object files for target remove_duplicates
remove_duplicates_EXTERNAL_OBJECTS =

remove_duplicates.exe: CMakeFiles/remove_duplicates.dir/main.cpp.obj
remove_duplicates.exe: CMakeFiles/remove_duplicates.dir/build.make
remove_duplicates.exe: CMakeFiles/remove_duplicates.dir/linklibs.rsp
remove_duplicates.exe: CMakeFiles/remove_duplicates.dir/objects1.rsp
remove_duplicates.exe: CMakeFiles/remove_duplicates.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Coding\yellow_band\remove_duplicates\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable remove_duplicates.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\remove_duplicates.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/remove_duplicates.dir/build: remove_duplicates.exe

.PHONY : CMakeFiles/remove_duplicates.dir/build

CMakeFiles/remove_duplicates.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\remove_duplicates.dir\cmake_clean.cmake
.PHONY : CMakeFiles/remove_duplicates.dir/clean

CMakeFiles/remove_duplicates.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Coding\yellow_band\remove_duplicates D:\Coding\yellow_band\remove_duplicates D:\Coding\yellow_band\remove_duplicates\cmake-build-debug D:\Coding\yellow_band\remove_duplicates\cmake-build-debug D:\Coding\yellow_band\remove_duplicates\cmake-build-debug\CMakeFiles\remove_duplicates.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/remove_duplicates.dir/depend
