# Motion-Estimation-of-Vehicles

This project presents a study of two keypoint detection techniques, namely SIFT and BRISK for motion estimation task. Motion estimation tracks how an object moves through a scene from one frame to another. The various applications of motion estimation are object segmentation in video, accessing dynamics of a system, quality of an activity and recognizing events and activity. Optical flow techniques are generally used for this task. Optical flow is the apparent motion of object or surface from one frame to another. The most acknowledged optical flow techniques are Lucas-Kanade (LK) and the Kanade-Lucas-Tomasi (KLT) algorithms. Other state of the art methods start with the LK algorithm in addition with gradient constancy, energy minimization with smoothing term, region matching and keypoint matching (long-range).

In general, optical flow estimates the location of keypoints in current frame given the set of keypoint from previous frame. In the first part of the experiment the pyramidal implementation of Kanade-Lucas-Tomasi technique is used to track the SIFT and BRISK keypoints. In the second part features corresponding to this keypoints are matched by using brute-force technique(Euclidean or Hamming distance) to get the counterpart keypoints between the two frames.

# Scale-Invariant Feature Transform(SIFT)

Scale-Invariant Feature Transform was proposed by Dr. David Lowe in his paper titled “Distinctive Image Features from Scale-Invariant Keypoints”. This method of keypoint detection is one of the finest methods which produces keypoints with unique properties and robustness to affine distortion, change in 3D viewpoint and noise. The SIFT detector works on a small neighborhood which results in unique and large number of keypoints in an image.

# Binary Robust Invariant Scalable Keypoints(BRISK)

The ultimate goal for any feature extractor is to produce high quality description with low computational requirements. BRISK[3] achieves comparable feature quality as SIFT but at very low computation cost. BRISK is binary feature extractor improves the notion of BRIEF (Binary robust independent elementary features)[10]. BRIEF is designed for fast feature extraction and matching and computed by comparing the intensity between pre-determined randomly chosen pair of pixels in a patch around a keypoint. BRIEF technique is fast but highly sensitive to rotation and scale variation. BRISK introduces a novel method for high-quality, fast keypoint detection, description and matching.

# Experiments and Results

We performed experiment to track vehicles caught by stationary camera. Four videos of 640x360 resolution have been used. For simplicity each video has been selected such that the object in motion remains in frame for most part of video and no new objects pop-up in between. OpenCV C++ implementation of SIFT, BRISK and pyramidal KLT algorithm has been used and executed on standard intel i7 computer. The experiment is divided in two parts: 1) SIFT and BRISK keypoint with KLT optical flow method, 2) SIFT and BRISK feature with brute force matching method.

Figure 1: Final frame of the 4 videos for BRISK + KLT:

![image](https://user-images.githubusercontent.com/31497107/40882824-b7879146-66a2-11e8-90ef-6db174f382f6.png)

Figure 2: Final frame of the 4 videos for BRISK + Hamming Distance:

![image](https://user-images.githubusercontent.com/31497107/40882828-cd51d414-66a2-11e8-8378-5758a92bb0ec.png)

Figure 3: Final frame of the 4 videos for SIFT + KLT:

![image](https://user-images.githubusercontent.com/31497107/40882863-ae529b06-66a3-11e8-985f-2839418f5013.png)

FIgure 4: Final frame of the 4 videos for SIFT + Euclidean Distance:

![image](https://user-images.githubusercontent.com/31497107/40882831-e38afad0-66a2-11e8-8f59-e357eb136c63.png)

# Conclusion

The experiment results suggest that KLT produces faster and accurate results as compared to Bruteforce matching technique. Whereas SIFT generates more number of repeatable features as compared to BRISK. But BRISK gives better time performance than SIFT. The experiment shows that KLT techniques produces a smoother tracking path than the Bruteforce matching method. As the Bruteforce matcher calculates keypoints every frame, it produces non-continuous results. We also observed that in case of BRISK detector the time taken by Hamming Distance matcher is faster than KLT/Euclidean distance. The major issue with KLT is that the it matches and updates old keypoints and does not consider new objects entering the frame. Hence, to determine the interval of reinitializing keypoints is a tough task. So, it would be an interesting topic of research to study on improving BRISK method to include the of knowledge of previous keypoints while searching for current keypoints. In this way the number of trackable keypoints for BRISK would be less and would allow new objects to be tracked efficiently with fastest matching algorithm. In this project Bruteforce technique is used for feature matching which can be replaced by faster matching techniques like Approximate nearest neighbor or other fast Binary matching method.


Project Contributors:

Mandar Rajendra Kulkarni
Rajhans Singh

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
