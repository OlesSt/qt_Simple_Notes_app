#include "notepad.h"
#include "./ui_notepad.h"



Notepad::Notepad(QWidget *parent)
{
    this->resize(500, 500);


    ui = new Ui::MainWindow();
    ui->setupUi(this);

    // Connect actions of FILE menuBar
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(actionNew()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(actionOpen()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(actionSave()));
    connect(ui->actionSave_As, SIGNAL(triggered()), this, SLOT(actionSaveAs()));
    connect(ui->actionExport_PDF, SIGNAL(triggered()), this, SLOT(actionExportPDF()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(actionExit()));






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

void Notepad::actionExit()
{
    QApplication::quit();
}
