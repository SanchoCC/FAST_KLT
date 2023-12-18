# FAST_KLT

# Build Instructions
To build the program, follow these steps:

1. Build OpenCV with CMake
Use CMake to build OpenCV and place the compiled files at the following path: FAST_KLT/external/opencv/build. Both static and dynamic linking options are available.

# Example with cmake-gui for Microsoft Visual Studio 2022

Browse source and build directories to "..FAST_KLT/external/opencv" for Source and "..FAST_KLT/external/opencv/build" for Build.


![image](https://github.com/SanchoCC/FAST_KLT/assets/134946556/7e411cfe-4b43-46ba-8c2b-e215648d1286)


Configure generator and chose x64 platform.


![image](https://github.com/SanchoCC/FAST_KLT/assets/134946556/a1e4d348-91bc-42d3-acd3-57ec44020aba)


Configure BUILD_SHARED_LIBS and press "Generate".


![image](https://github.com/SanchoCC/FAST_KLT/assets/134946556/f2995dbb-7f02-4daa-ad27-15bf398434fb)

Open OpenCV builded project and build solutions ALL_BUILD and INSTALL for both Debug and Release.

2. Build the Project
After successfully building OpenCV, proceed to build the FAST_KLT project itself.
```
cd FAST_KLT
mkdir build
cd build
cmake ..
```
Build solutions for Debug and Release of your project.
This will generate the executable for the FAST_KLT project. 

If you using SHARED_LIBS, copy dll files from ..FAST_KLT/external/opencv/build/bin/Debug and Release to ..FAST_KLT/build/Debug and Release.

# Examples of work FAST_Implementation with kDensity = 15

Number of keypoints: 996, Detection time: 1643 microseconds

![ResultImage](https://github.com/SanchoCC/FAST_KLT/assets/134946556/a6334f53-25ad-47f0-a6f1-9ceb6ffe6730)

Number of keypoints: 13344, Detection time: 16969 microseconds

![ResultImage](https://github.com/SanchoCC/FAST_KLT/assets/134946556/6079174e-d877-443f-a353-b32d68abe7a8)

