# Build Instructions
This project uses cmake. To build, create a folder for output files. I called this folder 'build'.

run `cmake -S . -B output_folder` to do initial cmake generation for first-time setup, then, to build the project, run `cmake --build output_folder`

Output executables should be found somewhere in output_folder, depending on the build system cmake decided to use.

## Adding new source files
Any time a new source file (not a header) is added to the project, it also must be added in CMakeLists.txt. Apparently this is considered good practice, 
because the alternative, globbing, will not cause cmake to update when you add a new file. I don't understand the reasoning here, really, but sure.