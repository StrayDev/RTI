# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.3.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.3.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = F:\Dev\RTI

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = F:\Dev\RTI\_build

# Include any dependencies generated for this target.
include CMakeFiles/RTI.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/RTI.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/RTI.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/RTI.dir/flags.make

CMakeFiles/RTI.dir/main.cpp.obj: CMakeFiles/RTI.dir/flags.make
CMakeFiles/RTI.dir/main.cpp.obj: CMakeFiles/RTI.dir/includes_CXX.rsp
CMakeFiles/RTI.dir/main.cpp.obj: ../main.cpp
CMakeFiles/RTI.dir/main.cpp.obj: CMakeFiles/RTI.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\Dev\RTI\_build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/RTI.dir/main.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RTI.dir/main.cpp.obj -MF CMakeFiles\RTI.dir\main.cpp.obj.d -o CMakeFiles\RTI.dir\main.cpp.obj -c F:\Dev\RTI\main.cpp

CMakeFiles/RTI.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RTI.dir/main.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\Dev\RTI\main.cpp > CMakeFiles\RTI.dir\main.cpp.i

CMakeFiles/RTI.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RTI.dir/main.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\Dev\RTI\main.cpp -o CMakeFiles\RTI.dir\main.cpp.s

CMakeFiles/RTI.dir/app/src/Application.cpp.obj: CMakeFiles/RTI.dir/flags.make
CMakeFiles/RTI.dir/app/src/Application.cpp.obj: CMakeFiles/RTI.dir/includes_CXX.rsp
CMakeFiles/RTI.dir/app/src/Application.cpp.obj: ../app/src/Application.cpp
CMakeFiles/RTI.dir/app/src/Application.cpp.obj: CMakeFiles/RTI.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\Dev\RTI\_build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/RTI.dir/app/src/Application.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RTI.dir/app/src/Application.cpp.obj -MF CMakeFiles\RTI.dir\app\src\Application.cpp.obj.d -o CMakeFiles\RTI.dir\app\src\Application.cpp.obj -c F:\Dev\RTI\app\src\Application.cpp

CMakeFiles/RTI.dir/app/src/Application.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RTI.dir/app/src/Application.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\Dev\RTI\app\src\Application.cpp > CMakeFiles\RTI.dir\app\src\Application.cpp.i

CMakeFiles/RTI.dir/app/src/Application.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RTI.dir/app/src/Application.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\Dev\RTI\app\src\Application.cpp -o CMakeFiles\RTI.dir\app\src\Application.cpp.s

CMakeFiles/RTI.dir/app/src/Vector3.cpp.obj: CMakeFiles/RTI.dir/flags.make
CMakeFiles/RTI.dir/app/src/Vector3.cpp.obj: CMakeFiles/RTI.dir/includes_CXX.rsp
CMakeFiles/RTI.dir/app/src/Vector3.cpp.obj: ../app/src/Vector3.cpp
CMakeFiles/RTI.dir/app/src/Vector3.cpp.obj: CMakeFiles/RTI.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\Dev\RTI\_build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/RTI.dir/app/src/Vector3.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RTI.dir/app/src/Vector3.cpp.obj -MF CMakeFiles\RTI.dir\app\src\Vector3.cpp.obj.d -o CMakeFiles\RTI.dir\app\src\Vector3.cpp.obj -c F:\Dev\RTI\app\src\Vector3.cpp

CMakeFiles/RTI.dir/app/src/Vector3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RTI.dir/app/src/Vector3.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\Dev\RTI\app\src\Vector3.cpp > CMakeFiles\RTI.dir\app\src\Vector3.cpp.i

CMakeFiles/RTI.dir/app/src/Vector3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RTI.dir/app/src/Vector3.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\Dev\RTI\app\src\Vector3.cpp -o CMakeFiles\RTI.dir\app\src\Vector3.cpp.s

CMakeFiles/RTI.dir/app/src/Tri.cpp.obj: CMakeFiles/RTI.dir/flags.make
CMakeFiles/RTI.dir/app/src/Tri.cpp.obj: CMakeFiles/RTI.dir/includes_CXX.rsp
CMakeFiles/RTI.dir/app/src/Tri.cpp.obj: ../app/src/Tri.cpp
CMakeFiles/RTI.dir/app/src/Tri.cpp.obj: CMakeFiles/RTI.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\Dev\RTI\_build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/RTI.dir/app/src/Tri.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RTI.dir/app/src/Tri.cpp.obj -MF CMakeFiles\RTI.dir\app\src\Tri.cpp.obj.d -o CMakeFiles\RTI.dir\app\src\Tri.cpp.obj -c F:\Dev\RTI\app\src\Tri.cpp

CMakeFiles/RTI.dir/app/src/Tri.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RTI.dir/app/src/Tri.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\Dev\RTI\app\src\Tri.cpp > CMakeFiles\RTI.dir\app\src\Tri.cpp.i

CMakeFiles/RTI.dir/app/src/Tri.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RTI.dir/app/src/Tri.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\Dev\RTI\app\src\Tri.cpp -o CMakeFiles\RTI.dir\app\src\Tri.cpp.s

CMakeFiles/RTI.dir/app/src/AABB.cpp.obj: CMakeFiles/RTI.dir/flags.make
CMakeFiles/RTI.dir/app/src/AABB.cpp.obj: CMakeFiles/RTI.dir/includes_CXX.rsp
CMakeFiles/RTI.dir/app/src/AABB.cpp.obj: ../app/src/AABB.cpp
CMakeFiles/RTI.dir/app/src/AABB.cpp.obj: CMakeFiles/RTI.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=F:\Dev\RTI\_build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/RTI.dir/app/src/AABB.cpp.obj"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/RTI.dir/app/src/AABB.cpp.obj -MF CMakeFiles\RTI.dir\app\src\AABB.cpp.obj.d -o CMakeFiles\RTI.dir\app\src\AABB.cpp.obj -c F:\Dev\RTI\app\src\AABB.cpp

CMakeFiles/RTI.dir/app/src/AABB.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RTI.dir/app/src/AABB.cpp.i"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E F:\Dev\RTI\app\src\AABB.cpp > CMakeFiles\RTI.dir\app\src\AABB.cpp.i

CMakeFiles/RTI.dir/app/src/AABB.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RTI.dir/app/src/AABB.cpp.s"
	C:\PROGRA~1\MINGW-~1\X86_64~1.0-P\mingw64\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S F:\Dev\RTI\app\src\AABB.cpp -o CMakeFiles\RTI.dir\app\src\AABB.cpp.s

# Object files for target RTI
RTI_OBJECTS = \
"CMakeFiles/RTI.dir/main.cpp.obj" \
"CMakeFiles/RTI.dir/app/src/Application.cpp.obj" \
"CMakeFiles/RTI.dir/app/src/Vector3.cpp.obj" \
"CMakeFiles/RTI.dir/app/src/Tri.cpp.obj" \
"CMakeFiles/RTI.dir/app/src/AABB.cpp.obj"

# External object files for target RTI
RTI_EXTERNAL_OBJECTS =

RTI.exe: CMakeFiles/RTI.dir/main.cpp.obj
RTI.exe: CMakeFiles/RTI.dir/app/src/Application.cpp.obj
RTI.exe: CMakeFiles/RTI.dir/app/src/Vector3.cpp.obj
RTI.exe: CMakeFiles/RTI.dir/app/src/Tri.cpp.obj
RTI.exe: CMakeFiles/RTI.dir/app/src/AABB.cpp.obj
RTI.exe: CMakeFiles/RTI.dir/build.make
RTI.exe: lib/tinyobj/libtinyobjloader.a
RTI.exe: CMakeFiles/RTI.dir/linklibs.rsp
RTI.exe: CMakeFiles/RTI.dir/objects1.rsp
RTI.exe: CMakeFiles/RTI.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=F:\Dev\RTI\_build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable RTI.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\RTI.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/RTI.dir/build: RTI.exe
.PHONY : CMakeFiles/RTI.dir/build

CMakeFiles/RTI.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\RTI.dir\cmake_clean.cmake
.PHONY : CMakeFiles/RTI.dir/clean

CMakeFiles/RTI.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" F:\Dev\RTI F:\Dev\RTI F:\Dev\RTI\_build F:\Dev\RTI\_build F:\Dev\RTI\_build\CMakeFiles\RTI.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/RTI.dir/depend

