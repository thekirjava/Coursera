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
CMAKE_SOURCE_DIR = D:\Coding\yellow_band\final

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Coding\yellow_band\final\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/final.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/final.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/final.dir/flags.make

CMakeFiles/final.dir/main.cpp.obj: CMakeFiles/final.dir/flags.make
CMakeFiles/final.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\yellow_band\final\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/final.dir/main.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\final.dir\main.cpp.obj -c D:\Coding\yellow_band\final\main.cpp

CMakeFiles/final.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/final.dir/main.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\yellow_band\final\main.cpp > CMakeFiles\final.dir\main.cpp.i

CMakeFiles/final.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/final.dir/main.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\yellow_band\final\main.cpp -o CMakeFiles\final.dir\main.cpp.s

CMakeFiles/final.dir/token.cpp.obj: CMakeFiles/final.dir/flags.make
CMakeFiles/final.dir/token.cpp.obj: ../token.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\yellow_band\final\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/final.dir/token.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\final.dir\token.cpp.obj -c D:\Coding\yellow_band\final\token.cpp

CMakeFiles/final.dir/token.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/final.dir/token.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\yellow_band\final\token.cpp > CMakeFiles\final.dir\token.cpp.i

CMakeFiles/final.dir/token.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/final.dir/token.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\yellow_band\final\token.cpp -o CMakeFiles\final.dir\token.cpp.s

CMakeFiles/final.dir/condition_parser.cpp.obj: CMakeFiles/final.dir/flags.make
CMakeFiles/final.dir/condition_parser.cpp.obj: ../condition_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\yellow_band\final\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/final.dir/condition_parser.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\final.dir\condition_parser.cpp.obj -c D:\Coding\yellow_band\final\condition_parser.cpp

CMakeFiles/final.dir/condition_parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/final.dir/condition_parser.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\yellow_band\final\condition_parser.cpp > CMakeFiles\final.dir\condition_parser.cpp.i

CMakeFiles/final.dir/condition_parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/final.dir/condition_parser.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\yellow_band\final\condition_parser.cpp -o CMakeFiles\final.dir\condition_parser.cpp.s

CMakeFiles/final.dir/condition_parser_test.cpp.obj: CMakeFiles/final.dir/flags.make
CMakeFiles/final.dir/condition_parser_test.cpp.obj: ../condition_parser_test.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\yellow_band\final\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/final.dir/condition_parser_test.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\final.dir\condition_parser_test.cpp.obj -c D:\Coding\yellow_band\final\condition_parser_test.cpp

CMakeFiles/final.dir/condition_parser_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/final.dir/condition_parser_test.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\yellow_band\final\condition_parser_test.cpp > CMakeFiles\final.dir\condition_parser_test.cpp.i

CMakeFiles/final.dir/condition_parser_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/final.dir/condition_parser_test.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\yellow_band\final\condition_parser_test.cpp -o CMakeFiles\final.dir\condition_parser_test.cpp.s

CMakeFiles/final.dir/date.cpp.obj: CMakeFiles/final.dir/flags.make
CMakeFiles/final.dir/date.cpp.obj: ../date.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\yellow_band\final\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/final.dir/date.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\final.dir\date.cpp.obj -c D:\Coding\yellow_band\final\date.cpp

CMakeFiles/final.dir/date.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/final.dir/date.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\yellow_band\final\date.cpp > CMakeFiles\final.dir\date.cpp.i

CMakeFiles/final.dir/date.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/final.dir/date.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\yellow_band\final\date.cpp -o CMakeFiles\final.dir\date.cpp.s

CMakeFiles/final.dir/node.cpp.obj: CMakeFiles/final.dir/flags.make
CMakeFiles/final.dir/node.cpp.obj: ../node.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\yellow_band\final\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/final.dir/node.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\final.dir\node.cpp.obj -c D:\Coding\yellow_band\final\node.cpp

CMakeFiles/final.dir/node.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/final.dir/node.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\yellow_band\final\node.cpp > CMakeFiles\final.dir\node.cpp.i

CMakeFiles/final.dir/node.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/final.dir/node.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\yellow_band\final\node.cpp -o CMakeFiles\final.dir\node.cpp.s

CMakeFiles/final.dir/database.cpp.obj: CMakeFiles/final.dir/flags.make
CMakeFiles/final.dir/database.cpp.obj: ../database.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\yellow_band\final\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/final.dir/database.cpp.obj"
	C:\MinGW\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\final.dir\database.cpp.obj -c D:\Coding\yellow_band\final\database.cpp

CMakeFiles/final.dir/database.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/final.dir/database.cpp.i"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\yellow_band\final\database.cpp > CMakeFiles\final.dir\database.cpp.i

CMakeFiles/final.dir/database.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/final.dir/database.cpp.s"
	C:\MinGW\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\yellow_band\final\database.cpp -o CMakeFiles\final.dir\database.cpp.s

# Object files for target final
final_OBJECTS = \
"CMakeFiles/final.dir/main.cpp.obj" \
"CMakeFiles/final.dir/token.cpp.obj" \
"CMakeFiles/final.dir/condition_parser.cpp.obj" \
"CMakeFiles/final.dir/condition_parser_test.cpp.obj" \
"CMakeFiles/final.dir/date.cpp.obj" \
"CMakeFiles/final.dir/node.cpp.obj" \
"CMakeFiles/final.dir/database.cpp.obj"

# External object files for target final
final_EXTERNAL_OBJECTS =

final.exe: CMakeFiles/final.dir/main.cpp.obj
final.exe: CMakeFiles/final.dir/token.cpp.obj
final.exe: CMakeFiles/final.dir/condition_parser.cpp.obj
final.exe: CMakeFiles/final.dir/condition_parser_test.cpp.obj
final.exe: CMakeFiles/final.dir/date.cpp.obj
final.exe: CMakeFiles/final.dir/node.cpp.obj
final.exe: CMakeFiles/final.dir/database.cpp.obj
final.exe: CMakeFiles/final.dir/build.make
final.exe: CMakeFiles/final.dir/linklibs.rsp
final.exe: CMakeFiles/final.dir/objects1.rsp
final.exe: CMakeFiles/final.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Coding\yellow_band\final\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable final.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\final.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/final.dir/build: final.exe

.PHONY : CMakeFiles/final.dir/build

CMakeFiles/final.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\final.dir\cmake_clean.cmake
.PHONY : CMakeFiles/final.dir/clean

CMakeFiles/final.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Coding\yellow_band\final D:\Coding\yellow_band\final D:\Coding\yellow_band\final\cmake-build-debug D:\Coding\yellow_band\final\cmake-build-debug D:\Coding\yellow_band\final\cmake-build-debug\CMakeFiles\final.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/final.dir/depend
