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
CMAKE_SOURCE_DIR = D:\Coding\Coursera\red_band\search_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Coding\Coursera\red_band\search_server\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/search_server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/search_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/search_server.dir/flags.make

CMakeFiles/search_server.dir/main.cpp.obj: CMakeFiles/search_server.dir/flags.make
CMakeFiles/search_server.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\Coursera\red_band\search_server\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/search_server.dir/main.cpp.obj"
	C:\dev\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\search_server.dir\main.cpp.obj -c D:\Coding\Coursera\red_band\search_server\main.cpp

CMakeFiles/search_server.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search_server.dir/main.cpp.i"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\Coursera\red_band\search_server\main.cpp > CMakeFiles\search_server.dir\main.cpp.i

CMakeFiles/search_server.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search_server.dir/main.cpp.s"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\Coursera\red_band\search_server\main.cpp -o CMakeFiles\search_server.dir\main.cpp.s

CMakeFiles/search_server.dir/parse.cpp.obj: CMakeFiles/search_server.dir/flags.make
CMakeFiles/search_server.dir/parse.cpp.obj: ../parse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\Coursera\red_band\search_server\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/search_server.dir/parse.cpp.obj"
	C:\dev\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\search_server.dir\parse.cpp.obj -c D:\Coding\Coursera\red_band\search_server\parse.cpp

CMakeFiles/search_server.dir/parse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search_server.dir/parse.cpp.i"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\Coursera\red_band\search_server\parse.cpp > CMakeFiles\search_server.dir\parse.cpp.i

CMakeFiles/search_server.dir/parse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search_server.dir/parse.cpp.s"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\Coursera\red_band\search_server\parse.cpp -o CMakeFiles\search_server.dir\parse.cpp.s

CMakeFiles/search_server.dir/search_server.cpp.obj: CMakeFiles/search_server.dir/flags.make
CMakeFiles/search_server.dir/search_server.cpp.obj: ../search_server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\Coursera\red_band\search_server\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/search_server.dir/search_server.cpp.obj"
	C:\dev\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\search_server.dir\search_server.cpp.obj -c D:\Coding\Coursera\red_band\search_server\search_server.cpp

CMakeFiles/search_server.dir/search_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/search_server.dir/search_server.cpp.i"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\Coursera\red_band\search_server\search_server.cpp > CMakeFiles\search_server.dir\search_server.cpp.i

CMakeFiles/search_server.dir/search_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/search_server.dir/search_server.cpp.s"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\Coursera\red_band\search_server\search_server.cpp -o CMakeFiles\search_server.dir\search_server.cpp.s

# Object files for target search_server
search_server_OBJECTS = \
"CMakeFiles/search_server.dir/main.cpp.obj" \
"CMakeFiles/search_server.dir/parse.cpp.obj" \
"CMakeFiles/search_server.dir/search_server.cpp.obj"

# External object files for target search_server
search_server_EXTERNAL_OBJECTS =

search_server.exe: CMakeFiles/search_server.dir/main.cpp.obj
search_server.exe: CMakeFiles/search_server.dir/parse.cpp.obj
search_server.exe: CMakeFiles/search_server.dir/search_server.cpp.obj
search_server.exe: CMakeFiles/search_server.dir/build.make
search_server.exe: CMakeFiles/search_server.dir/linklibs.rsp
search_server.exe: CMakeFiles/search_server.dir/objects1.rsp
search_server.exe: CMakeFiles/search_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Coding\Coursera\red_band\search_server\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable search_server.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\search_server.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/search_server.dir/build: search_server.exe

.PHONY : CMakeFiles/search_server.dir/build

CMakeFiles/search_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\search_server.dir\cmake_clean.cmake
.PHONY : CMakeFiles/search_server.dir/clean

CMakeFiles/search_server.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Coding\Coursera\red_band\search_server D:\Coding\Coursera\red_band\search_server D:\Coding\Coursera\red_band\search_server\cmake-build-debug D:\Coding\Coursera\red_band\search_server\cmake-build-debug D:\Coding\Coursera\red_band\search_server\cmake-build-debug\CMakeFiles\search_server.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/search_server.dir/depend
