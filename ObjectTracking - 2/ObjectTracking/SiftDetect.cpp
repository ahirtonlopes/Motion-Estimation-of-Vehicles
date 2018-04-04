#include <stdio.h>
#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2\video\tracking.hpp>
#include <opencv2/imgcodecs.hpp>


using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

/** @function main */
int main(int argc, char** argv)
{

	namedWindow("Recorded", WINDOW_AUTOSIZE);
	namedWindow("VideoKeypoints", WINDOW_AUTOSIZE);


	VideoCapture cap;
	Ptr<SIFT> Video_Detector = SIFT::create();
	vector<Point2f> previous_points, next_points;
	vector<Scalar> color;
	vector<unsigned char> status;
	vector<float> error;
	vector<KeyPoint> keypoints_1, keypoints_2;


	int i, j;
	cap.open("Video1.mp4");
	Mat Video_keypoints, old_frame, mask;
	Mat frame;
	mask = Mat::zeros(frame.size(), CV_8UC3);

	TermCriteria termcrit(TermCriteria::COUNT | TermCriteria::EPS, 30, 0.03);


	for (;;) {
		cap >> frame;
		if (frame.empty()) break;             // Ran out of film


		cvtColor(frame, frame, CV_RGB2GRAY);

		if (cv::waitKey(33) >= 0) break;


		Video_Detector->detect(frame, keypoints_1);

		drawKeypoints(frame, keypoints_1, Video_keypoints, Scalar::all(-1), DrawMatchesFlags::DEFAULT);



		//calcOpticalFlowPyrLK(old_frame, frame, previous_points, next_points, status, error, Size(21, 21), 4, termcrit);
		imshow("VideoKeypoints", Video_keypoints);


		

		imshow("Recorded", frame);
	}

	waitKey(0);

	return 0;
}
