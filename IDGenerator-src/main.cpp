#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <QTime>

int main(int argc, char *argv[])
{
//    std::cout << "Starting..." << std::endl;
//    std::cout.flush();
    // Prepare the randomizer
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());
    // Setup the application
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
