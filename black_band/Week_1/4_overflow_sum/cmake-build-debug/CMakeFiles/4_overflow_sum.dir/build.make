# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Disable VCS-based implicit rules.
% : %,v


# Disable VCS-based implicit rules.
% : RCS/%


# Disable VCS-based implicit rules.
% : RCS/%,v


# Disable VCS-based implicit rules.
% : SCCS/s.%


# Disable VCS-based implicit rules.
% : s.%


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

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
RM = "C:\Program Files\JetBrains\CLion 2019.1.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Coding\Coursera\black_band\Week_1\4_overflow_sum

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Coding\Coursera\black_band\Week_1\4_overflow_sum\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/4_overflow_sum.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/4_overflow_sum.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/4_overflow_sum.dir/flags.make

CMakeFiles/4_overflow_sum.dir/main.cpp.obj: CMakeFiles/4_overflow_sum.dir/flags.make
CMakeFiles/4_overflow_sum.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\Coursera\black_band\Week_1\4_overflow_sum\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/4_overflow_sum.dir/main.cpp.obj"
	C:\dev\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\4_overflow_sum.dir\main.cpp.obj -c D:\Coding\Coursera\black_band\Week_1\4_overflow_sum\main.cpp

CMakeFiles/4_overflow_sum.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/4_overflow_sum.dir/main.cpp.i"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\Coursera\black_band\Week_1\4_overflow_sum\main.cpp > CMakeFiles\4_overflow_sum.dir\main.cpp.i

CMakeFiles/4_overflow_sum.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/4_overflow_sum.dir/main.cpp.s"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\Coursera\black_band\Week_1\4_overflow_sum\main.cpp -o CMakeFiles\4_overflow_sum.dir\main.cpp.s

# Object files for target 4_overflow_sum
4_overflow_sum_OBJECTS = \
"CMakeFiles/4_overflow_sum.dir/main.cpp.obj"

# External object files for target 4_overflow_sum
4_overflow_sum_EXTERNAL_OBJECTS =

4_overflow_sum.exe: CMakeFiles/4_overflow_sum.dir/main.cpp.obj
4_overflow_sum.exe: CMakeFiles/4_overflow_sum.dir/build.make
4_overflow_sum.exe: CMakeFiles/4_overflow_sum.dir/linklibs.rsp
4_overflow_sum.exe: CMakeFiles/4_overflow_sum.dir/objects1.rsp
4_overflow_sum.exe: CMakeFiles/4_overflow_sum.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Coding\Coursera\black_band\Week_1\4_overflow_sum\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 4_overflow_sum.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\4_overflow_sum.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/4_overflow_sum.dir/build: 4_overflow_sum.exe

.PHONY : CMakeFiles/4_overflow_sum.dir/build

CMakeFiles/4_overflow_sum.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\4_overflow_sum.dir\cmake_clean.cmake
.PHONY : CMakeFiles/4_overflow_sum.dir/clean

CMakeFiles/4_overflow_sum.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Coding\Coursera\black_band\Week_1\4_overflow_sum D:\Coding\Coursera\black_band\Week_1\4_overflow_sum D:\Coding\Coursera\black_band\Week_1\4_overflow_sum\cmake-build-debug D:\Coding\Coursera\black_band\Week_1\4_overflow_sum\cmake-build-debug D:\Coding\Coursera\black_band\Week_1\4_overflow_sum\cmake-build-debug\CMakeFiles\4_overflow_sum.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/4_overflow_sum.dir/depend

