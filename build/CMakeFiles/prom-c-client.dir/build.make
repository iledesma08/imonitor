# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/build

# Include any dependencies generated for this target.
include CMakeFiles/prom-c-client.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/prom-c-client.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/prom-c-client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/prom-c-client.dir/flags.make

CMakeFiles/prom-c-client.dir/src/expose_metrics.c.o: CMakeFiles/prom-c-client.dir/flags.make
CMakeFiles/prom-c-client.dir/src/expose_metrics.c.o: /home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/src/expose_metrics.c
CMakeFiles/prom-c-client.dir/src/expose_metrics.c.o: CMakeFiles/prom-c-client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/prom-c-client.dir/src/expose_metrics.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/prom-c-client.dir/src/expose_metrics.c.o -MF CMakeFiles/prom-c-client.dir/src/expose_metrics.c.o.d -o CMakeFiles/prom-c-client.dir/src/expose_metrics.c.o -c /home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/src/expose_metrics.c

CMakeFiles/prom-c-client.dir/src/expose_metrics.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/prom-c-client.dir/src/expose_metrics.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/src/expose_metrics.c > CMakeFiles/prom-c-client.dir/src/expose_metrics.c.i

CMakeFiles/prom-c-client.dir/src/expose_metrics.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/prom-c-client.dir/src/expose_metrics.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/src/expose_metrics.c -o CMakeFiles/prom-c-client.dir/src/expose_metrics.c.s

CMakeFiles/prom-c-client.dir/src/main.c.o: CMakeFiles/prom-c-client.dir/flags.make
CMakeFiles/prom-c-client.dir/src/main.c.o: /home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/src/main.c
CMakeFiles/prom-c-client.dir/src/main.c.o: CMakeFiles/prom-c-client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/prom-c-client.dir/src/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/prom-c-client.dir/src/main.c.o -MF CMakeFiles/prom-c-client.dir/src/main.c.o.d -o CMakeFiles/prom-c-client.dir/src/main.c.o -c /home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/src/main.c

CMakeFiles/prom-c-client.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/prom-c-client.dir/src/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/src/main.c > CMakeFiles/prom-c-client.dir/src/main.c.i

CMakeFiles/prom-c-client.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/prom-c-client.dir/src/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/src/main.c -o CMakeFiles/prom-c-client.dir/src/main.c.s

CMakeFiles/prom-c-client.dir/src/metrics.c.o: CMakeFiles/prom-c-client.dir/flags.make
CMakeFiles/prom-c-client.dir/src/metrics.c.o: /home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/src/metrics.c
CMakeFiles/prom-c-client.dir/src/metrics.c.o: CMakeFiles/prom-c-client.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/prom-c-client.dir/src/metrics.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/prom-c-client.dir/src/metrics.c.o -MF CMakeFiles/prom-c-client.dir/src/metrics.c.o.d -o CMakeFiles/prom-c-client.dir/src/metrics.c.o -c /home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/src/metrics.c

CMakeFiles/prom-c-client.dir/src/metrics.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/prom-c-client.dir/src/metrics.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/src/metrics.c > CMakeFiles/prom-c-client.dir/src/metrics.c.i

CMakeFiles/prom-c-client.dir/src/metrics.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/prom-c-client.dir/src/metrics.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/src/metrics.c -o CMakeFiles/prom-c-client.dir/src/metrics.c.s

# Object files for target prom-c-client
prom__c__client_OBJECTS = \
"CMakeFiles/prom-c-client.dir/src/expose_metrics.c.o" \
"CMakeFiles/prom-c-client.dir/src/main.c.o" \
"CMakeFiles/prom-c-client.dir/src/metrics.c.o"

# External object files for target prom-c-client
prom__c__client_EXTERNAL_OBJECTS =

prom-c-client: CMakeFiles/prom-c-client.dir/src/expose_metrics.c.o
prom-c-client: CMakeFiles/prom-c-client.dir/src/main.c.o
prom-c-client: CMakeFiles/prom-c-client.dir/src/metrics.c.o
prom-c-client: CMakeFiles/prom-c-client.dir/build.make
prom-c-client: /usr/local/lib/libprom.so
prom-c-client: /usr/local/lib/libpromhttp.so
prom-c-client: /usr/lib/x86_64-linux-gnu/libmicrohttpd.so
prom-c-client: CMakeFiles/prom-c-client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable prom-c-client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/prom-c-client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/prom-c-client.dir/build: prom-c-client
.PHONY : CMakeFiles/prom-c-client.dir/build

CMakeFiles/prom-c-client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/prom-c-client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/prom-c-client.dir/clean

CMakeFiles/prom-c-client.dir/depend:
	cd /home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08 /home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08 /home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/build /home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/build /home/ignacio/Facultad/Operativos1/Practico/lab1/so-i-24-iledesma08/build/CMakeFiles/prom-c-client.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/prom-c-client.dir/depend

