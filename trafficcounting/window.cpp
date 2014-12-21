#include "window.h"
Window::~Window()
{
    delete mPlayButton;
    delete mFileNameList;
    delete mFileDialogButton;
    delete mSaveFileButton;
    delete mCityInfo;
    delete mStreetInfo;
    delete mFPSInfo;
    delete mFrameInfo;
    delete mResultsList;
    delete mImage;
    delete mImageLabel;
    delete mSlider;
    delete mLCDNum;

    mVidFromFile.release();

}

Window::Window(QWidget *parent): QMainWindow(parent)
{
}

int Window::Init(QString _winName, QSize _winSize)
{
    InitWindow(_winName, _winSize, Qt::WindowNoState);
    ///////
    this->mImageLabel = new QLabel(this);
    this->mImageLabel->move(10,10);
    this->mImageLabel->resize(mImageLabelSize.first, mImageLabelSize.second);

    this->mImage = new QImage("load.jpg");
    this->mImageLabel->setPixmap(QPixmap::fromImage(*mImage));
    this->mImageLabel->show();


    ///////

    this->mTimeOnImg.Initialize({5,20},1,{255, 0,0},2, 1.5);
    this->mPlayButton = new QPushButton("&Play", this);
    this->mPlayButton->move(this->mImageLabel->size().width()+ 12, 2);
    this->mPlayButton->resize(420, this->mPlayButton->size().height());
    this->mPlayButton->setObjectName("mPlayButton");
    this->mPlayButton->setEnabled(false);
    this->mPlayButton->show();

    this->mFileDialogButton = new QPushButton("&Open file", this);
    this->mFileDialogButton->move(this->mImageLabel->size().width()+ 12, 2+ this->mPlayButton->size().height());
    this->mFileDialogButton->setObjectName("mFileDialogButton");
    this->mFileDialogButton->resize( 420, this->mFileDialogButton->size().height());
    this->mFileDialogButton->show();

    this->mSaveFileButton = new QPushButton("&Save image", this);
    this->mSaveFileButton->move(this->mImageLabel->size().width()+ 12, 2+ this->mFileDialogButton->size().height()+mFileDialogButton->pos().y());
    this->mSaveFileButton->resize( 420, this->mSaveFileButton->size().height());
    this->mSaveFileButton->setObjectName("mSaveFileButton");
    this->mSaveFileButton->show();
    ///////

    this->mFileNameList = new QListWidget(this);
    this->mFileNameList->move(this->mImageLabel->size().width()+12 , 2+ this->mSaveFileButton->pos().y()+mSaveFileButton->size().height() );
    this->mFileNameList->resize(420, 200);
    this->mFileNameList->setObjectName("mFileNameList");
    this->mFileNameList->show();

    this->mResultsList = new QListWidget(this);
    this->mResultsList->move(this->mImageLabel->size().width()+12, 2+ this->mFileNameList->pos().y()+mFileNameList->size().height()+5);
    this->mResultsList->resize(420, 150);
    this->mResultsList->show();

    this->mSlider = new QSlider(Qt::Horizontal, this);
    this->mSlider->move( mImageLabel->pos().x(), mImageLabel->size().height()+22);
    this->mSlider->resize(this->mImageLabel->size().width(), 20);
    this->mSlider->setObjectName("mSlider");
    this->mSlider->setDisabled(true);
    this->mSlider->show();

    this->mFrameInfo = new QLabel(this);
    this->mFrameInfo->adjustSize();
    this->mFrameInfo->move( 15, this->mSlider->pos().y() + mSlider->size().height() + 7);
    this->mFrameInfo->hide();

    this->mFPSInfo = new QLabel(this);
    this->mFPSInfo->adjustSize();
    this->mFPSInfo->move( 15, this->mFrameInfo->pos().y() + mFrameInfo->size().height() + 7);
    this->mFPSInfo->hide();

    this->mCityInfo = new QLabel(this);
    this->mCityInfo->adjustSize();
    this->mCityInfo->move( 15, mFPSInfo->pos().y() + mFPSInfo->size().height() + 7);
    this->mCityInfo->hide();

    this->mStreetInfo = new QLabel(this);
    this->mStreetInfo->adjustSize();
    this->mStreetInfo->move( 15, mCityInfo->pos().y() + mCityInfo->size().height() + 7);
    this->mStreetInfo->hide();

    this->mTimeLabel = new QLabel(this);
    this->mTimeLabel->adjustSize();
    this->mTimeLabel->move(15, mStreetInfo->pos().y() + mStreetInfo->size().height()+7);
    this->mTimeLabel->hide();

    this->mButtonsPressedState["mPlayButton"] = false;
    this->mButtonsPressedState["mFileDialogButton"] = false;

    this->mShowContours = new QCheckBox(this);
    this->mShowContours->move(mImageLabel->pos().x() + mImageLabel->size().width()+ 12, mResultsList->pos().y() + mResultsList->size().height()+ 7 );
    this->mShowContours->setChecked(false);
    this->mShowContours->setText("Show contours");
    this->mShowContours->adjustSize();
    this->mShowContours->show();

    this->mFirstMethod = new QRadioButton(this);
    this->mFirstMethod->move(mShowContours->pos().x(), mShowContours->pos().y() + mShowContours->size().height() + 7);
    this->mFirstMethod->setChecked(true);
    this->mFirstMethod->setText("Method one");
    this->mFirstMethod->adjustSize();
    this->mFirstMethod->show();

    this->mSecondMethod = new QRadioButton(this);
    this->mSecondMethod->move(mShowContours->pos().x(), mFirstMethod->pos().y() + mFirstMethod->size().height() + 4);
    this->mSecondMethod->setChecked(false);
    this->mSecondMethod->setText("Method two");
    this->mSecondMethod->adjustSize();
    this->mSecondMethod->show();


    this->mLCDNum = new QLCDNumber(5, this);
    this->mLCDNum->setObjectName("mLCDNum");
    this->mLCDNum->setProperty("mandatoryField", true);

    this->mLCDNum->setStyleSheet("* {background-color: green;color: rgb(255,0,0); text-align: center;}");
    this->mLCDNum->setFont(QFont("Courier"));
    this->mLCDNum->move(this->mImageLabel->pos().x()+ this->mImageLabel->size().width()- this->mLCDNum->size().width(), this->mImageLabel->pos().y());
    this->mLCDNum->setSegmentStyle(QLCDNumber::Flat);
    this->mLCDNum->hide();

    this->mDetectedCarsCount = 0;
    this->mWasPlayed = false;
    this->mTimer = new QTimer(this);

    this->mThreshMax = 200;
    this->mThreshMin = 100;
    this->mBlur = 12;

    TestTrackBars();
    qWarning() << CV_VERSION << "   " << CV_VERSION_MAJOR <<" " <<CV_VERSION_STATUS;

    connect(mTimer, SIGNAL(timeout()), this, SLOT(ShowVideo()));
    connect(mFileNameList,SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(ItemDoubleClicked()));

    pMog2 = cv::createBackgroundSubtractorMOG2(1000);

    mControlPointsHeight = mImgSize.y - 180;
    mPoints.push_back(new cv::Point2i(80, 100));
    mPoints.push_back(new cv::Point2i(80, mImgSize.y - 100));

    mPoints.push_back(new cv::Point2i(mImgSize.x / 2, 100));
    mPoints.push_back(new cv::Point2i(mImgSize.x / 2, mImgSize.y - 100));

    mPoints.push_back(new cv::Point2i(mImgSize.x - 80, 100));
    mPoints.push_back(new cv::Point2i(mImgSize.x - 80, mImgSize.y - 100));

    mPoints.push_back(new cv::Point2i(80, mControlPointsHeight)); //6 left
    mPoints.push_back(new cv::Point2i(mImgSize.x - 80, mControlPointsHeight)); //7 right

    mPoints.push_back(new cv::Point2i(mImgSize.x /2, mControlPointsHeight)); // 8 middle

    QMetaObject::connectSlotsByName(this);

    return 0;
}
void Window::GetInfos(std::string _fileName)
{
    mCityInfo->show();
    mStreetInfo->show();
    mFPSInfo->show();
    mFrameInfo->show();

    mCityText.str("");
    mCityText << "City: " << GetCity(_fileName);
    mCityInfo->setText(QString::fromStdString(mCityText.str()));
    mCityInfo->adjustSize();

    mStreetText.str("");
    mStreetText << "Street: " << GetStreet(_fileName);
    mStreetInfo->setText(QString::fromStdString(mStreetText.str().c_str()));
    mStreetInfo->adjustSize();

    mFirstImage = GetFrameAndFPSAndCount(_fileName,0, mFPS_Info, mFrameC);

    this->mFrameInfo->setText(mFrameC);
    this->mFrameInfo->adjustSize();

    this->mFPSInfo->setText(mFPS_Info);
    this->mFPSInfo->adjustSize();

    GetVideoLength(_fileName);
    this->mTimeLabel->setText(QString::fromStdString( mVideoLength));
    mTimeLabel->show();
    this->mTimeLabel->adjustSize();

    this->mImageLabel->setPixmap(QPixmap::fromImage( cvMatToQImage(mFirstImage)));
}
void Window::ItemDoubleClicked()
{
    if (mOpenedFileName != mFileNameList->currentItem()->text())
    {
        mSavedFrameName << mOpenedFileName.toStdString();
        mPlayButton->setText("&Play");
        const QString _tmpFileNamestr = mFileNameList->currentItem()->text();

        this->mVidFromFile.open( _tmpFileNamestr.toStdString() );
        mOpenedFileName = _tmpFileNamestr;
        mWasPlayed = true;

        GetInfos(mOpenedFileName.toStdString());
        this->mLCDNum->hide();

        this->mSlider->setValue(0);
        this->mSlider->setDisabled(true);
        mFrameCounter = 0;

        if (mWasAtPointLeft) mWasAtPointLeft = false;
        if (mWasAtPointMiddle) mWasAtPointMiddle = false;
        if (mWasAtPointRight) mWasAtPointRight = false;
        mBoundingRect = cv::Rect(0,0,0,0);

        mDetectedCarsCount = 0;
        this->mLCDNum->display(QString::number(mDetectedCarsCount));

        mTimer->stop();

        qWarning() << "Current listitem: " << _tmpFileNamestr.toStdString().c_str() << "\n";
    }
}

void Window::InitWindow(QString _winName, QSize _winSize, Qt::WindowState _winState = Qt::WindowNoState)
{
    this->mWinName = _winName;
    this->mWinSize = _winSize;

    this->resize(mWinSize);
    this->setFixedSize(_winSize);
    this->setWindowTitle(mWinName);
    this->setWindowState(_winState);
}

std::string Window::GetCity(std::string _from)
{
    return _from.substr(0, _from.find_first_of("_"));
}

std::string Window::GetStreet(std::string _from)
{
    return _from.substr(_from.find_first_of("_")+1, _from.find_last_of(".")-_from.find_first_of("_")-1);
}

void Window::keyPressEvent(QKeyEvent *_keypressEvent)
{
    if ((_keypressEvent->key() == Qt::Key_Escape) & (this->windowState() == Qt::WindowNoState))
    {
        mQuit = true;

        this->close();
        exit(0);
    }
    else if ((_keypressEvent->key() == Qt::Key_Escape) & (this->windowState() == Qt::WindowFullScreen))
    {
        mWinSize = { 1124, 600 };
        this->InitWindow(mWinName, mWinSize, Qt::WindowFullScreen);
        this->showNormal();
    }

    if (_keypressEvent->key() == Qt::Key_F)
    {
        if (this->windowState() == Qt::WindowNoState)
        {
            this->setWindowState(Qt::WindowFullScreen);
        }
    }
    if (_keypressEvent->key() == Qt::Key_Space)
    {
        if (mTimer->isActive()) mTimer->stop();
        if (!mTimer->isActive()) mTimer->start();
    }
}

void Window::mouseMoveEvent(QMouseEvent *_mouseEvent)
{
    if (mMousePosPoint.inside(mImageArea))
    {
        if (mPoints[6]->y <= mImgSize.y - 100 && mPoints[6]->y >= 100)
        {
            QVector2D _relativeMousePos = mMousePosition - QVector2D(_mouseEvent->x(),_mouseEvent->y())  ;
            mPoints[6]->y = mPrevControlPointsHeight - _relativeMousePos.y();
            mPoints[7]->y = mPrevControlPointsHeight - _relativeMousePos.y();
            mPoints[8]->y = mPrevControlPointsHeight - _relativeMousePos.y();
        }

        if (mPoints[6]->y < 100)
        {
            mPoints[6]->y = 100;
            mPoints[7]->y = 100;
            mPoints[8]->y = 100;
        }
        if (mPoints[6]->y > mImgSize.y - 100)
        {
            mPoints[6]->y = mImgSize.y - 100;
            mPoints[7]->y = mImgSize.y - 100;
            mPoints[8]->y = mImgSize.y - 100;
        }
    }
}

void Window::mousePressEvent(QMouseEvent *_mouseEvent)
{
    mMousePosition = QVector2D(_mouseEvent->x(), _mouseEvent->y());
    mMousePosPoint = cv::Point2i(_mouseEvent->x(), _mouseEvent->y());

    if (mMousePosPoint.inside(mImageArea))
    {
        mPrevControlPointsHeight = mPoints[6]->y;
        this->setCursor(QCursor(Qt::CursorShape::ClosedHandCursor));
    }
}

void Window::mouseReleaseEvent(QMouseEvent *_mouseEvent)
{
    this->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
}

void Window::on_mSlider_sliderMoved()
{
}


void Window::on_mSlider_sliderPressed()
{
    if (!mSliderPressed)
    {
        if (mWasAtPointLeft) mWasAtPointLeft = false;
        if (mWasAtPointMiddle) mWasAtPointMiddle = false;
        if (mWasAtPointRight) mWasAtPointRight = false;
        mBoundingRect = cv::Rect(0,0,0,0);
        mSliderPressed = true;
    }
}
void Window::on_mSlider_sliderReleased()
{

    mSliderPressed = false;
    this->mFrameCounter = this->mSlider->value()*2;

    this->mSlider->setRange(0, this->mVidFromFile.get(CV_CAP_PROP_FRAME_COUNT)/2);

    mVidFromFile.set(CV_CAP_PROP_POS_FRAMES, this->mFrameCounter );
    mVidFromFile.set(CV_CAP_PROP_POS_FRAMES, this->mFrameCounter );


    mFrameCounter/=2;

}
std::string Window::GetFileNameOrExt(QString _fileDialogFileName, char _fromChar = '/')
{
    if (! _fileDialogFileName.isEmpty())
    {
        std::string _tmpstr = _fileDialogFileName.toStdString();

        qWarning() << ":: " << _tmpstr.substr(_tmpstr.find_last_of(_fromChar)+1).c_str() ;

        return _tmpstr.substr(_tmpstr.find_last_of(_fromChar)+1);
    }
    return "Empty filename!";
}
std::string Window::GetOnlyFileNameWOEXT(std::string _instr)
{
    unsigned int _pos = _instr.find_last_of('.');
    return _instr.substr(0,_pos);
}

void Window::on_mFileDialogButton_clicked()
{
    QString _tmpstr  = QFileDialog::getOpenFileName(this,tr("Open your video"),QDir::currentPath(),tr("Video/Image Files [ *.avi , *.mp4 , *.MP4 , *.JPG *.MTS 4]"));

    mSavedFrameName << GetFileNameOrExt(GetOnlyFileNameWOEXT(_tmpstr.toStdString()).c_str(), '/');
    mLastListItemStr = GetFileNameOrExt(_tmpstr,'/');

    if (!_tmpstr.isEmpty())
    {
        if (mFileNameList->findItems(QString::fromStdString(mLastListItemStr), Qt::MatchExactly).size() == 0)
        {
            new QListWidgetItem(QString::fromStdString(mLastListItemStr), mFileNameList);
            GetInfos(mLastListItemStr);
        }
        this->mPlayButton->setEnabled(true);
    }
    qWarning() << "mLastItem" << mLastListItemStr.c_str();
}
void Window::GetVideoLength(std::string _fileName)
{
    cv::VideoCapture _cap;

    _cap.open(_fileName);
    _cap.set(CV_CAP_PROP_POS_AVI_RATIO,1);
    int milliseconds = _cap.get(CV_CAP_PROP_POS_MSEC);
    mVideoLength = mTimeCalcs.VideoLength(milliseconds);
    _cap.set(CV_CAP_PROP_POS_FRAMES,1);
    _cap.release();
}



void Window::on_mSaveFileButton_clicked()
{


    this->mSavedFrameCounter++;
    this->mSavedFrameName<<'_' << mSavedFrameCounter << ".jpg";

    *this->mImage = this->cvMatToQImage(mCVImage);

    this->mImage->save(mSavedFrameName.str().c_str());
    qWarning() << "Frame saved!" << mSavedFrameName.str().c_str() << "\n";
    this->mSavedFrameName.str("");
    this->mSavedFrameName << GetFileNameOrExt(QString::fromStdString(GetOnlyFileNameWOEXT(mLastListItemStr)), '/');

}

cv::Mat Window::GetFrameAndFPSAndCount(std::string _fileName, unsigned int _pos, QString& _fps, QString& _count)
{
    cv::VideoCapture _cap;
    _cap.open(_fileName);
    cv::Mat _tmpMat;

    if (_cap.isOpened())
    {
        _cap.set(CV_CAP_PROP_POS_FRAMES, _pos);
        _cap.retrieve(_tmpMat);
        cv::resize(_tmpMat, _tmpMat, cv::Size(mImgSize)  );
        _fps = "Source frames per second: " + QString::number(_cap.get(CV_CAP_PROP_FPS));
        if (_fps[0] == '0')
            _fps = QString::fromStdString(_fps.toStdString().substr(0, _fps.toStdString().find_first_of("0")-1) + _fps.toStdString().substr(_fps.toStdString().find_first_of("0")+1));

        _count = "Source frame count: " + QString::number(_cap.get(CV_CAP_PROP_FRAME_COUNT));
        if (_count[0] == '0')
            _count =  QString::fromStdString(_count.toStdString().substr(0, _count.toStdString().find_first_of("0")-1)+ _count.toStdString().substr(_count.toStdString().find_first_of("0")+1));


        _cap.set(CV_CAP_PROP_POS_FRAMES, 1);
        _cap.release();
    }

    if (!_tmpMat.empty())
    {
        return _tmpMat;
    }

}

void Window::on_mPlayButton_clicked()
{
    if (mPlayButton->text() == "&Play")
    {
        if ( (mFileNameList->hasFocus() && !mWasPlayed) )
        {
            const QString _tmpFileNamestr = mFileNameList->currentItem()->text();

            this->mVidFromFile.open( _tmpFileNamestr.toStdString() );
            mOpenedFileName = _tmpFileNamestr;
            mWasPlayed = true;

            qWarning() << "Current listitem: " << _tmpFileNamestr.toStdString().c_str() << "\n";
        }
        else if (! mFileNameList->hasFocus() && !mWasPlayed)
        {
            this->mVidFromFile.open(mLastListItemStr);
            mOpenedFileName = QString::fromStdString(mLastListItemStr);
            qWarning() << "Current listitem_: " << mLastListItemStr.c_str() << "\n";
            mWasPlayed = true;

        }
        this->mSlider->setRange(0, this->mVidFromFile.get(CV_CAP_PROP_FRAME_COUNT)/2);

        if (!mVidFromFile.isOpened())
        {
            this->setWindowTitle("Error: VideoFileNotOpened!");
        }

        this->mPlayButton->setText("&Pause");
        this->mSlider->setEnabled(true);

        cv::waitKey(1000 / mVidFromFile.get(CV_CAP_PROP_FPS)*2);

        mTimer->start(1000 / mVidFromFile.get(CV_CAP_PROP_FPS)*2); //84
        if (!mWasPlayed)
        {
            this->mVidFromFile.set(CV_CAP_PROP_POS_FRAMES, 1);
        }
        this->mLCDNum->show();

        mPlayButton->setText("&Pause");
    }
    else if (mPlayButton->text() == "&Pause")
    {
        mTimer->stop();
        this->mLCDNum->show();

        this->mPlayButton->setText("&Play");
    }
}

int Window::InitTimeCalcByExt(const char *_fileExt)
{
    if ( !strcmp(_fileExt, "avi"))
    {
        qWarning() << "avi";

        return 25; // fg testing
    }
    if ( !strcmp(_fileExt, "AVI"))
    {
        qWarning() << "AVI";

        return 25;
    }
    if ( !strcmp(_fileExt, "mp4"))
    {
        qWarning() << "mp4";
        return mVidFromFile.get(CV_CAP_PROP_FPS);
    }
    if ( !strcmp(_fileExt, "MP4"))
    {
        qWarning() << "MP4";

        return mVidFromFile.get(CV_CAP_PROP_FPS);
    }
    if ( !strcmp(_fileExt, "MTS"))
    {
        qWarning() << "MTS";

        return mVidFromFile.get(CV_CAP_PROP_FPS);
    }
    qWarning() << "NoneOfFileTypes";

    return 30;
}
void Window::TestTrackBars()
{
    cv::namedWindow(mTrackBarWindowName, 0);
    cv::createTrackbar("ThreshMin", mTrackBarWindowName, &mThreshMin, 255, 0 , 0);
    cv::createTrackbar("ThreshMax", mTrackBarWindowName, &mThreshMax, 255, 0, 0);
    cv::createTrackbar("Blur", mTrackBarWindowName, &mBlur, 35, 0, 0);
}
cv::Mat Window::ProcessImage(cv::Mat& _frameToProcess)
{

    cv::resize(_frameToProcess, _frameToProcess, cv::Size(mImgSize)  );
    cv::cvtColor(_frameToProcess, mGrayImgO, cv::COLOR_BGR2GRAY);

    mTimeOnImg.WriteOnImage(mTimeCalcs.CurrentTime(mVidFromFile.get(CV_CAP_PROP_POS_MSEC)), _frameToProcess);
    mVidFromFile.read(mCVImage1);

    cv::resize(mCVImage1, mCVImage1, cv::Size(mImgSize)  );

    cv::cvtColor(mCVImage1, mGrayImg1, cv::COLOR_BGR2GRAY);

    cv::absdiff(mGrayImgO, mGrayImg1, mDiffOfImgs);

    cv::threshold(mDiffOfImgs, mThreshImg, 25, 255, cv::THRESH_BINARY);

    cv::blur(mThreshImg,mThreshImg, cv::Size(mBlur, mBlur));
    cv::threshold(mThreshImg, mThreshImg, mThreshMin, mThreshMax, cv::THRESH_BINARY);

    //pMog2->apply(_frameToProcess,fgMaskMOG2);
    SearchForObject(mThreshImg, _frameToProcess);

    cv::line(_frameToProcess, *mPoints[6], *mPoints[7], cv::Scalar(255,0,0),2,cv::LINE_4);

    return _frameToProcess;
}
void Window::SearchForObject(cv::Mat& _thresholdImage, cv::Mat &_CamImage)
{
    cv::findContours(_thresholdImage, mContours, mHierarchy, CV_RETR_TREE , CV_CHAIN_APPROX_SIMPLE);
    mHullPts.resize(mContours.size());
    for( size_t i = 0; i < mContours.size(); i++ )
    {
        cv::convexHull( cv::Mat(mContours[i]), mHullPts[i], false );
    }
    double mContAr = 0;
    int pos = 0;

    if (mContours.size()>0)
        for( size_t i = 0; i< mContours.size(); i++ )
        {
            if (cv::contourArea(mContours[i]) > mContAr)
            {
                mContAr = cv::contourArea(mContours[i]);
                pos = i;
                mBoundingRect = cv::boundingRect(mContours[i]);
            }
        }

    if (mPoints[6]->inside(mBoundingRect))
    {
        cv::line(_CamImage, *mPoints[0], *mPoints[1], cv::Scalar(0,0,255),2); // left
        mWasAtPointLeft = true;
    }
    else if (!mPoints[6]->inside(mBoundingRect))
    {
        cv::line(_CamImage, *mPoints[0], *mPoints[1], cv::Scalar(0,255,0),2);
    }

    if (mPoints[8]->inside(mBoundingRect))
    {
        cv::line(_CamImage, *mPoints[2], *mPoints[3], cv::Scalar(0,0,255),2); // middle
        mWasAtPointMiddle = true;

    }
    else if (!mPoints[8]->inside(mBoundingRect))
    {
        cv::line(_CamImage, *mPoints[2], *mPoints[3], cv::Scalar(0,255,0),2);
    }

    if (mPoints[7]->inside(mBoundingRect))
    {
        cv::line(_CamImage, *mPoints[4], *mPoints[5], cv::Scalar(0,0,255),2); // right
        mWasAtPointRight = true;

    }
    else if (!mPoints[7]->inside(mBoundingRect))
    {
        cv::line(_CamImage, *mPoints[4], *mPoints[5], cv::Scalar(0,255,0),2);
    }

    if (mWasAtPointLeft && mWasAtPointMiddle && mWasAtPointRight && mContAr > 3000)
    {
        mDetectedCarsCount++;
        this->mLCDNum->display(QString::number(mDetectedCarsCount));

        mWasAtPointLeft = false;
        mWasAtPointMiddle = false;
        mWasAtPointRight = false;

    }

    if (mShowContours->isChecked())
    {
        if (mContAr > 3000)
        {
            //cv::rectangle(_CamImage, mBoundingRect, cv::Scalar(255,0,0),2);
            cv::drawContours( _CamImage, mHullPts, pos, cv::Scalar(255,255,255), 2, 8, std::vector<cv::Vec4i>(), 0, cv::Point() );
        }
    }
}
QImage Window::cvMatToQImage(cv::Mat _frame)
{
    switch( _frame.type())
    {
    case CV_8UC4:
    {
        QImage _tmpimg (_frame.data, _frame.cols, _frame.rows, _frame.step, QImage::Format_RGB32);

        return _tmpimg;
    }
    case CV_8UC3:
    {
        QImage _tmpimg(_frame.data, _frame.cols, _frame.rows, _frame.step, QImage::Format_RGB888);

        return _tmpimg.rgbSwapped();
    }
    case CV_8UC1:
    {
        QImage _tmpimg(_frame.data, _frame.cols, _frame.rows, _frame.step, QImage::Format_Indexed8);
        return _tmpimg;
    }
    default:
        qWarning() << "Invalid cv::Mat type" << _frame.type();
        break;
    }
    return QImage();
}

void Window::ShowVideo()
{
    if (!mSliderPressed)
    {
        do
        {
            mVidFromFile.read(mCVImage);
            if (!mCVImage.empty())
            {
                if (mFrameCounter < (mVidFromFile.get(CV_CAP_PROP_FRAME_COUNT)/2 - 2))
                {
                    // qWarning () << "Processing image: " << mFrameCounter;
                    this->mFrameCounter++;
                    this->mSlider->setSliderPosition(mFrameCounter);

                    this->mImageLabel->setPixmap(QPixmap::fromImage( cvMatToQImage(ProcessImage(mCVImage))));
                }
                else
                {
                    mResultText.str("");
                    mResultText << mOpenedFileName.toStdString() << " -> detected cars: " << mDetectedCarsCount << " | CPM: "
                                << (mTimeCalcs.GetMinutes() > 1 ? static_cast<double>(mDetectedCarsCount)/ mTimeCalcs.GetMinutes(): mDetectedCarsCount / mTimeCalcs.GetMinutesD() );
                    mTimeCalcs.Reset();

                    qWarning () << "Restart, detected cars: " << mDetectedCarsCount;
                    new QListWidgetItem(tr(mResultText.str().c_str()), mResultsList);
                    mDetectedCarsCount = 0;
                    this->mLCDNum->display(QString::number(mDetectedCarsCount));

                    mFrameCounter = 0;
                    mVidFromFile.set(CV_CAP_PROP_POS_FRAMES, 1);
                }
            }
            else
            {
                qWarning () << "Empty image at: " << mFrameCounter;
                break;
            }
        } while (mFrameCounter  > ( mVidFromFile.get(CV_CAP_PROP_FRAME_COUNT)/2 - 2));
    }
}

QVector<QString> Window::GetFileNames()
{
    return mFileNames;
}


