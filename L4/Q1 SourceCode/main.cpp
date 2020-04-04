#include "mainwindow.h"
#include <QApplication>
#include<QFile>
#include<QTextStream>
//Please keep the input file in the required location otherwise the program will not work
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QFile file("L4_P1_input.csv");
    QStringList meaning;
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;

    while(!file.atEnd())
    {
        QString line=file.readLine();
        QStringList l=line.split(';');
        //words<<l.at(0);
        w.insert(l.at(0),l.at(1));
    }
    w.show();
    return a.exec();
}
