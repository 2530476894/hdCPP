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
    bool eventFilter(QObject *obj, QEvent *event);
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);
    void closeEvent(QCloseEvent *event);

    //截取鼠标事件绘制窗口位置. 因为标题栏隐藏后.窗口是无法拖动的。
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
private slots:
    void load_updateCaption();
    void slot_VideoWidgetEvent(int type);
    void onCustomContextMenuRequested(const QPoint &pos);
    void seek();
    void seek(int);
    void onTimeSliderHover(int pos, int value);
    void onTimeSliderLeave();
    void slot_onSetTimeSpeed(QAction *action);
    void slot_onListWidgetMenu(QAction *);
    void on_toolButton_load_clicked();

    void on_MediaPauseBtn_clicked();

    void on_MediaResetBtn_clicked();

    void on_MediaPrevBtn_clicked();

    void on_MediaPlayBtn_clicked();

    void on_VolumeBtn_clicked();

    void on_horizontalSlider_AudioValue_valueChanged(int value);

    void on_MediaSpeedBtn_clicked();

    void on_MediaSnapshotBtn_clicked();

    void on_listWidget_videoData_itemDoubleClicked(QListWidgetItem *item);

    void on_checkBox_video_list_clicked(bool checked);

    void on_toolButton_close_clicked();

    void timeout_update();
    void on_toolButton_pgup_clicked();

    void on_toolButton_pgDn_clicked();

    void slot_onMediaRotate(QAction *action);
    void on_MediaRotateBtn_clicked();

    void on_toolButton_about_clicked();

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
