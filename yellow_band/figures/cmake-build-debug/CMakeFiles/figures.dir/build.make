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
CMAKE_SOURCE_DIR = D:\Coding\yellow_band\figures

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Coding\yellow_band\figures\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/figures.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/figures.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/figures.dir/flags.make

CMakeFiles/figures.dir/main.cpp.obj: CMakeFiles/figures.dir/flags.make
CMakeFiles/figures.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\yellow_band\figures\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/figures.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\figures.dir\main.cpp.obj -c D:\Coding\yellow_band\figures\main.cpp

CMakeFiles/figures.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/figures.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\yellow_band\figures\main.cpp > CMakeFiles\figures.dir\main.cpp.i

CMakeFiles/figures.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/figures.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\yellow_band\figures\main.cpp -o CMakeFiles\figures.dir\main.cpp.s

# Object files for target figures
figures_OBJECTS = \
"CMakeFiles/figures.dir/main.cpp.obj"

# External object files for target figures
figures_EXTERNAL_OBJECTS =

figures.exe: CMakeFiles/figures.dir/main.cpp.obj
figures.exe: CMakeFiles/figures.dir/build.make
figures.exe: CMakeFiles/figures.dir/linklibs.rsp
figures.exe: CMakeFiles/figures.dir/objects1.rsp
figures.exe: CMakeFiles/figures.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Coding\yellow_band\figures\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable figures.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\figures.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/figures.dir/build: figures.exe

.PHONY : CMakeFiles/figures.dir/build

CMakeFiles/figures.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\figures.dir\cmake_clean.cmake
.PHONY : CMakeFiles/figures.dir/clean

CMakeFiles/figures.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Coding\yellow_band\figures D:\Coding\yellow_band\figures D:\Coding\yellow_band\figures\cmake-build-debug D:\Coding\yellow_band\figures\cmake-build-debug D:\Coding\yellow_band\figures\cmake-build-debug\CMakeFiles\figures.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/figures.dir/depend

