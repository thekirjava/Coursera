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
CMAKE_SOURCE_DIR = D:\Coding\Coursera\brown_band\Week_5\9_personal_budget_home_desktop

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Coding\Coursera\brown_band\Week_5\9_personal_budget_home_desktop\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/9_personal_budget_home_desktop.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/9_personal_budget_home_desktop.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/9_personal_budget_home_desktop.dir/flags.make

CMakeFiles/9_personal_budget_home_desktop.dir/main.cpp.obj: CMakeFiles/9_personal_budget_home_desktop.dir/flags.make
CMakeFiles/9_personal_budget_home_desktop.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\Coursera\brown_band\Week_5\9_personal_budget_home_desktop\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/9_personal_budget_home_desktop.dir/main.cpp.obj"
	C:\dev\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\9_personal_budget_home_desktop.dir\main.cpp.obj -c D:\Coding\Coursera\brown_band\Week_5\9_personal_budget_home_desktop\main.cpp

CMakeFiles/9_personal_budget_home_desktop.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/9_personal_budget_home_desktop.dir/main.cpp.i"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\Coursera\brown_band\Week_5\9_personal_budget_home_desktop\main.cpp > CMakeFiles\9_personal_budget_home_desktop.dir\main.cpp.i

CMakeFiles/9_personal_budget_home_desktop.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/9_personal_budget_home_desktop.dir/main.cpp.s"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\Coursera\brown_band\Week_5\9_personal_budget_home_desktop\main.cpp -o CMakeFiles\9_personal_budget_home_desktop.dir\main.cpp.s

# Object files for target 9_personal_budget_home_desktop
9_personal_budget_home_desktop_OBJECTS = \
"CMakeFiles/9_personal_budget_home_desktop.dir/main.cpp.obj"

# External object files for target 9_personal_budget_home_desktop
9_personal_budget_home_desktop_EXTERNAL_OBJECTS =

9_personal_budget_home_desktop.exe: CMakeFiles/9_personal_budget_home_desktop.dir/main.cpp.obj
9_personal_budget_home_desktop.exe: CMakeFiles/9_personal_budget_home_desktop.dir/build.make
9_personal_budget_home_desktop.exe: CMakeFiles/9_personal_budget_home_desktop.dir/linklibs.rsp
9_personal_budget_home_desktop.exe: CMakeFiles/9_personal_budget_home_desktop.dir/objects1.rsp
9_personal_budget_home_desktop.exe: CMakeFiles/9_personal_budget_home_desktop.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Coding\Coursera\brown_band\Week_5\9_personal_budget_home_desktop\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable 9_personal_budget_home_desktop.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\9_personal_budget_home_desktop.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/9_personal_budget_home_desktop.dir/build: 9_personal_budget_home_desktop.exe

.PHONY : CMakeFiles/9_personal_budget_home_desktop.dir/build

CMakeFiles/9_personal_budget_home_desktop.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\9_personal_budget_home_desktop.dir\cmake_clean.cmake
.PHONY : CMakeFiles/9_personal_budget_home_desktop.dir/clean

CMakeFiles/9_personal_budget_home_desktop.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Coding\Coursera\brown_band\Week_5\9_personal_budget_home_desktop D:\Coding\Coursera\brown_band\Week_5\9_personal_budget_home_desktop D:\Coding\Coursera\brown_band\Week_5\9_personal_budget_home_desktop\cmake-build-debug D:\Coding\Coursera\brown_band\Week_5\9_personal_budget_home_desktop\cmake-build-debug D:\Coding\Coursera\brown_band\Week_5\9_personal_budget_home_desktop\cmake-build-debug\CMakeFiles\9_personal_budget_home_desktop.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/9_personal_budget_home_desktop.dir/depend

