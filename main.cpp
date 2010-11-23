#include <QtGui/QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QStringList cmdline_args = QCoreApplication::arguments();

    if(cmdline_args.length() != 2) {
        qDebug("Usage :");
        qDebug("program path/to/track_bitmap.file ");
        return 0;
    }

    QString fileName = cmdline_args[1];
    MainWindow w;
    w.show();
    if(!w.setFileName(fileName)) {
        qDebug("Error reading image file");
        return -1;
    }

    return a.exec();
}

