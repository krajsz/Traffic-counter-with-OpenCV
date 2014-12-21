#include "fps.h"

FPS::FPS()
{
}
FPS::~FPS()
{
}

void FPS::Initialise()
{
    this->mFPS = 0;
    this->mStart = 0;
}

void FPS::Start()
{
    this->mStart = cv::getTickCount();
}

void FPS::Calculate()
{
    this->mFPS = (cv::getTickCount()  - mStart)* 1000/ cv::getTickFrequency();
}

double FPS::GetFPS()
{
    return mFPS;
}
