#include "widget.h"
#include <QDebug>
#include <QApplication>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    //支持在命令行传入播放文件
    if(argc==2)
    {
        qDebug()<<"传入视频文件.";
        //判断文件是否存在
        if(QFileInfo::exists(argv[1]))
        {
            qDebug()<<"视频文件名称:"<<argv[1];
            Widget w(argv[1]);
            w.show();
            return a.exec();
        }
    }

    Widget w;
    w.show();
    return a.exec();
}
