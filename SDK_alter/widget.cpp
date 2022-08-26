#include "widget.h"
#include "ui_widget.h"

Widget* Widget::pThis = nullptr;

Widget::Widget(QString filename,QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    pThis=this;

    setWindowFlags(Qt::FramelessWindowHint);

    setAcceptDrops(true);

    setFocusPolicy(Qt::StrongFocus);

    //设置窗口的标题名称
    this->setWindowTitle("视频播放器");

    //获取标题栏的状态
    win_flag=windowFlags();

    //加载样式表
    SetStyle(":/resource/QMDK_VideoPlayer.qss");

    //QMDK初始化
    QMDK_InitConfig();

    //UI界面相关初始化
    UI_InitConfig();

    //如果构造函数传入的视频文件就直接加载
    if(!filename.isEmpty())
    {
        load_video_file(0,filename);
    }

    isPressedWidget=false;

    //设置获取焦点
    ui->AV_player->setFocus();

    //窗口显示在屏幕正中间
    QDesktopWidget *desktop = QApplication::desktop();
    move((desktop->width()-this->width())/2,(desktop->height()-this->height())/2);

    //加载配置
    LoadConfig();

    //设置默认选中的条目
    if(ui->listWidget_videoData->count()>0)
    {
        ui->listWidget_videoData->setCurrentRow(0);

        //加载视频文件
        QTimer::singleShot(200, this, SLOT(load_updateCaption()));
    }
}


Widget::~Widget()
{
    delete ui;
}


void Widget::load_updateCaption()
{
    QString text=ui->listWidget_videoData->item(0)->text();
    qDebug()<<"加载视频文件:"<<text;
    load_video_file(false,text);
}

/*
工程: QtAV_VideoPlayer
日期: 2021-03-25
作者: DS小龙哥
环境: win10 QT5.12.6 MinGW32
功能: 加载样式表
*/
void Widget::SetStyle(const QString &qssFile)
{
    QFile file(qssFile);
    if (file.open(QFile::ReadOnly))
    {
        QByteArray qss=file.readAll();
        qApp->setStyleSheet(qss);
        file.close();
    }
}



//功能: UI界面初始化

void Widget::UI_InitConfig()
{
    //音量滑块范围设置
    ui->horizontalSlider_AudioValue->setMaximum(100);
    ui->horizontalSlider_AudioValue->setMinimum(0);

    //播放速度设置
    ui->MediaSpeedBtn->setCheckable(true);
    m_TimeSpeedGrp = new QActionGroup(this);
    QStringList strSpeedItems;
    strSpeedItems << tr("0.5X") << tr("0.75X") << tr("1.0X") << tr("1.25X") << tr("1.5X");
    float speeds[] = { 0.5,0.75,1.0,1.25,1.5};

    for (int i = 0; i < strSpeedItems.size(); i++)
    {
        QAction *pSpeedItem = m_SpeedMenu.addAction(strSpeedItems.at(i));
        pSpeedItem->setData(QVariant::fromValue(speeds[i]));
        pSpeedItem->setCheckable(true);
        m_TimeSpeedGrp->addAction(pSpeedItem);
        if (i == 2)
        {
            pSpeedItem->setChecked(true);
        }
    }
    connect(m_TimeSpeedGrp, SIGNAL(triggered(QAction *)), this, SLOT(slot_onSetTimeSpeed(QAction *)));


    //安装事件监听器 事件筛选器是接收发送到此对象的所有事件的对象
    ui->horizontalSlider_PlayPosition->installEventFilter(this);
    ui->horizontalSlider_AudioValue->installEventFilter(this);

    //状态信息初始化
    MediaInfo.state=MEDIA_NOLOAD;

    //工具提示信息
    ui->toolButton_load->setToolTip(tr("加载视频,也可以直接将视频文件拖拽到窗口"));

    ui->MediaPrevBtn->setToolTip(tr("快退"));
    ui->MediaPlayBtn->setToolTip(tr("快进"));
    ui->MediaPauseBtn->setToolTip(tr("暂停/继续"));
    ui->MediaSpeedBtn->setToolTip(tr("倍速选择"));
    ui->MediaResetBtn->setToolTip(tr("复位"));
    ui->MediaSnapshotBtn->setToolTip(tr("拍照(保存在程序运行目录下png)"));
    ui->VolumeBtn->setToolTip(tr("静音切换"));
    ui->checkBox_video_list->setToolTip(tr("显示视频列表"));
    ui->toolButton_pgup->setToolTip(tr("播放上一个媒体"));
    ui->toolButton_pgDn->setToolTip(tr("播放下一个媒体"));
    ui->MediaRotateBtn->setToolTip(tr("旋转图像"));
    ui->toolButton_about->setToolTip(tr("关于"));

    //默认不显示
    ui->listWidget_videoData->setVisible(false);

    //播放进度条滑块初始化
    connect(ui->horizontalSlider_PlayPosition, SIGNAL(onLeave()), SLOT(onTimeSliderLeave()));
    connect(ui->horizontalSlider_PlayPosition, SIGNAL(onHover(int,int)), SLOT(onTimeSliderHover(int,int)));
    connect(ui->horizontalSlider_PlayPosition, SIGNAL(sliderMoved(int)), SLOT(seek(int)));
    connect(ui->horizontalSlider_PlayPosition, SIGNAL(sliderPressed()), SLOT(seek()));

    this->setMouseTracking(true);

    /*初始化视频列表的右键菜单*/
    Grp_In_ListWidget = new QActionGroup(this);
    QAction *action_DeleteSelect_In_ListWidget = menu_In_ListWidget.addAction(tr("删除选中"));
    QAction *action_ClearAll_In_ListWidget = menu_In_ListWidget.addAction(tr("删除全部"));
    QAction *action_AddFile_In_ListWidget = menu_In_ListWidget.addAction(tr("添加文件"));
    action_DeleteSelect_In_ListWidget->setData(MENU_DEL_SELECT); //删除选中
    action_ClearAll_In_ListWidget->setData(MENU_DEL_ALL); //删除全部
    action_AddFile_In_ListWidget->setData(MENU_ADD_FILE); //添加文件
    Grp_In_ListWidget->addAction(action_DeleteSelect_In_ListWidget); //添加到分组
    Grp_In_ListWidget->addAction(action_ClearAll_In_ListWidget); //添加到分组
    Grp_In_ListWidget->addAction(action_AddFile_In_ListWidget); //添加到分组
    connect(Grp_In_ListWidget, SIGNAL(triggered(QAction *)), this, SLOT(slot_onListWidgetMenu(QAction *)));

   /*设置QListWidget的contextMenuPolicy属性，不然不能显示右键菜单*/
    ui->listWidget_videoData->setProperty("contextMenuPolicy", Qt::CustomContextMenu);

    /*绑定右键显示菜单：在单击右键之后会执行槽函数， 槽函数中负责弹出右键菜单*/
    connect(ui->listWidget_videoData, SIGNAL(customContextMenuRequested(const QPoint &)),
        this, SLOT(onCustomContextMenuRequested(const QPoint &)));


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeout_update()));


    //图像的旋转方向
    m_RotateGrp = new QActionGroup(this);
    QStringList strDegrees;
    strDegrees << tr("0~") << tr("90~") << tr("180~") << tr("270~");
    int Degrees[] = {0, 90, 180, 270 };
    for (int i = 0; i < strDegrees.size(); i++)
    {
        QAction *pItem = m_RotateMenu.addAction(strDegrees.at(i));
        pItem->setData(QVariant::fromValue(Degrees[i]));
        pItem->setCheckable(true);
        m_RotateGrp->addAction(pItem);
    }
    connect(m_RotateGrp, SIGNAL(triggered(QAction *)), this, SLOT(slot_onMediaRotate(QAction *)));
}




//功能: 事件处理函数

void Widget::onCustomContextMenuRequested(const QPoint &pos)
{
    qDebug()<<"弹出右键菜单";
    QAction *pSelect = menu_In_ListWidget.exec(QCursor::pos());
    if (pSelect == nullptr)
        return;
}



//功能: QMDK初始化配置

void Widget::QMDK_InitConfig()
{
    //SetGlobalOption("MDK_KEY", "10453B8F2140865027CEDD6FDF846D940CA738BE72FE5EE1397DF61714CAAA2A185B72EEC1F781FD5E1FA9BB0AB739E35CCC793F0EBC3FD0182D61EE56E59E08EFBAC47021408D50D8312290207B926B0CA730D91E982991551C8FD75973CAF6B1C4573E7CBF9467F3BAF34F8D9F0A8AE239503BFB1B7B02E4EB0F2121E5D408");

    //关联双击事件
    connect(ui->AV_player, &QMDKWidget::ss_VideoWidgetEvent, this,&Widget::slot_VideoWidgetEvent);

    m_preview=new QMDKWidget(ui->AV_player);

    m_preview->setVisible(false);
}



/*功能: 加载视频文件 flag=0 重新加载文件 flag=1 重新开始播放
QString file_path 这参数可以传入文件名称,因为窗口支持拖放文件进来
返回值: true 成功 false 失败*/

bool Widget::load_video_file(bool flag,QString file_path)
{
    if(flag==false)
    {
        QString filename=file_path;
        if(filename.isEmpty())
        {
             filename=QFileDialog::getOpenFileName(this,"选择播放的视频","D:/",tr("*.mp4 *.wmv *.*"));
        }
        strncpy(video_name,filename.toUtf8().data(),sizeof(video_name));
    }

    //判断文件是否存在
    if(QFileInfo::exists(video_name)==false)
    {
        return false;
    }
    else
    {
        MediaInfo.state=MEDIA_LOAD;
        MediaInfo.mediaName=video_name;
    }

    //设置播放的媒体文件
    ui->AV_player->stop();
    ui->AV_player->setMedia(video_name);
    ui->AV_player->play();

    //预览窗口
    m_preview->stop();
    m_preview->setMedia(video_name);
    m_preview->prepreForPreview();
    m_preview->setMute(true);
    QThread::msleep(100);

    //设置总时间
    ui->label_Total_Time->setText(QTime(0, 0, 0,0).addMSecs(int(ui->AV_player->duration())).toString(QString::fromLatin1("HH:mm:ss:zzz")));

    //设置进度条滑块范围
    ui->horizontalSlider_PlayPosition->setMinimum(0);
    ui->horizontalSlider_PlayPosition->setMaximum(ui->AV_player->duration());

    //每次加载新文件设置播放进度条为0
    ui->horizontalSlider_PlayPosition->setValue(0);

    qDebug()<<"停止原视频";
    ui->AV_player->pause();

    //设置当前播放的视频名称
    QFileInfo info(video_name);
    ui->label_FileName->setText(QString("%1").arg(info.fileName()));

    //设置按钮状态--暂停状态
    ui->MediaPauseBtn->setChecked(true);

    return true;
}



//功能: 加载视频文件

void Widget::on_toolButton_load_clicked()
{
    qDebug()<<"加载视频文件状态:"<<load_video_file(0,"");
}



//功能: 暂停播放

void Widget::on_MediaPauseBtn_clicked()
{
    bool bPause=ui->MediaPauseBtn->isChecked();

    if(bPause == true)
    {
        ui->AV_player->pause();
        timer->stop();
    }
    else
    {
        ui->AV_player->play();
        timer->start();
    }
}



//功能: 重新开始播放

void Widget::on_MediaResetBtn_clicked()
{
    //加重新开始播放
    load_video_file(true,"");
}


//功能: 快退播放

void Widget::on_MediaPrevBtn_clicked()
{
    ui->AV_player->seek(ui->AV_player->position()-10000);
}


//功能: 快进播放

void Widget::on_MediaPlayBtn_clicked()
{
    ui->AV_player->seek(ui->AV_player->position()+10000);
}



//功能: 音量设置

void Widget::on_VolumeBtn_clicked()
{
    bool checked=ui->VolumeBtn->isChecked();
    //静音
    ui->AV_player->setMute(checked);
}




//功能: 音量设置

void Widget::on_horizontalSlider_AudioValue_valueChanged(int value)
{
    ui->AV_player->setVolume(float(value/10.0));
}



//功能: 播放速度设置菜单选择

void Widget::slot_onSetTimeSpeed(QAction *action)
{
    action->setChecked(true);
    ui->MediaSpeedBtn->setToolTip(action->text());
    ui->MediaSpeedBtn->setText(action->text());

    //设置速度  正常速度是1.0
     ui->AV_player->setPlaybackRate(float(action->data().toFloat()));
}


//功能: 点击了速度设置按钮

void Widget::on_MediaSpeedBtn_clicked()
{
    QPoint ptWgt = ui->MediaSpeedBtn->mapToGlobal(QPoint(0, 0));
    ptWgt -= QPoint(10, 180);
    QAction *pSelect = m_SpeedMenu.exec(ptWgt);
    if (pSelect == nullptr)
        return;
}



//功能: 显示菜单

void Widget::slot_onListWidgetMenu(QAction *action)
{
    if (action == nullptr)
        return;
    //得到按下的序号
    MENU_ITEM item = MENU_ITEM(action->data().toInt());

    //删除选中
    if (item == MENU_DEL_SELECT)
    {
        /*获取当前选中的Item*/
        QList<QListWidgetItem*> items = ui->listWidget_videoData->selectedItems();
        if (items.count() > 0)
        {
            foreach(QListWidgetItem* var, items)
            {
                ui->listWidget_videoData->removeItemWidget(var);
                items.removeOne(var);
                delete var;
            }
        }
       qDebug()<<"删除选中";
    }
    //删除全部
    else if(item == MENU_DEL_ALL)
    {
        int counter = ui->listWidget_videoData->count();
        QListWidgetItem *item;
        for(int index = 0;index <counter;index++)
        {
            item = ui->listWidget_videoData->takeItem(0);
            delete item;
        }
        qDebug()<<"删除全部";
    }
    //添加文件
    else if(item == MENU_ADD_FILE)
    {
        QStringList filenamelist=QFileDialog::getOpenFileNames(this,"选择添加的文件","D:/",tr("*.*"));
        if(filenamelist.count()>0) ui->listWidget_videoData->addItems(filenamelist); //添加到列表
        qDebug()<<"添加文件";
    }
}




//功能: 点击了截图按钮

void Widget::on_MediaSnapshotBtn_clicked()
{
    ui->AV_player->snapshot();
}

void Widget:: onTimeSliderHover(int pos, int value)
{
    QPoint gpos=mapToGlobal(ui->horizontalSlider_PlayPosition->pos() + QPoint(pos, ui->AV_player->height()/5 *5));

   // qDebug()<<"onTimeSliderHover(int pos, int value) value"<<value;
    QToolTip::showText(gpos, QTime(0, 0, 0).addMSecs(value).toString(QString::fromLatin1("HH:mm:ss")));
    m_preview->seek(value);
    int w=ui->AV_player->width()/5;
    int h=ui->AV_player->height()/5;
    m_preview->resize(w,h);

    QPoint p;
    p.setY(ui->AV_player->height()/6 *5-30);
    p.setX(pos);
    m_preview->move(p);
    m_preview->show();
}


void Widget::onTimeSliderLeave()
{
    if (m_preview && m_preview->isVisible())
        m_preview->hide();
}


void Widget::seek(int value)
{


    ui->AV_player->seek(value);
    m_preview->seek(value);
    m_preview->resize(ui->AV_player->width()/5,ui->AV_player->height()/5);
    m_preview->show();

    ui->label_current_Time->setText(QTime(0, 0, 0,0).addMSecs(int(value)).toString(QString::fromLatin1("HH:mm:ss:zzz")));
}


void Widget::seek()
{
    qDebug()<<"seek()";
    seek(ui->horizontalSlider_PlayPosition->value());
}


void Widget::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls())
    {
        e->acceptProposedAction();
    }
}

void Widget::dropEvent(QDropEvent *e)
{
    foreach (const QUrl &url, e->mimeData()->urls())
    {
        QString fileName = url.toLocalFile();
        qDebug() << "拖入的文件名称:" << fileName;
        //加载视频文件
        load_video_file(false,fileName);
    }
}


//功能: 双击列表播放视频

void Widget::on_listWidget_videoData_itemDoubleClicked(QListWidgetItem *item)
{
    //加载视频文件
    load_video_file(false,item->text());
}



//功能: 显示视频列表

void Widget::on_checkBox_video_list_clicked(bool checked)
{
    if(checked)
    {
        //显示
        ui->listWidget_videoData->setVisible(true);
    }
    else
    {
        //不显示
        ui->listWidget_videoData->setVisible(false);
    }
}


//功能: 视频事件处理

void Widget::slot_VideoWidgetEvent(int type)
{
    //type =1  双击按下
    //type =2  鼠标左键按下
    //type =3  鼠标滚轮向前
    //type =4  鼠标滚轮向后
    int pos=0;
    switch (type) {
    case 1: //双击事件
        widget_state=!widget_state;
        if(widget_state) //全屏
        {
            showFullScreen();

            ui->listWidget_videoData->setVisible(false);
            ui->widget_tools->setVisible(false);
            ui->frame_time_bar->setVisible(false);
            ui->widget_tite->setVisible(false);

        }
        else //恢复非全屏
        {
           // setWindowFlags(win_flag);
          showNormal();
           if(ui->checkBox_video_list->isChecked())ui->listWidget_videoData->setVisible(true);
           ui->widget_tools->setVisible(true);
           ui->frame_time_bar->setVisible(true);
           ui->widget_tite->setVisible(true);
        }
        break;
    case 2:
        if(ui->AV_player->isPaused())
        {
            ui->AV_player->play();
             timer->start();
             //设置按钮状态--播放状态
             ui->MediaPauseBtn->setChecked(false);
        }
        else
        {
            ui->AV_player->pause();
            timer->stop();
            //设置按钮状态--暂停状态
            ui->MediaPauseBtn->setChecked(true);
        }
        break;
    case 3:  //鼠标滚轮向前
        pos=ui->horizontalSlider_PlayPosition->value();
        pos+=100;
        ui->horizontalSlider_PlayPosition->setValue(pos);
        ui->AV_player->seek(pos);
        ui->label_current_Time->setText(QTime(0, 0, 0,0).addMSecs(int(pos)).toString(QString::fromLatin1("HH:mm:ss:zzz")));
        break;
    case 4: //鼠标滚轮向后
        pos=ui->horizontalSlider_PlayPosition->value();
        pos-=100;
        ui->horizontalSlider_PlayPosition->setValue(pos);
        ui->AV_player->seek(pos);
        ui->label_current_Time->setText(QTime(0, 0, 0,0).addMSecs(int(pos)).toString(QString::fromLatin1("HH:mm:ss:zzz")));
        break;
    }
}



//功能: 关闭窗口

void Widget::on_toolButton_close_clicked()
{
    this->close();
}

//功能:mousePressEvent

void  Widget::mousePressEvent(QMouseEvent *event)
{
    m_lastPos = event->globalPos();
    isPressedWidget = true; // 当前鼠标按下的即是QWidget而非界面上布局的其它控件
}


//功能:mouseMoveEvent

void  Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (isPressedWidget) {
        this->move(this->x() + (event->globalX() - m_lastPos.x()),
                   this->y() + (event->globalY() - m_lastPos.y()));
        m_lastPos = event->globalPos();
    }
}




//功能:mouseReleaseEvent

void  Widget::mouseReleaseEvent(QMouseEvent *event)
{
    m_lastPos = event->globalPos();
    isPressedWidget = false; // 鼠标松开时，置为false
}


void Widget::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Space:
        if(ui->AV_player->isPaused())
        {
             ui->AV_player->play();
             timer->start();
             //设置按钮状态--播放状态
             ui->MediaPauseBtn->setChecked(false);
        }
        else
        {
            ui->AV_player->pause();
            timer->stop();
            //设置按钮状态--暂停状态
            ui->MediaPauseBtn->setChecked(true);
        }
        break;
    }
}


//定时器超时
void Widget::timeout_update()
{
    int64_t pos=ui->AV_player->position();
    //设置进度条的时间
    ui->horizontalSlider_PlayPosition->setValue(int(pos));
    ui->label_current_Time->setText(QTime(0, 0, 0,0).addMSecs(int(pos)).toString(QString::fromLatin1("HH:mm:ss:zzz")));
}


bool Widget::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==ui->horizontalSlider_AudioValue)
    {
        if (event->type()==QEvent::MouseButtonPress)           //判断类型
        {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
            if (mouseEvent->button() == Qt::LeftButton)	//判断左键
            {
               int value = QStyle::sliderValueFromPosition(ui->horizontalSlider_AudioValue->minimum(), ui->horizontalSlider_AudioValue->maximum(), mouseEvent->pos().x(), ui->horizontalSlider_AudioValue->width());
               ui->horizontalSlider_AudioValue->setValue(value);

               //设置音量
               ui->AV_player->setVolume(float(value/10.0));
            }
        }
    }
    return QObject::eventFilter(obj,event);
}

//播放上一个媒体
void Widget::on_toolButton_pgup_clicked()
{
    if(ui->listWidget_videoData->count()<=0)return;
    int row=0;
    row=ui->listWidget_videoData->currentRow(); //当前选中行
     qDebug()<<"row:"<<row;
    if(row>0)
    {
        row--;
        ui->listWidget_videoData->setCurrentRow(row);
    }
    else
    {
        ui->listWidget_videoData->setCurrentRow(ui->listWidget_videoData->count()-1);
    }

    //加载视频文件
    load_video_file(false,ui->listWidget_videoData->currentItem()->text());
}

//播放下一个媒体
void Widget::on_toolButton_pgDn_clicked()
{
    if(ui->listWidget_videoData->count()<=0)return;
    int row=0;
    row=ui->listWidget_videoData->currentRow(); //当前选中行
    qDebug()<<"row:"<<row;
    if(row<ui->listWidget_videoData->count()-1)
    {
        row++;
        ui->listWidget_videoData->setCurrentRow(row);
    }
    else
    {
         ui->listWidget_videoData->setCurrentRow(0);
    }

    //加载视频文件
    load_video_file(false,ui->listWidget_videoData->currentItem()->text());
}


void Widget::slot_onMediaRotate(QAction *action)
{
    action->setChecked(true);
    ui->MediaRotateBtn->setToolTip(action->text());
    ui->AV_player->setrotate(action->data().toInt());
}

void Widget::on_MediaRotateBtn_clicked()
{
    QPoint ptWgt = ui->MediaRotateBtn->mapToGlobal(QPoint(0, 0));
    ptWgt -= QPoint(10, 94);
    QAction *pSelect = m_RotateMenu.exec(ptWgt);
    if (pSelect == nullptr)
        return;
}


//保存配置文件
void Widget::SaveConfig()
{
    /*保存数据到文件,方便下次加载*/
    QString text;
    text=QCoreApplication::applicationDirPath()+"/"+ConfigFile;
    QFile filesrc(text);
    filesrc.open(QIODevice::WriteOnly);
    QDataStream out(&filesrc);

    for(int i=0;i<ui->listWidget_videoData->count();i++)
    {
        QListWidgetItem *item=ui->listWidget_videoData->item(i);
        out << item->text();  //序列化写
    }
    filesrc.flush();
    filesrc.close();
}


//加载配置
void Widget::LoadConfig()
{
    //读取配置文件
    QString text;
    QString data;
    text=QCoreApplication::applicationDirPath()+"/"+ConfigFile;

    //判断文件是否存在
    if(QFile::exists(text))
    {
        QFile filenew(text);
        filenew.open(QIODevice::ReadOnly);
        QDataStream in(&filenew); // 从文件读取序列化数据
        while(!in.atEnd())
        {
            in>>data;
             //文件存在才需要添加进去
             if(QFile::exists(data))
             {
                  ui->listWidget_videoData->addItem(data);
             }
        }
        filenew.close();
    }
}

void Widget::closeEvent(QCloseEvent *event)
{
    int ret = QMessageBox::question(this, tr("重要提示"),
    tr("是否需要关闭窗口?"),
    QMessageBox::Yes | QMessageBox::No);

    if(ret==QMessageBox::Yes)
    {
        SaveConfig();
        event->accept(); //接受事件
    }
    else
    {
        event->ignore(); //清除事件
    }
}


//功能: 关于的提示

void Widget::on_toolButton_about_clicked()
{
    QString text=
    "<html>"
    "<body>"
    "<h1><center>视频播放器功能介绍</center></h1>"
    "<p>1. 基于MDK-SDK接口开发.</p>"
    "<p>这是MDK-SDK的github地址: <a href=\"https://github.com/wang-bin/mdk-sdk/\"> https://github.com/wang-bin/mdk-sdk</a></p>"
    "<p>2. 鼠标左键双击放大.</p>"
    "<p>3. 鼠标右键或者空格键切换暂停与播放.</p>"
    "<p>4. 鼠标放在进度条上可以实现画面预览.</p>"
    "<p>5. 滚动条支持点击跳转或拖动.</p>"
    "<p>6. 支持音量调整、拖动或者点击.</p>"
    "<p>7. 支持静音切换.</p>"
    "<p>8. 支持播放列表添加,选中右下角的复选框，可以打开播放列表。\n播放列表里，鼠标右键可以添加、删除播放文件.</p>"
    "<p>9. 支持退出时保存播放列表,下次打开软件自动加载播放列表.\n下次打开软件时,如果播放列表文件路径存在,将自动选中第一个文件播放.</p>"
    "<p>10. 每次打开视频默认是暂停状态,不会播放，只显示第一个画面.</p>"
    "<p>11. 支持鼠标滚轮滚动预览画面.</p>"
    "</body>"
    "</html>";
    QMessageBox::about(this,"关于",text);
}

