# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gwy/Documents/webml/webml-wasm/ml/nn

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gwy/Documents/webml/webml-wasm/ml/nn/build

# Utility rule file for nn_ops_test.

# Include the progress variables for this target.
include CMakeFiles/nn_ops_test.dir/progress.make

CMakeFiles/nn_ops_test: nn_ops.js
CMakeFiles/nn_ops_test: ../bind/test/operations.js
CMakeFiles/nn_ops_test: operations.js
CMakeFiles/nn_ops_test: ../bind/test/index.html
CMakeFiles/nn_ops_test: index.html


operations.js: ../bind/test/operations.js
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/gwy/Documents/webml/webml-wasm/ml/nn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Copying operations.js"
	/usr/bin/cmake -E copy_if_different /home/gwy/Documents/webml/webml-wasm/ml/nn/bind/test/operations.js /home/gwy/Documents/webml/webml-wasm/ml/nn/build/operations.js

index.html: ../bind/test/index.html
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/gwy/Documents/webml/webml-wasm/ml/nn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Copying index.html"
	/usr/bin/cmake -E copy_if_different /home/gwy/Documents/webml/webml-wasm/ml/nn/bind/test/index.html /home/gwy/Documents/webml/webml-wasm/ml/nn/build/index.html

nn_ops_test: CMakeFiles/nn_ops_test
nn_ops_test: operations.js
nn_ops_test: index.html
nn_ops_test: CMakeFiles/nn_ops_test.dir/build.make

.PHONY : nn_ops_test

# Rule to build all files generated by this target.
CMakeFiles/nn_ops_test.dir/build: nn_ops_test

.PHONY : CMakeFiles/nn_ops_test.dir/build

CMakeFiles/nn_ops_test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/nn_ops_test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/nn_ops_test.dir/clean

CMakeFiles/nn_ops_test.dir/depend:
	cd /home/gwy/Documents/webml/webml-wasm/ml/nn/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gwy/Documents/webml/webml-wasm/ml/nn /home/gwy/Documents/webml/webml-wasm/ml/nn /home/gwy/Documents/webml/webml-wasm/ml/nn/build /home/gwy/Documents/webml/webml-wasm/ml/nn/build /home/gwy/Documents/webml/webml-wasm/ml/nn/build/CMakeFiles/nn_ops_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/nn_ops_test.dir/depend

