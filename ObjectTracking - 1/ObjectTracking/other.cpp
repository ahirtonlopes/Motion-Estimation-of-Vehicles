

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
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
	string filename = "Recorded.avi";
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
	std::vector<cv::KeyPoint> keypointsA, keypointsB;
	Mat descriptorsA, descriptorsB;

	int Threshl = 90;
	int Octaves = 6;
	float PatternScales = 1.0f;

	Ptr<BRISK> detector = BRISK::create(Threshl, Octaves, PatternScales);





	int count = 0;
	Mat frame1, gray_frame, old_gray_frame, m_mask;

	vector<Point2f>  m_prevPts;
	vector<Point2f>  m_nextPts;
	vector<unsigned char> m_status;
	vector<float>         m_error;
	vector<Scalar> color;
	TermCriteria termcrit(TermCriteria::COUNT | TermCriteria::EPS, 30, 0.03);
	capture >> frame1;
	cvtColor(frame1, old_gray_frame, CV_BGR2GRAY);
	//goodFeaturesToTrack(old_gray_frame, m_prevPts, 500,0.01, 10.00);
	m_mask = Mat::zeros(frame1.size(), CV_8UC3);
	detector->detect(old_gray_frame, keypointsB);

	for (int i = 0; i < keypointsB.size(); i++)
	{
		m_prevPts.push_back(keypointsB[i].pt);

	}
	for (int i = 0; i <5 * keypointsB.size(); i++)
		color.push_back(Scalar(rand() % 255, rand() % 255, rand() % 255));
	while (true)
	{
		cout << "frame1";
		capture >> frame1;
		if (frame1.empty()) { break; }
		//pyrDown(frame1, frame2);  //Gaussian blurring and downsampling
		//writer << frame2;

		cvtColor(frame1, gray_frame, CV_BGR2GRAY);
		//if (m_prevPts.size() == 0)
		//{
		//goodFeaturesToTrack(gray_frame, m_nextPts, 500, 0.01, 10.00);
		//cout << m_nextPts.size();
		//}

		//m_nextPts.clear();

		cout << m_prevPts.size();
		cv::calcOpticalFlowPyrLK(old_gray_frame, gray_frame, m_prevPts, m_nextPts, m_status, m_error, Size(21, 21), 4, termcrit);
		cout << "r";
		cout << m_nextPts.size();
		//vector<Point2f>  good_Pts;
		for (size_t i = 0; i < m_status.size(); i++)
		{
			if (m_status[i] && norm(m_nextPts[i] - m_prevPts[i])>0.05 && m_error[i]<25)
			{
				//cout << m_prevPts[i];
				//cout << "EE" << m_error[i] << "EE";
				//good_Pts.push_back(m_nextPts[i]);
				//circle(frame1, m_prevPts[i], 15, cv::Scalar(0), -1);
				line(m_mask, m_prevPts[i], m_nextPts[i], color[i], 1);

				//cv::circle(m_mask, m_nextPts[i], 3, cv::Scalar(0, 250, 0), -1);

			}

		}

		//detector->detect(gray_frame, keypointsA);
		//drawKeypoints(frame2, keypointsA, frame2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);

		//keypointsB = keypointsA;
		detector->detect(gray_frame, keypointsA);
		gray_frame.copyTo(old_gray_frame);
		m_prevPts.clear();
		for (int i = 0; i < keypointsA.size(); i++)
		{
			m_prevPts.push_back(keypointsA[i].pt);

		}

		add(frame1, m_mask, frame1);

		imshow("orig_video", frame1);


		//imshow("pyrDown", frame2);
		if (waitKey(30) >= 0) break;
		count++;

	}
	cout << "Finished Writing" << endl;
	return 0;
}
