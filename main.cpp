#include "CodeAutoBuild.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CodeAutoBuild w;
    w.show();
    return a.exec();
}
