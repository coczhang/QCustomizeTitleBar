#include "customizetitlebar.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CustomizeTitleBar w;
    w.show();

    return a.exec();
}
