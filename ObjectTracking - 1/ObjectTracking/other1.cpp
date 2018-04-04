


#include "opencv2\core\core.hpp"
#include "opencv2\highgui\highgui.hpp"
#include "opencv2\imgproc\imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/video/tracking.hpp"
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	namedWindow("orig_video", WINDOW_AUTOSIZE);
	//namedWindow("pyrDown", cv::WINDOW_AUTOSIZE);
	//VideoCapture capture(0); //openeing default camera, change it if u r using other camera device
	string filename = "cctv1.mp4";
	VideoCapture capture(filename);
	if (!capture.isOpened())
		return -1;  /// something went wrong  in opening the default camera
					//double fps = capture.get(CAP_PROP_FPS);
					//Size size((int)capture.get(CAP_PROP_FRAME_WIDTH)/2, (int)capture.get(CAP_PROP_FRAME_HEIGHT)/2); // factor 2 since pyrDown will downsample it by factor 2
					//VideoWriter writer;
					//writer.open("record.avi", -1, fps, size, true);
					// For Windows, if the above does not work, use the following command instead:
					// writer.open("record.avi", CV_FOURCC('D', 'I', 'V', '3'), fps, size, true);
					// For MAC OS, if the above does not work, use the following instruction instead:
					// writer.open("record.avi", CV_FOURCC('S', 'V', 'Q', '3'), 30.0, size, true);
					//if (!writer.isOpened())
					//{
					//	cout << "not able to write video: " << endl;
					//	return -1;
					//}
	std::vector<cv::KeyPoint> keypointsA, keypointsB, keypointsC;
	Mat descriptorsA, descriptorsB, descriptorsC;

	int Threshl = 95;
	int Octaves = 4;
	float PatternScales = 1.0f;

	Ptr<BRISK> detector = BRISK::create(Threshl, Octaves, PatternScales);





	int count = 0;
	Mat frame1, gray_frame, old_gray_frame, m_mask;

	vector<Point2f>  m_prevPts;
	vector<Point2f>  m_nextPts;
	vector<unsigned char> m_status;
	vector<float>         m_error;
	vector<Scalar> color, color1;
	vector<DMatch> match, match1;
	TermCriteria termcrit(TermCriteria::COUNT | TermCriteria::EPS, 50, 0.03);
	capture >> frame1;
	cvtColor(frame1, old_gray_frame, CV_BGR2GRAY);
	//goodFeaturesToTrack(old_gray_frame, m_prevPts, 500,0.01, 10.00);
	m_mask = Mat::zeros(frame1.size(), CV_8UC3);
	detector->detect(old_gray_frame, keypointsB);
	detector->compute(old_gray_frame, keypointsB, descriptorsB);

	//capture >> frame1;
	//cvtColor(frame1, old_gray_frame, CV_BGR2GRAY);
	//detector->detect(old_gray_frame, keypointsB);
	//detector->compute(old_gray_frame, keypointsB, descriptorsB);

	for (int i = 0; i < 20 * keypointsB.size(); i++)
	{
		//m_prevPts.push_back(keypointsB[i].pt);
		color.push_back(Scalar(rand() % 255, rand() % 255, rand() % 255));
		color1.push_back(Scalar(rand() % 255, rand() % 255, rand() % 255));
	}
	BFMatcher matcher(NORM_HAMMING, true);
	int f = 0;
	while (true)
	{
		//std::cout << "frame1";
		capture >> frame1;
		if (frame1.empty()) { break; }
		//pyrDown(frame1, frame2);  //Gaussian blurring and downsampling
		//writer << frame2;
		//m_mask = Mat::zeros(frame1.size(), CV_8UC3);
		cvtColor(frame1, gray_frame, CV_BGR2GRAY);


		keypointsA.clear();
		detector->detect(gray_frame, keypointsA);
		detector->compute(gray_frame, keypointsA, descriptorsA);


		matcher.match(descriptorsA, descriptorsB, match);
		//matcher.match(descriptorsA, descriptorsC, match1);

		//cv::calcOpticalFlowPyrLK(old_gray_frame, gray_frame, m_prevPts, m_nextPts, m_status, m_error, Size(21,21), 4, termcrit);
		//std::cout << match.size();
		//vector<DMatch>  good_match;
		cout << "r" << keypointsA.size() << "s" << match.size();
		int k = 0;
		for (size_t i = 0; i < match.size(); i++)
		{
			//cout << "r" << norm(keypointsA[match[i].queryIdx].pt - keypointsB[match[i].trainIdx].pt);
			if (match[i].distance <90)
			{
				k++;
				//std::cout << "s" << norm(keypointsA[match[i].queryIdx].pt - keypointsB[match[i].trainIdx].pt) << "r" << i << "t" << match[i].distance;
				//cout << "r";
				//good_match.push_back(match[i]);
				line(m_mask, (Point2i)keypointsA[match[i].queryIdx].pt, (Point2i)keypointsB[match[i].trainIdx].pt, color[match[i].trainIdx], 2);

				color1[match[i].queryIdx] = color[match[i].trainIdx];
				//cout << match[i].queryIdx << "#";
			}



		}
		cout << endl;
		/*
		for (size_t i = 0; i < match1.size(); i++)
		{
		//cout << "r" << norm(keypointsA[match[i].queryIdx].pt - keypointsB[match[i].trainIdx].pt);
		if (match1[i].distance <90 )
		{

		//std::cout << "s" << norm(keypointsA[match[i].queryIdx].pt - keypointsB[match[i].trainIdx].pt) << "r" << i << "t" << match[i].distance;
		//cout << "r";
		//good_match.push_back(match[i]);
		line(m_mask, (Point2i)keypointsA[match1[i].queryIdx].pt, (Point2i)keypointsC[match1[i].trainIdx].pt, color1[match1[i].queryIdx], 2);
		//cout << match1[i].queryIdx << "#";

		//color1[match1[i].queryIdx] = color[match1[i].trainIdx];
		}



		}
		*/
		cout << "##" << k << endl;
		//drawMatches(gray_frame, keypointsA, old_gray_frame, keypointsB, good_match, frame1);
		//detector->detect(gray_frame, keypointsA);
		//drawKeypoints(frame2, keypointsA, frame2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);



		gray_frame.copyTo(old_gray_frame);
		//m_prevPts = m_nextPts;
		//keypointsC.clear();
		//for (int i = 0; i < keypointsB.size(); i++)
		//	keypointsC.push_back(keypointsB[i]);
		keypointsB.clear();
		for (int i = 0; i < keypointsA.size(); i++)
			keypointsB.push_back(keypointsA[i]);
		color.clear();
		for (int i = 0; i < color1.size(); i++)
			color.push_back(color1[i]);
		//descriptorsB.copyTo(descriptorsC);
		descriptorsA.copyTo(descriptorsB);

		add(frame1, m_mask, frame1);

		imshow("orig_video", frame1);
		//imshow("pyrDown", frame2);
		if (waitKey(30) >= 0) break;
		cout << count++;

	}
	cout << "Finished Writing" << endl;
	return 0;
}



