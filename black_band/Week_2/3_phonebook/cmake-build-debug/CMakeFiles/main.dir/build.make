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
CMAKE_SOURCE_DIR = D:\Coding\Coursera\black_band\Week_2\3_phonebook

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Coding\Coursera\black_band\Week_2\3_phonebook\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

contact.pb.h: ../contact.proto
contact.pb.h: C:/dev/protobuf/bin/protoc.exe
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=D:\Coding\Coursera\black_band\Week_2\3_phonebook\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Running cpp protocol buffer compiler on contact.proto"
	C:\dev\protobuf\bin\protoc.exe --cpp_out D:/Coding/Coursera/black_band/Week_2/3_phonebook/cmake-build-debug -I D:/Coding/Coursera/black_band/Week_2/3_phonebook D:/Coding/Coursera/black_band/Week_2/3_phonebook/contact.proto

contact.pb.cc: contact.pb.h
	@$(CMAKE_COMMAND) -E touch_nocreate contact.pb.cc

CMakeFiles/main.dir/main.cpp.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/main.cpp.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\Coursera\black_band\Week_2\3_phonebook\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/main.cpp.obj"
	C:\dev\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\main.dir\main.cpp.obj -c D:\Coding\Coursera\black_band\Week_2\3_phonebook\main.cpp

CMakeFiles/main.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/main.cpp.i"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\Coursera\black_band\Week_2\3_phonebook\main.cpp > CMakeFiles\main.dir\main.cpp.i

CMakeFiles/main.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/main.cpp.s"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\Coursera\black_band\Week_2\3_phonebook\main.cpp -o CMakeFiles\main.dir\main.cpp.s

CMakeFiles/main.dir/contact.pb.cc.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/contact.pb.cc.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/contact.pb.cc.obj: contact.pb.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=D:\Coding\Coursera\black_band\Week_2\3_phonebook\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/main.dir/contact.pb.cc.obj"
	C:\dev\mingw\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\main.dir\contact.pb.cc.obj -c D:\Coding\Coursera\black_band\Week_2\3_phonebook\cmake-build-debug\contact.pb.cc

CMakeFiles/main.dir/contact.pb.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/contact.pb.cc.i"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Coding\Coursera\black_band\Week_2\3_phonebook\cmake-build-debug\contact.pb.cc > CMakeFiles\main.dir\contact.pb.cc.i

CMakeFiles/main.dir/contact.pb.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/contact.pb.cc.s"
	C:\dev\mingw\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Coding\Coursera\black_band\Week_2\3_phonebook\cmake-build-debug\contact.pb.cc -o CMakeFiles\main.dir\contact.pb.cc.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/main.cpp.obj" \
"CMakeFiles/main.dir/contact.pb.cc.obj"

# External object files for target main
main_EXTERNAL_OBJECTS =

main.exe: CMakeFiles/main.dir/main.cpp.obj
main.exe: CMakeFiles/main.dir/contact.pb.cc.obj
main.exe: CMakeFiles/main.dir/build.make
main.exe: C:/dev/protobuf/lib/libprotobuf.a
main.exe: CMakeFiles/main.dir/linklibs.rsp
main.exe: CMakeFiles/main.dir/objects1.rsp
main.exe: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=D:\Coding\Coursera\black_band\Week_2\3_phonebook\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable main.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\main.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: main.exe

.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\main.dir\cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend: contact.pb.h
CMakeFiles/main.dir/depend: contact.pb.cc
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Coding\Coursera\black_band\Week_2\3_phonebook D:\Coding\Coursera\black_band\Week_2\3_phonebook D:\Coding\Coursera\black_band\Week_2\3_phonebook\cmake-build-debug D:\Coding\Coursera\black_band\Week_2\3_phonebook\cmake-build-debug D:\Coding\Coursera\black_band\Week_2\3_phonebook\cmake-build-debug\CMakeFiles\main.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend
