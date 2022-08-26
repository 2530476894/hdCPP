/*
 * Copyright (c) 2020 WangBin <wbsecg1 at gmail.com>
 * MDK SDK with QOpenGLWidget example
 */
#include "QMDKWidget.h"
#include "mdk/Player.h"
#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QKeyEvent>
#include <QOpenGLContext>
#include <QStringList>
#include <QScreen>

bool av_MediaStatusChanged(mdk::MediaStatus m)
{
    if(m==mdk::NoMedia)
    {
        qDebug()<<"初始状态，非无效";
    }
    else if(m==mdk::Unloaded)
    {
        qDebug()<<"Unloaded";
    }
    else if(m==mdk::Loading)
    {
        qDebug()<<"打开并解析媒体";
    }
    else if(m==mdk::Loaded)
    {
        qDebug()<<"加载并解析媒体,播放器处于停止状态。mediaInfo()现在可用";
    }
    else if(m==mdk::Prepared)
    {
        qDebug()<<"所有磁道都已缓冲并准备好解码帧。未能打开解码器的磁道被忽略.";
    }
    else if(m==mdk::Stalled)
    {
        qDebug()<<"缓冲不足或其他中断（超时、用户中断）";
    }
    else if(m==mdk::Buffering)
    {
        qDebug()<<"Buffering";
    }
    else if(m==mdk::Buffered)
    {
        qDebug()<<"Buffered";
    }
    else if(m==mdk::End)
    {
        qDebug()<<"End";
    }
    else if(m==mdk::Seeking)
    {
        qDebug()<<"Seeking";
    }
    else if(m==mdk::Invalid)
    {
         qDebug()<<"Invalid";
    }

     qDebug()<<"MediaStatus:"<<m;
    return true;
}


bool av_MediaEvent(const mdk::MediaEvent&m)
{
    //出现错误
    if(m.error<0)
    {
        qDebug()<<"播放器的错误提示:"<<QString::fromStdString(m.detail);
    }
    else
    {
       qDebug()<<"播放器的事件提示:"<<QString::fromStdString(m.category);
    }
    return true;
}

void mdk_log(mdk::LogLevel log_type, const char*str)
{
    //qDebug()<<"log_type:"<<log_type<<"str:"<<str;
}


using namespace MDK_NS;
QMDKWidget::QMDKWidget(QWidget *parent, Qt::WindowFlags f)
    : QOpenGLWidget(parent, f)
    , player_(std::make_shared<Player>())
{
    player_->setVideoDecoders({"VT", "VAAPI", "MFT:d3d=11", "DXVA", "MMAL", "AMediaCodec:java=1:copy=0:surface=1:async=0", "FFmpeg"});

    //设置回调: 例如在渲染器中接收到新帧时，将调用该回调
    player_->setRenderCallback([this](void*){
        QMetaObject::invokeMethod(this, "update", Qt::QueuedConnection);
    });

    //设置回调: 事件
    player_->onEvent(av_MediaEvent);

     //获取状态
     //  MediaStatus a=player_->mediaStatus();

    //设置回调: 状态改变
    player_->onMediaStatusChanged(av_MediaStatusChanged);


    //日志重定向
    setLogHandler(mdk_log);
    setLogLevel(mdk::All);

    //设置密匙--向作者申请
    SetGlobalOption("MDK_KEY","xxxxxxxxxxxxx");
}


QMDKWidget::~QMDKWidget()
{
    makeCurrent();
    player_->setVideoSurfaceSize(-1, -1); // cleanup gl renderer resources
}


//设置音量  值：> = 0。1.0是原始音量
void QMDKWidget::setVolume(float value)
{
    player_->setVolume(value);
}

//当前进度 当前播放时间（以毫秒为单位）。相对于媒体的第一个时间戳。即mediaInfo().start_time，通常为0。
int64_t QMDKWidget::position()
{
    return player_->position();
}


//总时间
int64_t QMDKWidget::duration()
{
    return player_->mediaInfo().duration;
}

//设置静音
void QMDKWidget::setMute(bool value)
{
    player_->setMute(value);
}


void QMDKWidget::setPlaybackRate(float value)
{
    //设置播放器播放速度  正常速度是1.0
     player_->setPlaybackRate(value);
}


//旋转视频  逆时针0、90、180、270
//player_->rotate(int degree, void* vo_opaque = nullptr);
void QMDKWidget::setrotate(int degree) //设置旋转
{
    player_->rotate(degree);
}



//功能: 设置解码器
void QMDKWidget::setDecoders(const QStringList &dec)
{
    std::vector<std::string> v;
    foreach (QString d, dec) {
        v.push_back(d.toStdString());
    }
    player_->setVideoDecoders(v);
}

//功能: 设置媒体文件

void QMDKWidget::setMedia(const QString &url)
{
    player_->setMedia(url.toUtf8().constData());
}

void QMDKWidget::play()
{
    setMute(false);
    player_->setState(State::Playing);
}

void QMDKWidget::pause()
{
    setMute(true);
    player_->setState(State::Paused);
}

void QMDKWidget::stop()
{
     setMute(true);
    player_->setState(State::Stopped);
}

bool QMDKWidget::isPaused() const
{
    return player_->state() == State::Paused;
}

bool  QMDKWidget::isStop()const
{
    return player_->state() == State::Stopped;
}

void QMDKWidget::seek(qint64 ms)
{
    player_->seek(ms,SeekFlag::FromStart);
}


void QMDKWidget::snapshot() {
    Player::SnapshotRequest sr{};
    player_->snapshot(&sr, [](Player::SnapshotRequest *_sr, double frameTime) {
        const QString path = QDir::toNativeSeparators(
            QString("%1/%2.png")
                .arg(QCoreApplication::applicationDirPath())
                .arg(frameTime));
        return path.toStdString();
    });
}

void QMDKWidget::resizeGL(int w, int h)
{
    player_->setVideoSurfaceSize(w*devicePixelRatio(), h*devicePixelRatio());
}

void QMDKWidget::paintGL()
{
    player_->renderVideo();
}

/*
工程: QtAV_VideoPlayer
日期: 2021-03-25
作者: DS小龙哥
环境: win10 QT5.12.6 MinGW32
功能: 鼠标双击事件
*/
void QMDKWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    qDebug()<<"鼠标双击";
   // Widget::slot_VideoWidgetEvent(1);
    Q_EMIT ss_VideoWidgetEvent(1);
}

void QMDKWidget::prepreForPreview()
{
    player_->setProperty("continue_at_end", "1");
    player_->setBufferRange(0);
    player_->prepare();
}


void QMDKWidget::wheelEvent(QWheelEvent *event)
{
    if(event->delta()>0)
    {
        qDebug()<<"向前滑动";
        Q_EMIT ss_VideoWidgetEvent(3);
    }
    else
    {
        qDebug()<<"向后滑动";
        Q_EMIT ss_VideoWidgetEvent(4);
    }
    event->accept(); //接收事件
}


void QMDKWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::RightButton)
    {
        Q_EMIT ss_VideoWidgetEvent(2);
    }
}

