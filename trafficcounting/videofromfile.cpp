#include "videofromfile.h"

VideoFromFile::VideoFromFile(int _winCount, QVector<QString> _winNames)
{
    Initialize(_winCount, _winNames);
}
VideoFromFile::~VideoFromFile()
{

}
void VideoFromFile::Play()
{
    ShowImage();
}

void VideoFromFile::ShowImage()
{
    for (auto it: mWindows)
    {
        it->show();
    }
}

int VideoFromFile::Initialize(int _winCount, QVector<QString> _winNames)
{
    this->mWinCount = _winCount;
    this->mWinNames = _winNames;

    if (mWinCount != mWinNames.size())
    {
        exit(1);
    }
    for (int it = 0; it < _winCount; it++)
    {
        Window*   _tmpwind = new Window();

        _tmpwind->Init( _winNames[it], {1124, 650});
        mWindows.push_back(_tmpwind);
    }
    return 0;
}

