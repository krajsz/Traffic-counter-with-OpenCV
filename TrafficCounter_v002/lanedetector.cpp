#include "lanedetector.h"

LaneDetector::LaneDetector():mLaneCount(0)
{
    mTrackbarValues["H_values"].push_back(0);
    mTrackbarValues["H_values"].push_back(512);

    mTrackbarValues["S_values"].push_back(0);
    mTrackbarValues["S_values"].push_back(512);

    mTrackbarValues["V_values"].push_back(0);
    mTrackbarValues["V_values"].push_back(512);
    cv::Mat a;
    cv::cuda::GpuMat b(a);
}

LaneDetector::~LaneDetector()
{
}

std::pair<cv::Point2i,cv::Point2i> LaneDetector::DetectLanes(cv::Mat _frame)
{
    CreateTrackbars();

    cv::cvtColor(_frame, mHSVFrame, cv::COLOR_BGR2HSV);
    cv::inRange(mHSVFrame,cv::Scalar(0, 0, 1),cv::Scalar(20, 20, 1),mThresholdedFrame);
    cv::inRange(mHSVFrame, cv::Scalar(mTrackbarValues["H_values"][0], mTrackbarValues["S_values"][0], mTrackbarValues["V_values"][0]), cv::Scalar(mTrackbarValues["H_values"][1],mTrackbarValues["S_values"][1], mTrackbarValues["V_values"][1]), mThresholdedFrame);
    mErodeElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(4,4));
    mDilateElement = cv::getStructuringElement(cv::MORPH_RECT,cv::Size(12,12));

    cv::erode(mThresholdedFrame, mThresholdedFrame, mErodeElement);
    cv::dilate(mThresholdedFrame, mThresholdedFrame, mDilateElement);

    cv::imshow("LaneTest",mThresholdedFrame);
}
void LaneDetector::CreateTrackbars()
{
    cv::namedWindow("Trackbars", 0);
    cv::createTrackbar("H_Min", "Trackbars", &mTrackbarValues["H_values"][0], mTrackbarValues["H_values"][1], 0, 0);
    cv::createTrackbar("H_Max","Trackbars", &mTrackbarValues["H_values"][1], mTrackbarValues["H_values"][1], 0, 0);

    cv::createTrackbar("S_Min","Trackbars", &mTrackbarValues["S_values"][0], mTrackbarValues["S_values"][1], 0, 0);
    cv::createTrackbar("S_Max","Trackbars", &mTrackbarValues["S_values"][1], mTrackbarValues["S_values"][1], 0, 0);

    cv::createTrackbar("V_Min","Trackbars", &mTrackbarValues["V_values"][0], mTrackbarValues["V_values"][1], 0, 0);
    cv::createTrackbar("V_Max","Trackbars", &mTrackbarValues["V_values"][1], mTrackbarValues["V_values"][1], 0, 0);
}
