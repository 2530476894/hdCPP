QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

CONFIG += c++17 utf8_source

MDK_SDK = $$PWD/mdk-sdk
INCLUDEPATH += $$MDK_SDK/include

MDK_ARCH = x86

LIBS += -L$$MDK_SDK/lib/$$MDK_ARCH -lmdk
LIBS += -L$$MDK_SDK/bin/$$MDK_ARCH

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS


# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    QMDKWidget.cpp \
    Slider.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    QMDKWidget.h \
    Slider.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES +=

#可执行文件名称
TARGET=MDKPlayer

#版本信息
VERSION = 1.3.3

#图标
RC_ICONS =resource/logo.ico


#产品名称
QMAKE_TARGET_PRODUCT = "MDKPlayer"

#文件说明
QMAKE_TARGET_DESCRIPTION = "Qt Creator based on Qt 5.12.6 (MinGW 32 bit)"



#中文（简体）
RC_LANG = 0x0004

