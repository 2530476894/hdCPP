#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QFile>
#include <QFileDialog>
#include <QActionGroup>
#include <QMenu>
#include <QApplication>
#include <QClipboard>
#include <QStyle>
#include <QToolTip>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QKeyEvent>
#include "QMDKWidget.h"
#include <QThread>
#include <QTimer>
#include <QDebug>
#include <iostream>
#include <QDesktopWidget>
#include <QTime>
#include <QOpenGLWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE


enum MENU_ITEM
{
    MENU_COPY_CLIPBOARD = 0,
    MENU_SAVE_FILE_SYSTEM,
    MENU_EDIT_SUBTITLE,
    MENU_SHOW_SUBTITLE,
    MENU_PLAY_NARRATOR,
    MENU_DEL_SELECT,
    MENU_DEL_ALL,
    MENU_ADD_FILE,
};

enum MEDIA_STATE
{
    MEDIA_NOLOAD,//视频未加载
    MEDIA_LOAD,//视频加载
};

//媒体状态信息
struct MediaStateInfo
{
    MEDIA_STATE state;
    QString mediaName;
};

//配置文件名称
#define ConfigFile "cofnig.ini"

class Widget : public QWidget
{
    Q_OBJECT

public:
    bool widget_state=false; //true表示全屏  false表示非全屏

    Widget(QString filename=nullptr,QWidget *parent = nullptr);
    ~Widget();

    //加载样式表
    void SetStyle(const QString &qssFile);
    //UI界面初始化
    void UI_InitConfig();
    //QMDK初始化设置
    void QMDK_InitConfig();
    //加载视频文件
    bool load_video_file(bool flag, QString file_path);
    //保存配置文件
    void SaveConfig();
    //加载配置
    void LoadConfig();
 signals:
    void s_pause_state(bool pause_state,qint64 current_time);
protected:
    bool eventFilter(QObject *obj, QEvent *event);//判断鼠标事件的过滤器
    void dragEnterEvent(QDragEnterEvent *e);//拖进视频
    void dropEvent(QDropEvent *e);//放入视频
    void closeEvent(QCloseEvent *event);//关闭事件
    void mouseReleaseEvent(QMouseEvent *event);//鼠标释放
    void mouseMoveEvent(QMouseEvent *event);//鼠标移动
    void mousePressEvent(QMouseEvent *event);//鼠标点击
    void keyPressEvent(QKeyEvent *event); //键盘事件

//slots 自动添加 on_对象命_信号（）槽函数声明
private slots:
    void load_updateCaption(); //加载视频
    void slot_VideoWidgetEvent(int type);//鼠标操作视频界面函数槽
    void onCustomContextMenuRequested(const QPoint &pos);//右键菜单
    void seek();//播放位置
    void seek(int);//进度寻址
    void onTimeSliderHover(int pos, int value);//进度条拖拽
    void onTimeSliderLeave();//进度隐藏
    void slot_onSetTimeSpeed(QAction *action);//倍速播放
    void slot_onListWidgetMenu(QAction *);//显示菜单
    void on_toolButton_load_clicked();//加载视频文件
    void on_MediaPauseBtn_clicked();//暂停槽函数
    void on_MediaResetBtn_clicked();//复位槽函数
    void on_MediaPrevBtn_clicked();//快退槽函数
    void on_MediaPlayBtn_clicked();//快进槽函数
    void on_VolumeBtn_clicked();//静音设置槽函数
    void on_horizontalSlider_AudioValue_valueChanged(int value);//滑轨音量设置槽函数
    void on_MediaSpeedBtn_clicked();//倍速播放槽函数
    void on_MediaSnapshotBtn_clicked();//截图槽函数
    void on_listWidget_videoData_itemDoubleClicked(QListWidgetItem *item);//列表播放槽函数
    void on_checkBox_video_list_clicked(bool checked);//列表显示槽函数
    void on_toolButton_close_clicked();//关闭槽函数
    void timeout_update();//进度超时槽函数
    void on_toolButton_pgup_clicked();//播放上一个视频槽函数
    void on_toolButton_pgDn_clicked();//播放下一个视频槽函数
    void slot_onMediaRotate(QAction *action);//旋转视频槽函数
    void on_MediaRotateBtn_clicked();//槽函数
    void on_toolButton_about_clicked();//提示槽函数

private:
    Ui::Widget *ui;
    struct MediaStateInfo MediaInfo;

    QActionGroup *m_TimeSpeedGrp;
    QMenu			m_SpeedMenu;

    QActionGroup	*m_RotateGrp;
    QMenu			m_RotateMenu;

    //视频名称
    char video_name[1024]; //视频名称

    //视频列表的右键菜单
    QActionGroup *Grp_In_ListWidget;
    QMenu	menu_In_ListWidget;

    Qt::WindowFlags  win_flag;

    bool isPressedWidget;
    QPoint m_lastPos;

    QTimer *timer;

    static Widget *pThis;

    QMDKWidget *m_preview;
};
#endif // WIDGET_H
