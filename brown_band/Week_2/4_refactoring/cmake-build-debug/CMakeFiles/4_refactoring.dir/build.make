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
CMAKE_SOURCE_DIR = D:\Coding\Coursera\brown_band\Week_2\4_refactoring

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Coding\Coursera\brown_band\Week_2\4_refactoring\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/4_refactoring.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/4_refactoring.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/4_refactoring.dir/flags.make

CMakeFiles/4_refactoring.dir/main.cpp.obj: CMakeFiles/4_refactoring.dir/flags.make
CMakeFiles/4_refactoring.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\Coursera\brown_band\Week_2\4_refactoring\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/4_refactoring.dir/main.cpp.obj"
	C:\dev\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\4_refactoring.dir\main.cpp.obj -c D:\Coding\Coursera\brown_band\Week_2\4_refactoring\main.cpp

CMakeFiles/4_refactoring.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/4_refactoring.dir/main.cpp.i"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\Coursera\brown_band\Week_2\4_refactoring\main.cpp > CMakeFiles\4_refactoring.dir\main.cpp.i

CMakeFiles/4_refactoring.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/4_refactoring.dir/main.cpp.s"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\Coursera\brown_band\Week_2\4_refactoring\main.cpp -o CMakeFiles\4_refactoring.dir\main.cpp.s

CMakeFiles/4_refactoring.dir/json.cpp.obj: CMakeFiles/4_refactoring.dir/flags.make
CMakeFiles/4_refactoring.dir/json.cpp.obj: ../json.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\Coursera\brown_band\Week_2\4_refactoring\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/4_refactoring.dir/json.cpp.obj"
	C:\dev\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\4_refactoring.dir\json.cpp.obj -c D:\Coding\Coursera\brown_band\Week_2\4_refactoring\json.cpp

CMakeFiles/4_refactoring.dir/json.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/4_refactoring.dir/json.cpp.i"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\Coursera\brown_band\Week_2\4_refactoring\json.cpp > CMakeFiles\4_refactoring.dir\json.cpp.i

CMakeFiles/4_refactoring.dir/json.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/4_refactoring.dir/json.cpp.s"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\Coursera\brown_band\Week_2\4_refactoring\json.cpp -o CMakeFiles\4_refactoring.dir\json.cpp.s

CMakeFiles/4_refactoring.dir/xml.cpp.obj: CMakeFiles/4_refactoring.dir/flags.make
CMakeFiles/4_refactoring.dir/xml.cpp.obj: ../xml.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\Coursera\brown_band\Week_2\4_refactoring\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/4_refactoring.dir/xml.cpp.obj"
	C:\dev\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\4_refactoring.dir\xml.cpp.obj -c D:\Coding\Coursera\brown_band\Week_2\4_refactoring\xml.cpp

CMakeFiles/4_refactoring.dir/xml.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/4_refactoring.dir/xml.cpp.i"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\Coursera\brown_band\Week_2\4_refactoring\xml.cpp > CMakeFiles\4_refactoring.dir\xml.cpp.i

CMakeFiles/4_refactoring.dir/xml.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/4_refactoring.dir/xml.cpp.s"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\Coursera\brown_band\Week_2\4_refactoring\xml.cpp -o CMakeFiles\4_refactoring.dir\xml.cpp.s

# Object files for target 4_refactoring
4_refactoring_OBJECTS = \
"CMakeFiles/4_refactoring.dir/main.cpp.obj" \
"CMakeFiles/4_refactoring.dir/json.cpp.obj" \
"CMakeFiles/4_refactoring.dir/xml.cpp.obj"

# External object files for target 4_refactoring
4_refactoring_EXTERNAL_OBJECTS =

4_refactoring.exe: CMakeFiles/4_refactoring.dir/main.cpp.obj
4_refactoring.exe: CMakeFiles/4_refactoring.dir/json.cpp.obj
4_refactoring.exe: CMakeFiles/4_refactoring.dir/xml.cpp.obj
4_refactoring.exe: CMakeFiles/4_refactoring.dir/build.make
4_refactoring.exe: CMakeFiles/4_refactoring.dir/linklibs.rsp
4_refactoring.exe: CMakeFiles/4_refactoring.dir/objects1.rsp
4_refactoring.exe: CMakeFiles/4_refactoring.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Coding\Coursera\brown_band\Week_2\4_refactoring\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable 4_refactoring.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\4_refactoring.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/4_refactoring.dir/build: 4_refactoring.exe

.PHONY : CMakeFiles/4_refactoring.dir/build

CMakeFiles/4_refactoring.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\4_refactoring.dir\cmake_clean.cmake
.PHONY : CMakeFiles/4_refactoring.dir/clean

CMakeFiles/4_refactoring.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Coding\Coursera\brown_band\Week_2\4_refactoring D:\Coding\Coursera\brown_band\Week_2\4_refactoring D:\Coding\Coursera\brown_band\Week_2\4_refactoring\cmake-build-debug D:\Coding\Coursera\brown_band\Week_2\4_refactoring\cmake-build-debug D:\Coding\Coursera\brown_band\Week_2\4_refactoring\cmake-build-debug\CMakeFiles\4_refactoring.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/4_refactoring.dir/depend

