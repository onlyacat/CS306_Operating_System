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
CMAKE_SOURCE_DIR = /home/cat/OS_LAB5/reader-writer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/cat/OS_LAB5/reader-writer

# Include any dependencies generated for this target.
include CMakeFiles/reader_writer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/reader_writer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/reader_writer.dir/flags.make

CMakeFiles/reader_writer.dir/Main_file.c.o: CMakeFiles/reader_writer.dir/flags.make
CMakeFiles/reader_writer.dir/Main_file.c.o: Main_file.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/cat/OS_LAB5/reader-writer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/reader_writer.dir/Main_file.c.o"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/reader_writer.dir/Main_file.c.o   -c /home/cat/OS_LAB5/reader-writer/Main_file.c

CMakeFiles/reader_writer.dir/Main_file.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/reader_writer.dir/Main_file.c.i"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/cat/OS_LAB5/reader-writer/Main_file.c > CMakeFiles/reader_writer.dir/Main_file.c.i

CMakeFiles/reader_writer.dir/Main_file.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/reader_writer.dir/Main_file.c.s"
	/usr/bin/cc  $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/cat/OS_LAB5/reader-writer/Main_file.c -o CMakeFiles/reader_writer.dir/Main_file.c.s

CMakeFiles/reader_writer.dir/Main_file.c.o.requires:

.PHONY : CMakeFiles/reader_writer.dir/Main_file.c.o.requires

CMakeFiles/reader_writer.dir/Main_file.c.o.provides: CMakeFiles/reader_writer.dir/Main_file.c.o.requires
	$(MAKE) -f CMakeFiles/reader_writer.dir/build.make CMakeFiles/reader_writer.dir/Main_file.c.o.provides.build
.PHONY : CMakeFiles/reader_writer.dir/Main_file.c.o.provides

CMakeFiles/reader_writer.dir/Main_file.c.o.provides.build: CMakeFiles/reader_writer.dir/Main_file.c.o


# Object files for target reader_writer
reader_writer_OBJECTS = \
"CMakeFiles/reader_writer.dir/Main_file.c.o"

# External object files for target reader_writer
reader_writer_EXTERNAL_OBJECTS =

reader_writer: CMakeFiles/reader_writer.dir/Main_file.c.o
reader_writer: CMakeFiles/reader_writer.dir/build.make
reader_writer: CMakeFiles/reader_writer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/cat/OS_LAB5/reader-writer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable reader_writer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/reader_writer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/reader_writer.dir/build: reader_writer

.PHONY : CMakeFiles/reader_writer.dir/build

CMakeFiles/reader_writer.dir/requires: CMakeFiles/reader_writer.dir/Main_file.c.o.requires

.PHONY : CMakeFiles/reader_writer.dir/requires

CMakeFiles/reader_writer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/reader_writer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/reader_writer.dir/clean

CMakeFiles/reader_writer.dir/depend:
	cd /home/cat/OS_LAB5/reader-writer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/cat/OS_LAB5/reader-writer /home/cat/OS_LAB5/reader-writer /home/cat/OS_LAB5/reader-writer /home/cat/OS_LAB5/reader-writer /home/cat/OS_LAB5/reader-writer/CMakeFiles/reader_writer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/reader_writer.dir/depend

