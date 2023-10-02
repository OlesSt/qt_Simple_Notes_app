#include "notepad.h"
#include "./ui_notepad.h"

Notepad::Notepad(QWidget *parent)
{
    this->resize(500, 500);


    ui = new Ui::MainWindow();
    ui->setupUi(this);

    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(actionNew()));





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
