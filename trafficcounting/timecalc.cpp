#include "timecalc.h"

TimeCalc::TimeCalc():mMS(0), mMSeconds(0), mM(0),mMinutes(0),mSeconds(0),mS(0),mH(0),mHours(0)
{
}
TimeCalc::~TimeCalc()
{
}

int TimeCalc::GetRounded(float _mSec)
{
    if (std::floor(_mSec+0.5) > _mSec)
    {
        return std::floor(_mSec-0.5);
    }
    else
    {
        return std::floor(_mSec+0.5);
    }
}

void TimeCalc::Reset()
{
    mMS = 0;
    mS = 0;
    mM = 0;
    mH = 0;
    mCurrentTime.str("");
}

const double TimeCalc::GetMinutesD() const
{
    return static_cast<double> (mMS) / 1000.0 / 60.0;
}

std::string TimeCalc::CurrentTime(int _currentMS)
{
    mCurrentTime.str("");

    mMS = _currentMS;

    mS =    mMS/1000;
    mM = mS/60;
    mH = mM/60;

    mS%=60;
    mM%=60;

    QString s = QString("%1").arg(mS, 2, 10, QLatin1Char('0'));
    QString m = QString("%1").arg(mM, 2, 10, QLatin1Char('0'));
    QString h = QString("%1").arg(mH, 2, 10, QLatin1Char('0'));


    mCurrentTime << "[ " << h.toStdString() << " : " << m.toStdString() << " : " << s.toStdString() << " ]";
    return mCurrentTime.str();
}


const int TimeCalc::GetMinutes() const
{
    return mMinutes;
}

std::string TimeCalc::VideoLength(int currentMS)
{
    mVideoLength.str("");

    this->mMSeconds = currentMS;
    this->mSeconds = currentMS/1000;
    this->mMinutes = currentMS / 1000/ 60;
    this->mHours = mM/60;

    mMSeconds %=1000;
    mSeconds %=60;
    mM %= 60;


    QString ms = QString("%1").arg(mMSeconds,3, 10, QLatin1Char('0'));
    QString s  = QString("%1").arg(mSeconds, 2, 10, QLatin1Char('0'));
    QString m  = QString("%1").arg(mMinutes, 2, 10, QLatin1Char('0'));
    QString h  = QString("%1").arg(mHours,   2, 10, QLatin1Char('0'));


    mVideoLength << "Video length = [ " << h.toStdString() << " : " << m.toStdString() << " : " << s.toStdString() << " :: " << ms.toStdString() << " ]";

    return mVideoLength.str();
}
