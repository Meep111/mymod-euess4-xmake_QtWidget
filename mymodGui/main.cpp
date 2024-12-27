#include "mymodGui.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mymodGui w;
    w.show();
    return a.exec();
}
