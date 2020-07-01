#define png_infopp_NULL (png_infopp)NULL
#define int_p_NULL (int*)NULL

#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
