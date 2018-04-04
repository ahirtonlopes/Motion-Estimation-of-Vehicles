/* Including required headers and libraries */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <chrono>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2\video\tracking.hpp>
#include <opencv2/imgcodecs.hpp>

/* Using following namespace */
using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

/** @function main */
int main(int argc, char** argv)
{



	/* Opens window for the video */
	namedWindow("Recorded", WINDOW_AUTOSIZE);

	/* Variable declaration */
	VideoCapture cap;
	Ptr<SIFT> Video_Detector = SIFT::create();
	vector<Point2f> previous_points, next_points, good_points;
	vector<Scalar> color;
	vector<int> class_old, class_new, difference;
	vector<float> angle_old, angle_new;
	vector<unsigned char> status;
	vector<float> error;
	vector<KeyPoint> keypoints_1, keypoints_2;
	int i, j, number=1;
	ofstream output("output_SIFT_KLT.txt");
	ofstream keypoint("keypoint_SIFT_KLT.txt");
	float start, end;
	Mat Video_keypoints, old_frame, last_frame, mask;
	Mat frame, grayframe;
	TermCriteria termcrit(TermCriteria::COUNT | TermCriteria::EPS, 30, 0.03);


	/* Run all the 4 videos */
	while (number < 5)
	{
		string filename = "final_cctv" + to_string(number) + ".mp4";

	/* open file */
		cap.open(filename);
		cap >> frame;


	/* Using the SIFT detector object to generate keypoints */
		cvtColor(frame, old_frame, CV_BGR2GRAY);
		mask = Mat::zeros(frame.size(), CV_8UC3);
		Video_Detector->detect(old_frame, keypoints_2);


	/* Copying keypoints to different array */

		for (i = 0; i < keypoints_2.size(); i++)
		{
			previous_points.push_back(keypoints_2[i].pt);

		}
		for (j = 0; j < 5 * keypoints_2.size(); j++)
		{
			color.push_back(Scalar(rand() % 255, rand() % 255, rand() % 255));

		}


	/* Run until the frame finishes */
		for (;;) {
			cap >> frame;
			if (frame.empty())
			{
				string imageName = "final_image_KLT" + to_string(number) + ".jpg";
				imwrite(imageName, last_frame);
				break;             // Ran out of film
			}



			start = getTickCount();

			cvtColor(frame, grayframe, CV_RGB2GRAY);


	/* Calculate optical flow and also the time required for the same */

			chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

			cv::calcOpticalFlowPyrLK(old_frame, grayframe, previous_points, next_points, status, error, Size(21, 21), 4, termcrit);

			chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

			auto duration = chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count(); 



	/* Mask a line to track the given object */

			for (size_t i = 0; i < status.size(); i++)
			{

				if (status[i] && norm(next_points[i] - previous_points[i]) > 0.06 && error[i] < 50)
				{

					line(mask, previous_points[i], next_points[i], color[i], 1.5);
					good_points.push_back(next_points[i]);
				}
			}

	/* Detect keypoints in the new frame to pass them to KLT */

			Video_Detector->detect(frame, keypoints_1);
			grayframe.copyTo(old_frame);
			previous_points.clear();

			if (good_points.size() == 0)
			{
				for (i = 0; i < keypoints_1.size(); i++)
				{
					previous_points.push_back(keypoints_1[i].pt);

				}
			}
			else {
				for (i = 0; i < good_points.size(); i++)
				{
					previous_points.push_back(good_points[i]);
				}

			}


	/* Add the line joining same keypoints */
			add(frame, mask, frame);

			end = getTickCount();

	/* Write the calues of time and number of keypoints generated to the respective files */

			output << duration << endl;
			keypoint << keypoints_1.size() << endl;

			imshow("Recorded", frame);
			last_frame = frame;
			good_points.clear();
			if (waitKey(33) >= 0)break;
		}
		output << "End Video" << endl;
		keypoint << "End Video" << endl;
		number++;
	}

	return 0;
}
