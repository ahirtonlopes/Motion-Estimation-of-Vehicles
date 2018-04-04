/* Include required headers */
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <fstream>
#include "opencv2/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2\video\tracking.hpp>
#include <opencv2/imgcodecs.hpp>

/* Namespace */

using namespace cv;
using namespace std;
using namespace cv::xfeatures2d;

/* Function main */
int main(int argc, char** argv)
{

	namedWindow("Recorded", WINDOW_AUTOSIZE);

/* Variable declaration */
	VideoCapture cap;
	Ptr<SIFT> Video_Detector = SIFT::create();
	vector<Point2f> previous_points, next_points;
	vector<Scalar> color;
	vector<int> class_old, class_new;
	vector<float> angle_old, angle_new, differ;
	vector<unsigned char> status;
	vector<float> error;
	vector<KeyPoint> keypoints_1, keypoints_2, good_points;
	vector<DMatch> dmatch;
	int i, j, number = 1;
	ofstream output_bf("output_SIFT_bf.txt"), keypoint_bf("keypoint__SIFT_bf.txt"), SIFT_detect("SIFT_detect.txt");
	float start, end, diff;
	Mat Video_keypoints, old_frame, mask, last_frame;
	Mat frame, grayframe, descriptor_1, descriptor_2, descriptor_goodpts;
	BFMatcher match(NORM_L1, true);

/* Declaration of the termcriteria for optical flow  */
	TermCriteria termcrit(TermCriteria::COUNT | TermCriteria::EPS, 30, 0.03);
	while (number < 5)
	{
		/* Open the cap */
		string filename = "final_cctv" + to_string(number) + ".mp4";

		cap.open(filename);
		cap >> frame;

		/* Change the frame to Gray */
		cvtColor(frame, old_frame, CV_BGR2GRAY);
		mask = Mat::zeros(frame.size(), CV_8UC3);

		/* Detect and compute keypoints using SIFT detector */


		Video_Detector->detect(old_frame, keypoints_2);
		Video_Detector->compute(old_frame, keypoints_2, descriptor_2);


		/* Copy the keypoint location for comparison with the next frames */
		for (i = 0; i < keypoints_2.size(); i++)
		{
			previous_points.push_back(keypoints_2[i].pt);


		}

		/* Assign colors to each keypoints */
		for (j = 0; j < 5 * keypoints_2.size(); j++)
		{
			color.push_back(Scalar(rand() % 255, rand() % 255, rand() % 255));

		}


		/* Loop through the entire video frame by frame */
		for (;;) {
			cap >> frame;
			if (frame.empty())
			{
				string imageName = "final_image__SIFT_BF" + to_string(number) + ".jpg";
				imwrite(imageName, last_frame);
				break;             // Ran out of film
			}
			start = getTickCount();

			cvtColor(frame, grayframe, CV_RGB2GRAY);
			keypoints_1.clear();

			/* Detect keypoints from the next frame */
			
			chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
			Video_Detector->detect(frame, keypoints_1);
			Video_Detector->compute(frame, keypoints_1, descriptor_1);



			chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

			auto duration1 = chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
			SIFT_detect << duration1 << endl;

			dmatch.clear();


			/* Match the descriptors using NORM_L1 */

			chrono::high_resolution_clock::time_point t3 = chrono::high_resolution_clock::now();
			match.match(descriptor_1, descriptor_2, dmatch);


			chrono::high_resolution_clock::time_point t4 = chrono::high_resolution_clock::now();

			auto duration = chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();


			/* Draw line between keypoints based on the distance traversed */
			for (size_t i = 0; i < dmatch.size(); i++)
			{

				if (dmatch[i].distance < 250 && norm(keypoints_1[dmatch[i].queryIdx].pt - keypoints_2[dmatch[i].trainIdx].pt)>0.08)
				{

					line(mask, (Point2i)keypoints_1[dmatch[i].queryIdx].pt, (Point2i)keypoints_2[dmatch[i].trainIdx].pt, color[i], 1);
					good_points.push_back(keypoints_1[i]);
				}
			}

			/* Pass the new frame as previous for the next loop */
			grayframe.copyTo(old_frame);


			/* Copy unique keypoints to pass for the next loop */
			if (good_points.size() == 0)
			{
				descriptor_1.copyTo(descriptor_2);
				keypoints_2.clear();
				for (i = 0; i < keypoints_1.size(); i++)
				{
					keypoints_2.push_back(keypoints_1[i]);


				}
			}
			
			else
			{
				keypoints_2.clear();
				for (i = 0; i < good_points.size(); i++)
				{
					keypoints_2.push_back(good_points[i]);

				}
				Video_Detector->compute(grayframe, keypoints_2, descriptor_2);
			}
			


			keypoint_bf << good_points.size() << endl;

			/* Add the mask of the line to the new frame */
			add(frame, mask, frame);

			output_bf << duration << endl;


			last_frame = frame;
			imshow("Recorded", frame);
			good_points.clear();
			if (waitKey(33) >= 0)break;
		}


		output_bf << "End Video" << endl;
		SIFT_detect << "End Video" << endl;
		keypoint_bf << "End Video" << endl;

		number++;
	}
	return 0;
}
