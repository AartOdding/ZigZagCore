# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.16.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.16.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/aart/Documents/libsigcplusplus-3.0.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/aart/Documents/libsigcplusplus-3.0.0/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/test_slot.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/test_slot.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/test_slot.dir/flags.make

tests/CMakeFiles/test_slot.dir/test_slot.cc.o: tests/CMakeFiles/test_slot.dir/flags.make
tests/CMakeFiles/test_slot.dir/test_slot.cc.o: ../tests/test_slot.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aart/Documents/libsigcplusplus-3.0.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/test_slot.dir/test_slot.cc.o"
	cd /Users/aart/Documents/libsigcplusplus-3.0.0/build/tests && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_slot.dir/test_slot.cc.o -c /Users/aart/Documents/libsigcplusplus-3.0.0/tests/test_slot.cc

tests/CMakeFiles/test_slot.dir/test_slot.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_slot.dir/test_slot.cc.i"
	cd /Users/aart/Documents/libsigcplusplus-3.0.0/build/tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/aart/Documents/libsigcplusplus-3.0.0/tests/test_slot.cc > CMakeFiles/test_slot.dir/test_slot.cc.i

tests/CMakeFiles/test_slot.dir/test_slot.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_slot.dir/test_slot.cc.s"
	cd /Users/aart/Documents/libsigcplusplus-3.0.0/build/tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/aart/Documents/libsigcplusplus-3.0.0/tests/test_slot.cc -o CMakeFiles/test_slot.dir/test_slot.cc.s

tests/CMakeFiles/test_slot.dir/testutilities.cc.o: tests/CMakeFiles/test_slot.dir/flags.make
tests/CMakeFiles/test_slot.dir/testutilities.cc.o: ../tests/testutilities.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/aart/Documents/libsigcplusplus-3.0.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object tests/CMakeFiles/test_slot.dir/testutilities.cc.o"
	cd /Users/aart/Documents/libsigcplusplus-3.0.0/build/tests && /Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_slot.dir/testutilities.cc.o -c /Users/aart/Documents/libsigcplusplus-3.0.0/tests/testutilities.cc

tests/CMakeFiles/test_slot.dir/testutilities.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_slot.dir/testutilities.cc.i"
	cd /Users/aart/Documents/libsigcplusplus-3.0.0/build/tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/aart/Documents/libsigcplusplus-3.0.0/tests/testutilities.cc > CMakeFiles/test_slot.dir/testutilities.cc.i

tests/CMakeFiles/test_slot.dir/testutilities.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_slot.dir/testutilities.cc.s"
	cd /Users/aart/Documents/libsigcplusplus-3.0.0/build/tests && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/aart/Documents/libsigcplusplus-3.0.0/tests/testutilities.cc -o CMakeFiles/test_slot.dir/testutilities.cc.s

# Object files for target test_slot
test_slot_OBJECTS = \
"CMakeFiles/test_slot.dir/test_slot.cc.o" \
"CMakeFiles/test_slot.dir/testutilities.cc.o"

# External object files for target test_slot
test_slot_EXTERNAL_OBJECTS =

tests/test_slot: tests/CMakeFiles/test_slot.dir/test_slot.cc.o
tests/test_slot: tests/CMakeFiles/test_slot.dir/testutilities.cc.o
tests/test_slot: tests/CMakeFiles/test_slot.dir/build.make
tests/test_slot: sigc++/libsigc-3.0.2.99.1.dylib
tests/test_slot: tests/CMakeFiles/test_slot.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/aart/Documents/libsigcplusplus-3.0.0/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test_slot"
	cd /Users/aart/Documents/libsigcplusplus-3.0.0/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_slot.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/test_slot.dir/build: tests/test_slot

.PHONY : tests/CMakeFiles/test_slot.dir/build

tests/CMakeFiles/test_slot.dir/clean:
	cd /Users/aart/Documents/libsigcplusplus-3.0.0/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/test_slot.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/test_slot.dir/clean

tests/CMakeFiles/test_slot.dir/depend:
	cd /Users/aart/Documents/libsigcplusplus-3.0.0/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/aart/Documents/libsigcplusplus-3.0.0 /Users/aart/Documents/libsigcplusplus-3.0.0/tests /Users/aart/Documents/libsigcplusplus-3.0.0/build /Users/aart/Documents/libsigcplusplus-3.0.0/build/tests /Users/aart/Documents/libsigcplusplus-3.0.0/build/tests/CMakeFiles/test_slot.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/test_slot.dir/depend

