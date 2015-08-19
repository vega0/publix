#include <QApplication>

#include "defines/entry.h"
#include "launcher.h"

#define __CLASS__ "[Main]"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    __mark( M1, "Progra~, entry." );
    Launcher w;
    w.show();
    __elapsed( M1, "User code initialized in");
    return a.exec();
}
