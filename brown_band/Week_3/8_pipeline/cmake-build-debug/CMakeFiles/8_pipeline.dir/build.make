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
CMAKE_SOURCE_DIR = D:\Coding\Coursera\brown_band\Week_3\8_pipeline

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Coding\Coursera\brown_band\Week_3\8_pipeline\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/8_pipeline.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/8_pipeline.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/8_pipeline.dir/flags.make

CMakeFiles/8_pipeline.dir/main.cpp.obj: CMakeFiles/8_pipeline.dir/flags.make
CMakeFiles/8_pipeline.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\Coursera\brown_band\Week_3\8_pipeline\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/8_pipeline.dir/main.cpp.obj"
	C:\dev\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\8_pipeline.dir\main.cpp.obj -c D:\Coding\Coursera\brown_band\Week_3\8_pipeline\main.cpp

CMakeFiles/8_pipeline.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/8_pipeline.dir/main.cpp.i"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\Coursera\brown_band\Week_3\8_pipeline\main.cpp > CMakeFiles\8_pipeline.dir\main.cpp.i

CMakeFiles/8_pipeline.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/8_pipeline.dir/main.cpp.s"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\Coursera\brown_band\Week_3\8_pipeline\main.cpp -o CMakeFiles\8_pipeline.dir\main.cpp.s

# Object files for target 8_pipeline
8_pipeline_OBJECTS = \
"CMakeFiles/8_pipeline.dir/main.cpp.obj"

# External object files for target 8_pipeline
8_pipeline_EXTERNAL_OBJECTS =

8_pipeline.exe: CMakeFiles/8_pipeline.dir/main.cpp.obj
8_pipeline.exe: CMakeFiles/8_pipeline.dir/build.make
8_pipeline.exe: CMakeFiles/8_pipeline.dir/linklibs.rsp
8_pipeline.exe: CMakeFiles/8_pipeline.dir/objects1.rsp
8_pipeline.exe: CMakeFiles/8_pipeline.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Coding\Coursera\brown_band\Week_3\8_pipeline\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 8_pipeline.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\8_pipeline.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/8_pipeline.dir/build: 8_pipeline.exe

.PHONY : CMakeFiles/8_pipeline.dir/build

CMakeFiles/8_pipeline.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\8_pipeline.dir\cmake_clean.cmake
.PHONY : CMakeFiles/8_pipeline.dir/clean

CMakeFiles/8_pipeline.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Coding\Coursera\brown_band\Week_3\8_pipeline D:\Coding\Coursera\brown_band\Week_3\8_pipeline D:\Coding\Coursera\brown_band\Week_3\8_pipeline\cmake-build-debug D:\Coding\Coursera\brown_band\Week_3\8_pipeline\cmake-build-debug D:\Coding\Coursera\brown_band\Week_3\8_pipeline\cmake-build-debug\CMakeFiles\8_pipeline.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/8_pipeline.dir/depend

