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
CMAKE_SOURCE_DIR = D:\Coding\yellow_band\phone_number

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Coding\yellow_band\phone_number\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/phone_number.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/phone_number.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/phone_number.dir/flags.make

CMakeFiles/phone_number.dir/main.cpp.obj: CMakeFiles/phone_number.dir/flags.make
CMakeFiles/phone_number.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\yellow_band\phone_number\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/phone_number.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\phone_number.dir\main.cpp.obj -c D:\Coding\yellow_band\phone_number\main.cpp

CMakeFiles/phone_number.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/phone_number.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\yellow_band\phone_number\main.cpp > CMakeFiles\phone_number.dir\main.cpp.i

CMakeFiles/phone_number.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/phone_number.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\yellow_band\phone_number\main.cpp -o CMakeFiles\phone_number.dir\main.cpp.s

CMakeFiles/phone_number.dir/phone_number.cpp.obj: CMakeFiles/phone_number.dir/flags.make
CMakeFiles/phone_number.dir/phone_number.cpp.obj: ../phone_number.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\yellow_band\phone_number\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/phone_number.dir/phone_number.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\phone_number.dir\phone_number.cpp.obj -c D:\Coding\yellow_band\phone_number\phone_number.cpp

CMakeFiles/phone_number.dir/phone_number.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/phone_number.dir/phone_number.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\yellow_band\phone_number\phone_number.cpp > CMakeFiles\phone_number.dir\phone_number.cpp.i

CMakeFiles/phone_number.dir/phone_number.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/phone_number.dir/phone_number.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\yellow_band\phone_number\phone_number.cpp -o CMakeFiles\phone_number.dir\phone_number.cpp.s

# Object files for target phone_number
phone_number_OBJECTS = \
"CMakeFiles/phone_number.dir/main.cpp.obj" \
"CMakeFiles/phone_number.dir/phone_number.cpp.obj"

# External object files for target phone_number
phone_number_EXTERNAL_OBJECTS =

phone_number.exe: CMakeFiles/phone_number.dir/main.cpp.obj
phone_number.exe: CMakeFiles/phone_number.dir/phone_number.cpp.obj
phone_number.exe: CMakeFiles/phone_number.dir/build.make
phone_number.exe: CMakeFiles/phone_number.dir/linklibs.rsp
phone_number.exe: CMakeFiles/phone_number.dir/objects1.rsp
phone_number.exe: CMakeFiles/phone_number.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Coding\yellow_band\phone_number\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable phone_number.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\phone_number.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/phone_number.dir/build: phone_number.exe

.PHONY : CMakeFiles/phone_number.dir/build

CMakeFiles/phone_number.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\phone_number.dir\cmake_clean.cmake
.PHONY : CMakeFiles/phone_number.dir/clean

CMakeFiles/phone_number.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Coding\yellow_band\phone_number D:\Coding\yellow_band\phone_number D:\Coding\yellow_band\phone_number\cmake-build-debug D:\Coding\yellow_band\phone_number\cmake-build-debug D:\Coding\yellow_band\phone_number\cmake-build-debug\CMakeFiles\phone_number.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/phone_number.dir/depend
