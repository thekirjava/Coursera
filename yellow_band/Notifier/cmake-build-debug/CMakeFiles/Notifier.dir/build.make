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
CMAKE_SOURCE_DIR = D:\Coding\yellow_band\Notifier

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Coding\yellow_band\Notifier\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Notifier.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Notifier.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Notifier.dir/flags.make

CMakeFiles/Notifier.dir/main.cpp.obj: CMakeFiles/Notifier.dir/flags.make
CMakeFiles/Notifier.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\yellow_band\Notifier\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Notifier.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\Notifier.dir\main.cpp.obj -c D:\Coding\yellow_band\Notifier\main.cpp

CMakeFiles/Notifier.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Notifier.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\yellow_band\Notifier\main.cpp > CMakeFiles\Notifier.dir\main.cpp.i

CMakeFiles/Notifier.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Notifier.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\yellow_band\Notifier\main.cpp -o CMakeFiles\Notifier.dir\main.cpp.s

# Object files for target Notifier
Notifier_OBJECTS = \
"CMakeFiles/Notifier.dir/main.cpp.obj"

# External object files for target Notifier
Notifier_EXTERNAL_OBJECTS =

Notifier.exe: CMakeFiles/Notifier.dir/main.cpp.obj
Notifier.exe: CMakeFiles/Notifier.dir/build.make
Notifier.exe: CMakeFiles/Notifier.dir/linklibs.rsp
Notifier.exe: CMakeFiles/Notifier.dir/objects1.rsp
Notifier.exe: CMakeFiles/Notifier.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Coding\yellow_band\Notifier\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Notifier.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Notifier.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Notifier.dir/build: Notifier.exe

.PHONY : CMakeFiles/Notifier.dir/build

CMakeFiles/Notifier.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Notifier.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Notifier.dir/clean

CMakeFiles/Notifier.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Coding\yellow_band\Notifier D:\Coding\yellow_band\Notifier D:\Coding\yellow_band\Notifier\cmake-build-debug D:\Coding\yellow_band\Notifier\cmake-build-debug D:\Coding\yellow_band\Notifier\cmake-build-debug\CMakeFiles\Notifier.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Notifier.dir/depend

