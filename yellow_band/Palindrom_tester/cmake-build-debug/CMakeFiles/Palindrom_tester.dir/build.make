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
CMAKE_SOURCE_DIR = D:\Coding\yellow_band\Palindrom_tester

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Coding\yellow_band\Palindrom_tester\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Palindrom_tester.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Palindrom_tester.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Palindrom_tester.dir/flags.make

CMakeFiles/Palindrom_tester.dir/main.cpp.obj: CMakeFiles/Palindrom_tester.dir/flags.make
CMakeFiles/Palindrom_tester.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\yellow_band\Palindrom_tester\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Palindrom_tester.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Palindrom_tester.dir\main.cpp.obj -c D:\Coding\yellow_band\Palindrom_tester\main.cpp

CMakeFiles/Palindrom_tester.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Palindrom_tester.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\yellow_band\Palindrom_tester\main.cpp > CMakeFiles\Palindrom_tester.dir\main.cpp.i

CMakeFiles/Palindrom_tester.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Palindrom_tester.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\yellow_band\Palindrom_tester\main.cpp -o CMakeFiles\Palindrom_tester.dir\main.cpp.s

# Object files for target Palindrom_tester
Palindrom_tester_OBJECTS = \
"CMakeFiles/Palindrom_tester.dir/main.cpp.obj"

# External object files for target Palindrom_tester
Palindrom_tester_EXTERNAL_OBJECTS =

Palindrom_tester.exe: CMakeFiles/Palindrom_tester.dir/main.cpp.obj
Palindrom_tester.exe: CMakeFiles/Palindrom_tester.dir/build.make
Palindrom_tester.exe: CMakeFiles/Palindrom_tester.dir/linklibs.rsp
Palindrom_tester.exe: CMakeFiles/Palindrom_tester.dir/objects1.rsp
Palindrom_tester.exe: CMakeFiles/Palindrom_tester.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Coding\yellow_band\Palindrom_tester\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Palindrom_tester.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Palindrom_tester.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Palindrom_tester.dir/build: Palindrom_tester.exe

.PHONY : CMakeFiles/Palindrom_tester.dir/build

CMakeFiles/Palindrom_tester.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Palindrom_tester.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Palindrom_tester.dir/clean

CMakeFiles/Palindrom_tester.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Coding\yellow_band\Palindrom_tester D:\Coding\yellow_band\Palindrom_tester D:\Coding\yellow_band\Palindrom_tester\cmake-build-debug D:\Coding\yellow_band\Palindrom_tester\cmake-build-debug D:\Coding\yellow_band\Palindrom_tester\cmake-build-debug\CMakeFiles\Palindrom_tester.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Palindrom_tester.dir/depend

