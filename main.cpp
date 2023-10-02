// ===== SIMPLE NOTEPAD =====
// ===== Oles Stepanov  =====

#include <QApplication>

#include "notepad.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Notepad notepad;
    notepad.show();

    return a.exec();
}
