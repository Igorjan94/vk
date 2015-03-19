#include "vk.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Vk w;
    w.show();
    return a.exec();
}
