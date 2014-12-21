#ifndef VIDEOFROMFILE_H
#define VIDEOFROMFILE_H

#include "window.h"

class VideoFromFile
{

public:
    VideoFromFile(int _winCount, QVector<QString> _winNames);
    ~VideoFromFile();
    int Initialize(int _winCount, QVector<QString> _winNames);
    void Play();
private:

    QVector <Window*> mWindows;
    QVector <QString> mWinNames;
    void ShowImage();

    int mWinCount;


};

#endif // VIDEOFROMFILE_H
