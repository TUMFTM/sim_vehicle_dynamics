# Workflow building the project with CMake
Make sure you have a compiler and [CMake installed](https://cmake.org/install/) on your System.
You can check your version with the following command in the terminal:
```
cmake --version
```
First create a build directory and then go inside it with the following two commands  
```
mkdir build

cd build/
```
By typing  
```
cmake ..
```
CMake will create the make files inside the build folder.
Moreover, this will output the detected compiler CMake is utilized.
After that you can build the program using
```
cmake --build .
```
The process creates the following executable file

__Sim_Vehicle_Dynamics__

You can run it inside the terminal by typing
```
./Sim_Vehicle_Dynamics
```
This command will run the `/src/main.c` file of the project. Each time
something is changed in the `main.c` file, the described sequence must be
repeated for the changes to take effect.

## Current configuration and customization
To customize the build process, the file `CMakeLists.txt` must be modified.
The commands within the file specify which sources are compiled.  
Due to errors within the dual track model, only the following files are compiled:
- SingleTrackModel.c
- VehicleState.c
- execute_testcase.c
- create_csv_testcases.c
- ini.c

To add another FILE to the list of compiled files use
```
list(APPEND SOURCES src/FILE.c)
```

### compiler flags

For the following compilers, all warnings have been disabled
- GNU
- AppleClang
- MinGW
- MSVC

A full list of compilers supported by CMake can be found at the bottom of the page [here](https://cmake.org/cmake/help/latest/manual/cmake-compile-features.7.html#supported-compilers).

If another compiler is used, no flags are passed to the compiler.
In this case, it must also be checked whether the math library must be linked manually.
To change a compiler flag, the following command is used within CMakeLists.txt.
```
target_compile_options(Sim_Vehicle_Dynamics PRIVATE FLAG)
```
The following command is used to link the math library manually.
```
target_link_libraries(Sim_Vehicle_Dynamics PRIVATE m)

```

### build on Windows

If several compilers are installed on Windows, it can be specified which compiler will be used during the make process.
It is recommended to use the MinGW compiler.
The commands for the selection of the MSVC and the MinGW compiler are shown below as examples.
Please make sure that you use the first command with the installed version of the MSVC compiler on your machine and change the text inside the quotes accordingly.  
```
cmake .. -G “Visual Studio 16 2019”

cmake .. -G "MinGW Makefiles"
```

## NOTICE/ Accepted bug

If you use the MSVC compiler the executable will be created inside the /build/Debug directory.
To run the program you first have to move the executable to the /build directory.
