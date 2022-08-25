#include "widget.h"
#include <QDebug>

#include <QApplication>

void customMessageHandler(QtMsgType type, const QMessageLogContext &, const QString & str)
{
    QString txt=str;
    QString app_run_addr;
    //获取程序当前运行目录
    QString current_PathName = QCoreApplication::applicationDirPath();
    if(QFile::exists(current_PathName)==false)
    {
        app_run_addr="debug.log";
    }else
    {
        app_run_addr=current_PathName+"/"+"debug.log";
    }
    QFile outFile(app_run_addr);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << endl;
}


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    //初始化qdebug的输出重定向到文件
   // qInstallMessageHandler(customMessageHandler);

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
