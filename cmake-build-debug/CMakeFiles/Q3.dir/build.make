# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.26

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

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.2.2\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.2.2\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\tomer\CLionProjects\b3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\tomer\CLionProjects\b3\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Q3.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Q3.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Q3.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Q3.dir/flags.make

CMakeFiles/Q3.dir/main2.cpp.obj: CMakeFiles/Q3.dir/flags.make
CMakeFiles/Q3.dir/main2.cpp.obj: C:/Users/tomer/CLionProjects/b3/main2.cpp
CMakeFiles/Q3.dir/main2.cpp.obj: CMakeFiles/Q3.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\tomer\CLionProjects\b3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Q3.dir/main2.cpp.obj"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Q3.dir/main2.cpp.obj -MF CMakeFiles\Q3.dir\main2.cpp.obj.d -o CMakeFiles\Q3.dir\main2.cpp.obj -c C:\Users\tomer\CLionProjects\b3\main2.cpp

CMakeFiles/Q3.dir/main2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Q3.dir/main2.cpp.i"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\tomer\CLionProjects\b3\main2.cpp > CMakeFiles\Q3.dir\main2.cpp.i

CMakeFiles/Q3.dir/main2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Q3.dir/main2.cpp.s"
	C:\MinGW\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\tomer\CLionProjects\b3\main2.cpp -o CMakeFiles\Q3.dir\main2.cpp.s

# Object files for target Q3
Q3_OBJECTS = \
"CMakeFiles/Q3.dir/main2.cpp.obj"

# External object files for target Q3
Q3_EXTERNAL_OBJECTS =

Q3.exe: CMakeFiles/Q3.dir/main2.cpp.obj
Q3.exe: CMakeFiles/Q3.dir/build.make
Q3.exe: CMakeFiles/Q3.dir/linkLibs.rsp
Q3.exe: CMakeFiles/Q3.dir/objects1.rsp
Q3.exe: CMakeFiles/Q3.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\tomer\CLionProjects\b3\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Q3.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Q3.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Q3.dir/build: Q3.exe
.PHONY : CMakeFiles/Q3.dir/build

CMakeFiles/Q3.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Q3.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Q3.dir/clean

CMakeFiles/Q3.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\tomer\CLionProjects\b3 C:\Users\tomer\CLionProjects\b3 C:\Users\tomer\CLionProjects\b3\cmake-build-debug C:\Users\tomer\CLionProjects\b3\cmake-build-debug C:\Users\tomer\CLionProjects\b3\cmake-build-debug\CMakeFiles\Q3.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Q3.dir/depend

