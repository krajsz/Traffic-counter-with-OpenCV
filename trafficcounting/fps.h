#ifndef FPS_H
#define FPS_H

#include "font.h"

class FPS
{
public:
    FPS();
    ~FPS();
    void Start();
    void Calculate();
    void Initialise();
    double GetFPS();
private:
    double mFPS;
    int64 mStart;

};

#endif // FPS_H
