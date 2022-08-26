/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qmdkwidget.h"
#include "slider.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_tite;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_FileName;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *toolButton_close;
    QHBoxLayout *horizontalLayout_8;
    QMDKWidget *AV_player;
    QListWidget *listWidget_videoData;
    QFrame *frame_time_bar;
    QHBoxLayout *horizontalLayout_7;
    Slider *horizontalSlider_PlayPosition;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_current_Time;
    QLabel *label_3;
    QLabel *label_Total_Time;
    QWidget *widget_tools;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *toolButton_load;
    QSpacerItem *horizontalSpacer_6;
    QToolButton *MediaPrevBtn;
    QSpacerItem *horizontalSpacer_7;
    QToolButton *MediaPauseBtn;
    QSpacerItem *horizontalSpacer_8;
    QToolButton *MediaPlayBtn;
    QSpacerItem *horizontalSpacer_9;
    QToolButton *MediaResetBtn;
    QSpacerItem *horizontalSpacer_10;
    QToolButton *toolButton_pgup;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *toolButton_pgDn;
    QSpacerItem *horizontalSpacer_4;
    QToolButton *VolumeBtn;
    QSlider *horizontalSlider_AudioValue;
    QSpacerItem *horizontalSpacer_5;
    QToolButton *MediaSpeedBtn;
    QSpacerItem *horizontalSpacer_14;
    QToolButton *MediaRotateBtn;
    QSpacerItem *horizontalSpacer_12;
    QToolButton *MediaSnapshotBtn;
    QSpacerItem *horizontalSpacer_11;
    QToolButton *toolButton_about;
    QSpacerItem *horizontalSpacer_13;
    QCheckBox *checkBox_video_list;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(833, 502);
        verticalLayout_3 = new QVBoxLayout(Widget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget_tite = new QWidget(Widget);
        widget_tite->setObjectName(QString::fromUtf8("widget_tite"));
        widget_tite->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_5 = new QHBoxLayout(widget_tite);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(5, 5, 5, 5);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_FileName = new QLabel(widget_tite);
        label_FileName->setObjectName(QString::fromUtf8("label_FileName"));

        horizontalLayout->addWidget(label_FileName);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        toolButton_close = new QToolButton(widget_tite);
        toolButton_close->setObjectName(QString::fromUtf8("toolButton_close"));

        horizontalLayout->addWidget(toolButton_close);


        horizontalLayout_5->addLayout(horizontalLayout);


        verticalLayout_3->addWidget(widget_tite);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        AV_player = new QMDKWidget(Widget);
        AV_player->setObjectName(QString::fromUtf8("AV_player"));

        horizontalLayout_8->addWidget(AV_player);

        listWidget_videoData = new QListWidget(Widget);
        listWidget_videoData->setObjectName(QString::fromUtf8("listWidget_videoData"));
        listWidget_videoData->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_8->addWidget(listWidget_videoData);


        verticalLayout_3->addLayout(horizontalLayout_8);

        frame_time_bar = new QFrame(Widget);
        frame_time_bar->setObjectName(QString::fromUtf8("frame_time_bar"));
        frame_time_bar->setMaximumSize(QSize(16777215, 30));
        frame_time_bar->setFrameShape(QFrame::StyledPanel);
        frame_time_bar->setFrameShadow(QFrame::Raised);
        horizontalLayout_7 = new QHBoxLayout(frame_time_bar);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(5, 5, 5, 0);
        horizontalSlider_PlayPosition = new Slider(frame_time_bar);
        horizontalSlider_PlayPosition->setObjectName(QString::fromUtf8("horizontalSlider_PlayPosition"));
        horizontalSlider_PlayPosition->setOrientation(Qt::Horizontal);

        horizontalLayout_7->addWidget(horizontalSlider_PlayPosition);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(9, 0, 9, -1);
        label_current_Time = new QLabel(frame_time_bar);
        label_current_Time->setObjectName(QString::fromUtf8("label_current_Time"));
        label_current_Time->setStyleSheet(QString::fromUtf8("background-color:#242526;\n"
"	color:#9A9A9A;"));

        horizontalLayout_6->addWidget(label_current_Time);

        label_3 = new QLabel(frame_time_bar);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("background-color:#242526;\n"
"	color:#9A9A9A;"));

        horizontalLayout_6->addWidget(label_3);

        label_Total_Time = new QLabel(frame_time_bar);
        label_Total_Time->setObjectName(QString::fromUtf8("label_Total_Time"));
        label_Total_Time->setStyleSheet(QString::fromUtf8("background-color:#242526;"));

        horizontalLayout_6->addWidget(label_Total_Time);


        horizontalLayout_7->addLayout(horizontalLayout_6);


        verticalLayout_3->addWidget(frame_time_bar);

        widget_tools = new QWidget(Widget);
        widget_tools->setObjectName(QString::fromUtf8("widget_tools"));
        widget_tools->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_3 = new QHBoxLayout(widget_tools);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(5, 5, 5, 5);
        toolButton_load = new QToolButton(widget_tools);
        toolButton_load->setObjectName(QString::fromUtf8("toolButton_load"));

        horizontalLayout_3->addWidget(toolButton_load);

        horizontalSpacer_6 = new QSpacerItem(20, 24, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);

        MediaPrevBtn = new QToolButton(widget_tools);
        MediaPrevBtn->setObjectName(QString::fromUtf8("MediaPrevBtn"));

        horizontalLayout_3->addWidget(MediaPrevBtn);

        horizontalSpacer_7 = new QSpacerItem(20, 24, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_7);

        MediaPauseBtn = new QToolButton(widget_tools);
        MediaPauseBtn->setObjectName(QString::fromUtf8("MediaPauseBtn"));
        MediaPauseBtn->setCheckable(true);
        MediaPauseBtn->setChecked(true);

        horizontalLayout_3->addWidget(MediaPauseBtn);

        horizontalSpacer_8 = new QSpacerItem(20, 24, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);

        MediaPlayBtn = new QToolButton(widget_tools);
        MediaPlayBtn->setObjectName(QString::fromUtf8("MediaPlayBtn"));

        horizontalLayout_3->addWidget(MediaPlayBtn);

        horizontalSpacer_9 = new QSpacerItem(20, 24, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_9);

        MediaResetBtn = new QToolButton(widget_tools);
        MediaResetBtn->setObjectName(QString::fromUtf8("MediaResetBtn"));

        horizontalLayout_3->addWidget(MediaResetBtn);

        horizontalSpacer_10 = new QSpacerItem(20, 24, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_10);

        toolButton_pgup = new QToolButton(widget_tools);
        toolButton_pgup->setObjectName(QString::fromUtf8("toolButton_pgup"));

        horizontalLayout_3->addWidget(toolButton_pgup);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        toolButton_pgDn = new QToolButton(widget_tools);
        toolButton_pgDn->setObjectName(QString::fromUtf8("toolButton_pgDn"));

        horizontalLayout_3->addWidget(toolButton_pgDn);

        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        VolumeBtn = new QToolButton(widget_tools);
        VolumeBtn->setObjectName(QString::fromUtf8("VolumeBtn"));
        VolumeBtn->setCheckable(true);

        horizontalLayout_3->addWidget(VolumeBtn);

        horizontalSlider_AudioValue = new QSlider(widget_tools);
        horizontalSlider_AudioValue->setObjectName(QString::fromUtf8("horizontalSlider_AudioValue"));
        horizontalSlider_AudioValue->setMaximumSize(QSize(100, 16777215));
        horizontalSlider_AudioValue->setMaximum(10);
        horizontalSlider_AudioValue->setValue(10);
        horizontalSlider_AudioValue->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(horizontalSlider_AudioValue);

        horizontalSpacer_5 = new QSpacerItem(182, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        MediaSpeedBtn = new QToolButton(widget_tools);
        MediaSpeedBtn->setObjectName(QString::fromUtf8("MediaSpeedBtn"));
        MediaSpeedBtn->setCheckable(false);

        horizontalLayout_3->addWidget(MediaSpeedBtn);

        horizontalSpacer_14 = new QSpacerItem(20, 24, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_14);

        MediaRotateBtn = new QToolButton(widget_tools);
        MediaRotateBtn->setObjectName(QString::fromUtf8("MediaRotateBtn"));

        horizontalLayout_3->addWidget(MediaRotateBtn);

        horizontalSpacer_12 = new QSpacerItem(20, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_12);

        MediaSnapshotBtn = new QToolButton(widget_tools);
        MediaSnapshotBtn->setObjectName(QString::fromUtf8("MediaSnapshotBtn"));

        horizontalLayout_3->addWidget(MediaSnapshotBtn);

        horizontalSpacer_11 = new QSpacerItem(20, 24, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_11);

        toolButton_about = new QToolButton(widget_tools);
        toolButton_about->setObjectName(QString::fromUtf8("toolButton_about"));

        horizontalLayout_3->addWidget(toolButton_about);

        horizontalSpacer_13 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_13);

        checkBox_video_list = new QCheckBox(widget_tools);
        checkBox_video_list->setObjectName(QString::fromUtf8("checkBox_video_list"));

        horizontalLayout_3->addWidget(checkBox_video_list);


        verticalLayout_3->addWidget(widget_tools);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", nullptr));
        label_FileName->setText(QString());
        toolButton_close->setText(QString());
        label_current_Time->setText(QApplication::translate("Widget", "00.00.00.00", nullptr));
        label_3->setText(QApplication::translate("Widget", "/", nullptr));
        label_Total_Time->setText(QApplication::translate("Widget", "00.00.00.00", nullptr));
        toolButton_load->setText(QString());
        MediaPrevBtn->setText(QString());
        MediaPauseBtn->setText(QString());
        MediaPlayBtn->setText(QString());
        MediaResetBtn->setText(QString());
        toolButton_pgup->setText(QString());
        toolButton_pgDn->setText(QString());
        VolumeBtn->setText(QString());
        MediaSpeedBtn->setText(QApplication::translate("Widget", "1.0", nullptr));
        MediaRotateBtn->setText(QString());
        MediaSnapshotBtn->setText(QString());
        toolButton_about->setText(QString());
        checkBox_video_list->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
