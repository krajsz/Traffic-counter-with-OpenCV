#include "font.h"

Font::Font(std::pair<int, int> _startCoord, int _fontFace, BGRdColor _FontColor, int _thickness, double _fontScale)
{
    Initialize(_startCoord, _fontFace, _FontColor, _thickness, _fontScale);
}
Font::Font()
{
}

Font::~Font()
{
}

void Font::WriteOnImage(std::string _Text, cv::Mat _Image)
{
    cv::putText(_Image, _Text, mStartCoord, mFontFace, mFontScale, mColor, mThickness);
}
int Font::Initialize(std::pair<int, int> _startCoord, int _fontFace, BGRdColor _FontColor, int _thickness, double _fontScale)
{
    this->mFontFace = _fontFace;
    this->mStartCoord.x = _startCoord.first;
    this->mStartCoord.y = _startCoord.second;
    this->mFontScale = _fontScale;

    this->mColor = cv::Scalar(_FontColor._r,_FontColor._g, _FontColor._b);
    this->mThickness = _thickness;

    return 0;
}

void Font::GetInfos()
{
    /*std::cout << "Font infos: " << "\n" <<
                  "     StartCoord: " << this->mStartCoord << "\n" <<
                  "     Fontface: " << this->mFontFace << "\n" <<
                  "     Color: " << this->mColor << "\n";*/
}
