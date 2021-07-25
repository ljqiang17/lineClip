#include "lineclip.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LineClip w;
    w.show();

    return a.exec();
}
