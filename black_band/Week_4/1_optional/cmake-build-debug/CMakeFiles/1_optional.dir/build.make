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
CMAKE_SOURCE_DIR = D:\Coding\Coursera\black_band\Week_4\1_optional

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Coding\Coursera\black_band\Week_4\1_optional\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/1_optional.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/1_optional.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/1_optional.dir/flags.make

CMakeFiles/1_optional.dir/main.cpp.obj: CMakeFiles/1_optional.dir/flags.make
CMakeFiles/1_optional.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\Coursera\black_band\Week_4\1_optional\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/1_optional.dir/main.cpp.obj"
	C:\dev\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\1_optional.dir\main.cpp.obj -c D:\Coding\Coursera\black_band\Week_4\1_optional\main.cpp

CMakeFiles/1_optional.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/1_optional.dir/main.cpp.i"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\Coursera\black_band\Week_4\1_optional\main.cpp > CMakeFiles\1_optional.dir\main.cpp.i

CMakeFiles/1_optional.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/1_optional.dir/main.cpp.s"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\Coursera\black_band\Week_4\1_optional\main.cpp -o CMakeFiles\1_optional.dir\main.cpp.s

# Object files for target 1_optional
1_optional_OBJECTS = \
"CMakeFiles/1_optional.dir/main.cpp.obj"

# External object files for target 1_optional
1_optional_EXTERNAL_OBJECTS =

1_optional.exe: CMakeFiles/1_optional.dir/main.cpp.obj
1_optional.exe: CMakeFiles/1_optional.dir/build.make
1_optional.exe: CMakeFiles/1_optional.dir/linklibs.rsp
1_optional.exe: CMakeFiles/1_optional.dir/objects1.rsp
1_optional.exe: CMakeFiles/1_optional.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Coding\Coursera\black_band\Week_4\1_optional\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 1_optional.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\1_optional.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/1_optional.dir/build: 1_optional.exe

.PHONY : CMakeFiles/1_optional.dir/build

CMakeFiles/1_optional.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\1_optional.dir\cmake_clean.cmake
.PHONY : CMakeFiles/1_optional.dir/clean

CMakeFiles/1_optional.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Coding\Coursera\black_band\Week_4\1_optional D:\Coding\Coursera\black_band\Week_4\1_optional D:\Coding\Coursera\black_band\Week_4\1_optional\cmake-build-debug D:\Coding\Coursera\black_band\Week_4\1_optional\cmake-build-debug D:\Coding\Coursera\black_band\Week_4\1_optional\cmake-build-debug\CMakeFiles\1_optional.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/1_optional.dir/depend

