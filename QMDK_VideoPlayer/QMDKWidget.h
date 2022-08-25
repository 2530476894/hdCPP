/*
 * Copyright (c) 2020 WangBin <wbsecg1 at gmail.com>
 * MDK SDK with QOpenGLWindow example
 */
#pragma once
#include <QOpenGLWidget>
#include <memory>
#include <QMouseEvent>
#include <QObject>

namespace mdk {
class Player;
}
class QMDKWidget : public QOpenGLWidget
{
      Q_OBJECT
public:
    QMDKWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~QMDKWidget()override;
    void setDecoders(const QStringList& dec);
    void setMedia(const QString& url);
    void play();
    void pause();
    void stop();
    bool isPaused() const;
    bool isStop() const;
    void seek(qint64 ms);
    void snapshot();
    void setPlaybackRate(float value); //播放速度
    void setrotate(int degree);   //设置旋转
    void setMute(bool value);     //设置静音
    void setVolume(float value);  //设置音量
    int64_t duration(); //视频总时间
    int64_t position(); //当前进度
    void prepreForPreview();
signals:
    //type =1  鼠标双击按下
    //type =2  鼠标左键按下
    //type =3  鼠标滚轮向前
    //type =4  鼠标滚轮向后
    void ss_VideoWidgetEvent(int type);
protected:
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void mouseDoubleClickEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *event)override;
    void mousePressEvent(QMouseEvent *e)override;
private:
    std::shared_ptr<mdk::Player> player_;
};
