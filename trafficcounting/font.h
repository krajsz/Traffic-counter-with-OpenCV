#ifndef FONT_H
#define FONT_H


#include "opencv2/highgui/highgui_c.h"
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/videoio.hpp"
#include <opencv2/video.hpp>
#include <opencv2/core.hpp>

typedef struct bgrdColor
{
    double _b;
    double _g;
    double _r;
} BGRdColor;


class Font
{
public:
    Font(std::pair<int, int> _startCoord, int _fontFace, BGRdColor _FontColor, int _thickness, double _fontScale);
    Font();
    ~Font();

    int Initialize(std::pair<int,int> _startCoord, int _fontFace , BGRdColor _FontColor, int _thickness, double _fontScale);
    void WriteOnImage(std::string _Text, cv::Mat _Image);
    void GetInfos();

private:
    cv::Point mStartCoord = cv::Point( 10,10);
    cv::Scalar mColor;
    int mThickness { 1 };
    double mFontScale;
    int mFontFace { cv::FONT_HERSHEY_SIMPLEX };
    BGRdColor mRGBColor { 1.0, 0.0,0.0};
};

#endif // FONT_H
