# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/rafa/Escritorio/UCO/Tercero/FSIV/Practicas/fsiv_tutorial_opencv

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/rafa/Escritorio/UCO/Tercero/FSIV/Practicas/fsiv_tutorial_opencv/build

# Include any dependencies generated for this target.
include CMakeFiles/show_video.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/show_video.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/show_video.dir/flags.make

CMakeFiles/show_video.dir/show_video.cc.o: CMakeFiles/show_video.dir/flags.make
CMakeFiles/show_video.dir/show_video.cc.o: ../show_video.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/rafa/Escritorio/UCO/Tercero/FSIV/Practicas/fsiv_tutorial_opencv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/show_video.dir/show_video.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/show_video.dir/show_video.cc.o -c /home/rafa/Escritorio/UCO/Tercero/FSIV/Practicas/fsiv_tutorial_opencv/show_video.cc

CMakeFiles/show_video.dir/show_video.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/show_video.dir/show_video.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/rafa/Escritorio/UCO/Tercero/FSIV/Practicas/fsiv_tutorial_opencv/show_video.cc > CMakeFiles/show_video.dir/show_video.cc.i

CMakeFiles/show_video.dir/show_video.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/show_video.dir/show_video.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/rafa/Escritorio/UCO/Tercero/FSIV/Practicas/fsiv_tutorial_opencv/show_video.cc -o CMakeFiles/show_video.dir/show_video.cc.s

CMakeFiles/show_video.dir/show_video.cc.o.requires:

.PHONY : CMakeFiles/show_video.dir/show_video.cc.o.requires

CMakeFiles/show_video.dir/show_video.cc.o.provides: CMakeFiles/show_video.dir/show_video.cc.o.requires
	$(MAKE) -f CMakeFiles/show_video.dir/build.make CMakeFiles/show_video.dir/show_video.cc.o.provides.build
.PHONY : CMakeFiles/show_video.dir/show_video.cc.o.provides

CMakeFiles/show_video.dir/show_video.cc.o.provides.build: CMakeFiles/show_video.dir/show_video.cc.o


# Object files for target show_video
show_video_OBJECTS = \
"CMakeFiles/show_video.dir/show_video.cc.o"

# External object files for target show_video
show_video_EXTERNAL_OBJECTS =

show_video: CMakeFiles/show_video.dir/show_video.cc.o
show_video: CMakeFiles/show_video.dir/build.make
show_video: /usr/lib/x86_64-linux-gnu/libopencv_shape.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_stitching.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_superres.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_videostab.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_aruco.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_bgsegm.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_bioinspired.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_ccalib.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_datasets.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_dpm.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_face.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_freetype.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_fuzzy.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_hdf.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_line_descriptor.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_optflow.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_plot.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_reg.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_saliency.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_stereo.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_structured_light.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_surface_matching.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_text.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_ximgproc.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_xobjdetect.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_xphoto.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_video.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_viz.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_phase_unwrapping.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_rgbd.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_features2d.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_flann.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_ml.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_highgui.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_photo.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_videoio.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_imgcodecs.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.3.2.0
show_video: /usr/lib/x86_64-linux-gnu/libopencv_core.so.3.2.0
show_video: CMakeFiles/show_video.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/rafa/Escritorio/UCO/Tercero/FSIV/Practicas/fsiv_tutorial_opencv/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable show_video"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/show_video.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/show_video.dir/build: show_video

.PHONY : CMakeFiles/show_video.dir/build

CMakeFiles/show_video.dir/requires: CMakeFiles/show_video.dir/show_video.cc.o.requires

.PHONY : CMakeFiles/show_video.dir/requires

CMakeFiles/show_video.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/show_video.dir/cmake_clean.cmake
.PHONY : CMakeFiles/show_video.dir/clean

CMakeFiles/show_video.dir/depend:
	cd /home/rafa/Escritorio/UCO/Tercero/FSIV/Practicas/fsiv_tutorial_opencv/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/rafa/Escritorio/UCO/Tercero/FSIV/Practicas/fsiv_tutorial_opencv /home/rafa/Escritorio/UCO/Tercero/FSIV/Practicas/fsiv_tutorial_opencv /home/rafa/Escritorio/UCO/Tercero/FSIV/Practicas/fsiv_tutorial_opencv/build /home/rafa/Escritorio/UCO/Tercero/FSIV/Practicas/fsiv_tutorial_opencv/build /home/rafa/Escritorio/UCO/Tercero/FSIV/Practicas/fsiv_tutorial_opencv/build/CMakeFiles/show_video.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/show_video.dir/depend
