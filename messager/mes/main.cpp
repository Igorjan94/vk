#include "vk.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    char* s;
    if (argv[0][0] != '.' && argv[0][0] != '/' && argv[0][0] != '\"')
        s = argv[0];
    else
        s = argv[1];
    Vk w(s);
    w.show();
    return a.exec();
}
