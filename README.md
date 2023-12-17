# FAST_KLT

Build Instructions
To build the program, follow these steps:

1. Build OpenCV with CMake
Use CMake to build OpenCV and place the compiled files at the following path: FAST_KLT/external/opencv/build. Both static and dynamic linking options are available.

# Example with cmake-gui for Microsoft Visual Studio 2022

Browse source and build directories to "..external/opencv" for Source and "..external/opencv/build" for Build


![image](https://github.com/SanchoCC/FAST_KLT/assets/134946556/7e411cfe-4b43-46ba-8c2b-e215648d1286)


Configure generator and chose x64 platform


![image](https://github.com/SanchoCC/FAST_KLT/assets/134946556/a1e4d348-91bc-42d3-acd3-57ec44020aba)


Configure BUILD_SHARED_LIBS and press "Generate"


![image](https://github.com/SanchoCC/FAST_KLT/assets/134946556/f2995dbb-7f02-4daa-ad27-15bf398434fb)


2. Build the Project
After successfully building OpenCV, proceed to build the FAST_KLT project itself.
```
cd FAST_KLT
mkdir build
cd build
cmake ..
```
This will generate the executable for the FAST_KLT project. Ensure that all dependencies are correctly linked during the build process.
