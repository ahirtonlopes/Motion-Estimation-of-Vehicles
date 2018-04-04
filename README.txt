Project Contributors:

Mandar Rajendra Kulkarni 1213383936
Rajhans Singh 1213315296

Instructor:

Prof. Dr. Lina Karam

Implemented feature detectors:

SIFT
BRISK 

Application:

Motion Estimation

Description:

The codes work on 4 different video files to show a comparative study of features and matching algorithms. The outputs generated will be the last frames running in the algorithm.

Project Files in code directory:

BRISK_Hamming_Match - file main.cpp(BRISK with Bruteforce matcher)
BRISK_KLT_OpticalFlow - file main.cpp(BRISK with KLT)
ObjectTracking-1 - sample.cpp(SIFT with KLT)
ObjectTracking-2 - sample1.cpp(SIFT with Bruteforce matcher)

System Specifications:

Visual Studio 17 on Windows 10 64bit
Intel i7 processor

How to compile and run:

For BRISK detector: Do the following in each project file:
1) Open the test1.sln (microsoft visual studio solution) file with visual studio 17
2)The source file is : ..\test1\main.cpp (in visual studio it will be in source files section)
3)Build the project: Build->Build Solution
4)Execute the test1.exe file present in ..\x64\Debug\test1.exe
5)output will be genreated in same ..\x64\Debug\ as png image.

For each project: .exe file is located in ..\x64\Debug\test1.exe in their respective project file

For SIFT detector: Do the following in each project file:
1) Open the ObjectTracking.sln (microsoft visual studio solution) file with visual studio 17
2)The source file is : ..\ObjectTracking\sample.cpp for KLT(in visual studio it will be in source files section) and ..\ObjectTracking\sample1.cpp for Bruteforce.
3)Build the project: Build->Build Solution
4)Execute the test1.exe file present in ..\x64\Debug\ObjectTracking.exe
5)output will be genreated in same ..\x64\Debug\ as png image.

For each project: .exe file is located in ..\x64\Debug\ObjectTracking.exe in their respective project file