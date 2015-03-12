#pragma once

#include "opencv2/highgui/highgui_c.h"
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/video.hpp>
#include <opencv2/core.hpp>


class VideoStance
{
public:
    VideoStance();
    ~VideoStance();
    void ProcessVideo(cv::Mat _frame);
    const unsigned int GetVideoStance() const;
private:
    unsigned int mVideoStance;
};




// VIDEOSTANCE_H
