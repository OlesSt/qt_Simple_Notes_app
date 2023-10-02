#include "notepad.h"
#include "./ui_notepad.h"


Notepad::Notepad(QWidget *parent)
{
    this->resize(500, 500);

    ui = new Ui::MainWindow();
    ui->setupUi(this);

    // Connect actions of FILE menuBar
    connect (ui->actionNew,         SIGNAL(triggered()), this, SLOT(actionNew()));
    connect (ui->actionOpen,        SIGNAL(triggered()), this, SLOT(actionOpen()));
    connect (ui->actionSave,        SIGNAL(triggered()), this, SLOT(actionSave()));
    connect (ui->actionSave_As,     SIGNAL(triggered()), this, SLOT(actionSaveAs()));
    connect (ui->actionExport_PDF,  SIGNAL(triggered()), this, SLOT(actionExportPDF()));
    connect (ui->actionExit,        SIGNAL(triggered()), this, SLOT(actionExit()));

    // Connect actions of EDIT menuBar
    connect (ui->actionCopy,        SIGNAL(triggered()), this, SLOT(actionCopy()));
    connect (ui->actionCut,         SIGNAL(triggered()), this, SLOT(actionCut()));
    connect (ui->actionPaste,       SIGNAL(triggered()), this, SLOT(actionPaste()));
    connect (ui->actionUndo,        SIGNAL(triggered()), this, SLOT(actionUndo()));
    connect (ui->actionRedo,        SIGNAL(triggered()), this, SLOT(actionRedo()));

    // Connect actions of FORMAT menuBar
    connect(ui->actionBold,         SIGNAL(triggered()), this, SLOT(actionBold()));
    connect(ui->actionItalic,       SIGNAL(triggered()), this, SLOT(actionItalic()));
    connect(ui->actionUnderline,    SIGNAL(triggered()), this, SLOT(actionUnderline()));
    connect(ui->actionLeft,         SIGNAL(triggered()), this, SLOT(actionLeft()));
    connect(ui->actionRight,        SIGNAL(triggered()), this, SLOT(actionRight()));
    connect(ui->actionCenter,       SIGNAL(triggered()), this, SLOT(actionCenter()));
    connect(ui->actionFont,         SIGNAL(triggered()), this, SLOT(actionFont()));
    connect(ui->actionColor,        SIGNAL(triggered()), this, SLOT(actionColor()));

    connect(ui->actionAbout,        SIGNAL(triggered()), this, SLOT(actionAbout()));
}

Notepad::~Notepad()
{
    delete ui;
    ui = nullptr;
}

void Notepad::actionNew()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}

void Notepad::actionOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open file");
    QFile file(fileName);
    currentFile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Not found" + file.errorString());
        return;
    }

    setWindowTitle(fileName);
    QTextStream in (&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();

}

void Notepad::actionSave()
{
    QString fileName;
    if(currentFile.isEmpty())
    {
        fileName = QFileDialog::getSaveFileName(this, "Save", "", "Text Files (*.txt)");
        currentFile = fileName;
    }
    else {fileName = currentFile;}

    QFile file (fileName);
    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Not found" + file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out (&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::actionSaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save As", "", "Text Files (*.txt)");
    QFile file(fileName);

    if(!file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, "Warning", "Not found" + file.errorString());
        return;
    }
    currentFile = fileName;
    setWindowTitle(fileName);
    QTextStream out (&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void Notepad::actionExportPDF()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF", "", "PDF Files (*.pdf)");
    if(fileName != " ")
    {
        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        printer.setPageMargins(QMarginsF(30,30,30,30));
        ui->textEdit->document()->print(&printer);
    }
}

void Notepad::actionExit()  { QApplication::quit();}

void Notepad::actionCopy()  { ui->textEdit->copy();}

void Notepad::actionCut()   { ui->textEdit->cut();}

void Notepad::actionPaste() { ui->textEdit->paste();}

void Notepad::actionUndo()  { ui->textEdit->undo();}

void Notepad::actionRedo()  { ui->textEdit->redo();}

void Notepad::actionBold()
{
    QTextCharFormat format;
    QTextCursor cursor = ui->textEdit->textCursor();

    format = cursor.charFormat();

    if (format.fontWeight() == QFont::Bold)
        {format.setFontWeight(QFont::Normal);}
    else
        {format.setFontWeight(QFont::Bold);}

    cursor.setCharFormat(format);
}

void Notepad::actionItalic()
{
    QTextCharFormat format;
    QTextCursor cursor = ui->textEdit->textCursor();

    format = cursor.charFormat();

    if (format.fontWeight() == QFont::StyleItalic)
    {format.setFontWeight(QFont::Normal);}
    else
    {format.setFontWeight(QFont::StyleItalic);}

    cursor.setCharFormat(format);
}

void Notepad::actionUnderline()
{
    QTextCharFormat format;
    QTextCursor cursor = ui->textEdit->textCursor();

    format = cursor.charFormat();

    if (format.fontWeight() == QFont::UnderlineResolved)
    {format.setFontWeight(QFont::Normal);}
    else
    {format.setFontWeight(QFont::UnderlineResolved);}

    cursor.setCharFormat(format);
}

void Notepad::actionLeft()  { ui->textEdit->setAlignment(Qt::AlignmentFlag::AlignLeft);}

void Notepad::actionRight() { ui->textEdit->setAlignment(Qt::AlignmentFlag::AlignRight);}

void Notepad::actionCenter() { ui->textEdit->setAlignment(Qt::AlignmentFlag::AlignCenter);}

void Notepad::actionFont()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok)
        ui->textEdit->setFont(font);
}

void Notepad::actionColor()
{
    QColor color = QColorDialog::getColor();
    ui->textEdit->setTextColor(color);
}

void Notepad::actionAbout()
{
    QMessageBox::about(this, "About", "This is a simple notepad. Made by Oles Stepanov with QT6 in C++ as part of Qt6 and C++ courses.");
}



