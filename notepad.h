#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>
#include <QApplication>

#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>


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
    // menuBar - FILE:
    void actionNew();
    void actionOpen();
    void actionSave();
    void actionSaveAs();
    void actionExportPDF();
    void actionExit();

    // menuBar - EDIT:
    void actionCopy();
    void actionCut();
    void actionPaste();
    void actionUndo();
    void actionRedo();

    // menuBar - FORMAT:
//    void actionBold();
//    void actionItalic();
//    void actionUnderline();
//    void actionLeft();
//    void actionRight();
//    void actionCenter();
//    void actionFont();
//    void actionColor();


private:
    QString currentFile;
    Ui::MainWindow *ui;


};

#endif // NOTEPAD_H
