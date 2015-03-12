#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVector>
#include <QListWidget>
#include <QKeyEvent>
#include <QDir>
#include <QFileDialog>
#include <QMouseEvent>
#include <QImage>
#include <QLabel>
#include <QTimer>
#include <QPainter>
#include <QSlider>
#include <QtDebug>
#include <QCheckBox>
#include <QLCDNumber>
#include <QRadioButton>
#include <array>
#include <ostream>

#include "fps.h"
#include "timecalc.h"

class Window: public QMainWindow
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);
    ~Window();
    int Init(QString _winName, QSize _winSize);
    QVector<QString> GetFileNames();

private:
    void InitWindow(QString _winName, QSize _winSize, Qt::WindowState _winState);

    QImage cvMatToQImage(cv::Mat _frame);

    void keyPressEvent(QKeyEvent* _keypressEvent);
    void mouseMoveEvent(QMouseEvent* _mouseEvent);
    void mousePressEvent(QMouseEvent* _mouseEvent);
    void mouseReleaseEvent(QMouseEvent * _mouseEvent);

    void GetVideoLength(std::string _fileName);
    void SearchForObject(cv::Mat &_thresholdImage, cv::Mat &_CamImage);
    void TestTrackBars();
    bool IsBetween(double _min, double _max, double _value);
    double CalculateBrightness(cv::Mat _CamImage);


    int InitTimeCalcByExt(const char * _fileExt);

    cv::Mat ProcessImage(cv::Mat &_frameToProcess);
    cv::Mat GetFrameAndFPSAndCount(std::string _fileName, unsigned int _pos, QString &_fps, QString &_count);
    std::string GetFileNameOrExt(QString _fileDialogFileName, char _fromChar);
    std::string GetOnlyFileNameWOEXT(std::string _instr);
    std::string GetCity  (std::string _from);
    std::string GetStreet(std::string _from);

    QPushButton* mPlayButton;
    QPushButton* mFileDialogButton;
    QPushButton* mSaveFileButton;


    QSize mWinSize { 1124, 600 };
    QString mWinName { "Test" };
    QString mFrameC;
    QString mFPS_Info;
    QString mOpenedFileName;
    QImage* mImage;

    QLabel* mImageLabel;
    QLabel* mFrameInfo;
    QLabel* mFPSInfo;
    QLabel* mCityInfo;
    QLabel* mStreetInfo;
    QLabel* mTimeLabel;
    QLabel* mBrightnessInfo;

    QCheckBox* mShowContours;

    QRadioButton* mFirstMethod;
    QRadioButton* mSecondMethod;



    QVector2D mMousePosition;
    QLCDNumber* mLCDNum;
    int mControlPointsHeight { 0 };
    int mPrevControlPointsHeight;

    QTimer* mTimer;

    QSlider* mSlider;
    QListWidget *mFileNameList;
    QListWidget *mResultsList;

    QKeyEvent* mEvent;
    QVector<QString> mFileNames;

    bool mQuit = false;
    bool mStarted = false;
    bool mSliderPressed = false;

    int mThreshMin;
    int mThreshMax;
    int mBlur;
    double mBrightnessOfImage;

    std::string mLastListItemStr;
    std::string mSelectedListItem;

    QMap <QString, bool> mButtonsPressedState;

    const QPair <int, int> mImageLabelSize { 640, 480 };
    ////////
    cv::VideoCapture mVidFromFile;
    cv::VideoCapture mForSecondImage;

    cv::Mat mFirstImage;

    cv::Mat mCVImage;
    cv::Mat mCVImage1;

    cv::Mat mGrayImgO;
    cv::Mat mGrayImg1;

    cv::Mat mThreshImg;

    cv::Mat mDiffOfImgs;

    const cv::Rect mImageArea = cv::Rect(10,10,640,480);
    cv::Point mMousePosPoint;
    std::vector< std::vector<cv::Point> > mContours;
    std::vector< std::vector<cv::Point> > mHullPts;
    std::vector<cv::Vec4i> mHierarchy;

    cv::Rect mBoundingRect;
    Font mTimeOnImg;

    bool mWasPlayed;
    TimeCalc mTimeCalcs;
    int mFrameCounter { 0 };
    unsigned int mDetectedCarsCount {0};
    int mSavedFrameCounter { 0 };
    std::stringstream mSavedFrameName;
    std::stringstream mResultText;
    std::stringstream mCityText;
    std::stringstream mStreetText;
    std::string mVideoLength;
    double mCarsPerMinutes {0};
    int mMinutesOfVideo {0};

    void GetInfos(std::string _fileName);

    const cv::Point mImgSize = cv::Point(640, 480);
    //////////

    cv::Mat fgMaskMOG2;

    cv::Ptr<cv::BackgroundSubtractorMOG2> pMog2;

    QVector<cv::Point2i*> mPoints;

    const std::string mTrackBarWindowName = "TestTrackbars";
    bool mWasAtPointLeft = false;
    bool mWasAtPointMiddle = false;
    bool mWasAtPointRight = false;



private slots:
    void ShowVideo();
    void on_mFileDialogButton_clicked();
    void on_mPlayButton_clicked();
    void on_mSaveFileButton_clicked();
    void on_mSlider_sliderMoved();
    void on_mSlider_sliderPressed();
    void on_mSlider_sliderReleased();
    void ItemDoubleClicked();
};

#endif // WINDOW_H
