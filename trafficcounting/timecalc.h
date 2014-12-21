#ifndef TIMECALC_H
#define TIMECALC_H
#include <cmath>
#include <sstream>
#include <QString>

class TimeCalc
{
public:
    TimeCalc();
    ~TimeCalc();
    std::string VideoLength(int _currentMS);
    std::string CurrentTime(int _currentMS);
    int GetMinutes() const;
    double GetMinutesD() const;

    void Reset();
private:
    int GetRounded(float _mSec);


    std::stringstream mVideoLength;
    std::stringstream mCurrentTime;
    // for Length
    int mHours;
    int mMinutes;
    int mSeconds ;
    int mMSeconds;
    int mSecRounded;
    int mFrameCount;
    // for Current

    int mH;
    int mM;
    int mS;
    int mMS;
};

#endif // TIMECALC_H
