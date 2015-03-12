#pragma once


#include "opencv2/highgui/highgui_c.h"
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/video.hpp>
#include <opencv2/core.hpp>
#include <opencv2/core/cuda.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <opencv2/core/cuda_types.hpp>
#include <opencv2/objdetect.hpp>
//#include <opencv2/core/cuda/utility.hpp>
//#include <opencv2/ts/gpu_test.hpp>


class LaneDetector
{
public:
    LaneDetector();
    ~LaneDetector();
    std::pair<cv::Point2i, cv::Point2i> DetectLanes(cv::Mat _frame);

private:
    unsigned int mLaneCount;
    std::map <std::string, std::vector<int> > mTrackbarValues;
    cv::Mat mHSVFrame;
    cv::Mat mErodeElement;
    cv::Mat mDilateElement;
    cv::Mat mThresholdedFrame;
    void CreateTrackbars();
};

// LANEDETECTOR_H
