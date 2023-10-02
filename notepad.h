#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QApplication>

#include <QMenuBar>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT
public:
    Notepad(QWidget *patent = nullptr);
    ~Notepad();

public slots:
    void actionNew();

private:
    QString currentFile;
    Ui::MainWindow *ui;





};

#endif // NOTEPAD_H
