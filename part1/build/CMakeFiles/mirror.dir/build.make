# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/rt/Desktop/IC_LabWork2/part1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rt/Desktop/IC_LabWork2/part1/build

# Include any dependencies generated for this target.
include CMakeFiles/mirror.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/mirror.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/mirror.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mirror.dir/flags.make

CMakeFiles/mirror.dir/mirror.cpp.o: CMakeFiles/mirror.dir/flags.make
CMakeFiles/mirror.dir/mirror.cpp.o: /home/rt/Desktop/IC_LabWork2/part1/mirror.cpp
CMakeFiles/mirror.dir/mirror.cpp.o: CMakeFiles/mirror.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rt/Desktop/IC_LabWork2/part1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mirror.dir/mirror.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/mirror.dir/mirror.cpp.o -MF CMakeFiles/mirror.dir/mirror.cpp.o.d -o CMakeFiles/mirror.dir/mirror.cpp.o -c /home/rt/Desktop/IC_LabWork2/part1/mirror.cpp

CMakeFiles/mirror.dir/mirror.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mirror.dir/mirror.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rt/Desktop/IC_LabWork2/part1/mirror.cpp > CMakeFiles/mirror.dir/mirror.cpp.i

CMakeFiles/mirror.dir/mirror.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mirror.dir/mirror.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rt/Desktop/IC_LabWork2/part1/mirror.cpp -o CMakeFiles/mirror.dir/mirror.cpp.s

# Object files for target mirror
mirror_OBJECTS = \
"CMakeFiles/mirror.dir/mirror.cpp.o"

# External object files for target mirror
mirror_EXTERNAL_OBJECTS =

/home/rt/Desktop/IC_LabWork2/part1/part1-bin/mirror: CMakeFiles/mirror.dir/mirror.cpp.o
/home/rt/Desktop/IC_LabWork2/part1/part1-bin/mirror: CMakeFiles/mirror.dir/build.make
/home/rt/Desktop/IC_LabWork2/part1/part1-bin/mirror: /usr/local/lib/libopencv_gapi.so.4.6.0
/home/rt/Desktop/IC_LabWork2/part1/part1-bin/mirror: /usr/local/lib/libopencv_highgui.so.4.6.0
/home/rt/Desktop/IC_LabWork2/part1/part1-bin/mirror: /usr/local/lib/libopencv_ml.so.4.6.0
/home/rt/Desktop/IC_LabWork2/part1/part1-bin/mirror: /usr/local/lib/libopencv_objdetect.so.4.6.0
/home/rt/Desktop/IC_LabWork2/part1/part1-bin/mirror: /usr/local/lib/libopencv_photo.so.4.6.0
/home/rt/Desktop/IC_LabWork2/part1/part1-bin/mirror: /usr/local/lib/libopencv_stitching.so.4.6.0
/home/rt/Desktop/IC_LabWork2/part1/part1-bin/mirror: /usr/local/lib/libopencv_video.so.4.6.0
/home/rt/Desktop/IC_LabWork2/part1/part1-bin/mirror: /usr/local/lib/libopencv_videoio.so.4.6.0
/home/rt/Desktop/IC_LabWork2/part1/part1-bin/mirror: /usr/local/lib/libopencv_imgcodecs.so.4.6.0
/home/rt/Desktop/IC_LabWork2/part1/part1-bin/mirror: /usr/local/lib/libopencv_dnn.so.4.6.0
/home/rt/Desktop/IC_LabWork2/part1/part1-bin/mirror: /usr/local/lib/libopencv_calib3d.so.4.6.0
/home/rt/Desktop/IC_LabWork2/part1/part1-bin/mirror: /usr/local/lib/libopencv_features2d.so.4.6.0
/home/rt/Desktop/IC_LabWork2/part1/part1-bin/mirror: /usr/local/lib/libopencv_flann.so.4.6.0
/home/rt/Desktop/IC_LabWork2/part1/part1-bin/mirror: /usr/local/lib/libopencv_imgproc.so.4.6.0
/home/rt/Desktop/IC_LabWork2/part1/part1-bin/mirror: /usr/local/lib/libopencv_core.so.4.6.0
/home/rt/Desktop/IC_LabWork2/part1/part1-bin/mirror: CMakeFiles/mirror.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rt/Desktop/IC_LabWork2/part1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/rt/Desktop/IC_LabWork2/part1/part1-bin/mirror"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mirror.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mirror.dir/build: /home/rt/Desktop/IC_LabWork2/part1/part1-bin/mirror
.PHONY : CMakeFiles/mirror.dir/build

CMakeFiles/mirror.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mirror.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mirror.dir/clean

CMakeFiles/mirror.dir/depend:
	cd /home/rt/Desktop/IC_LabWork2/part1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rt/Desktop/IC_LabWork2/part1 /home/rt/Desktop/IC_LabWork2/part1 /home/rt/Desktop/IC_LabWork2/part1/build /home/rt/Desktop/IC_LabWork2/part1/build /home/rt/Desktop/IC_LabWork2/part1/build/CMakeFiles/mirror.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mirror.dir/depend

