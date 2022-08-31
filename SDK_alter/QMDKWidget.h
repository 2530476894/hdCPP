#pragma once
#include <QOpenGLWidget>
#include <memory>
#include <QMouseEvent>
#include <QObject>

namespace mdk {
class Player;
}
class QMDKWidget : public QOpenGLWidget//构造函数 创建QMDKWidget类和对象QWidget 并经行初始化
{
      Q_OBJECT //实现信号和槽机制
public:
    QMDKWidget(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    ~QMDKWidget()override;
    void setDecoders(const QStringList& dec); //设置解码器
    void setMedia(const QString& url); //设置媒体文件
    void play(); //播放
    void pause(); //暂停
    void stop(); //停止
    bool isPaused() const; //判断状态
    bool isStop() const; //判断状态
    void seek(qint64 ms);//进度条查找
    void snapshot(); //截图
    void setPlaybackRate(float value); //播放速度
    void setrotate(int degree);//设置旋转
    void setMute(bool value);//设置静音
    void setVolume(float value);//设置音量
    int64_t duration(); //视频总时间
    int64_t position(); //当前进度
    void prepreForPreview();//复位
signals:
    //type =1  鼠标双击按下
    //type =2  鼠标左键按下
    //type =3  鼠标滚轮向前
    //type =4  鼠标滚轮向后
    void ss_VideoWidgetEvent(int type);
protected:
    void resizeGL(int w, int h) override;//页面大小
    void paintGL() override;//渲染
    void mouseDoubleClickEvent(QMouseEvent *e) override;//双击槽
    void wheelEvent(QWheelEvent *event)override;//滚轮槽
    void mousePressEvent(QMouseEvent *e)override;//单击槽
private:
    std::shared_ptr<mdk::Player> player_;
};
