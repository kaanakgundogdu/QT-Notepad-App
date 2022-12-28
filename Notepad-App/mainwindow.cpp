#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->text_edit_area);
    ui->statusbar->showMessage("Kaan Akgündoğdu");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    current_file.clear();
    ui->text_edit_area->setText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString file_name=QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(file_name);
    current_file=file_name;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,"Warning","Cannot Open File: " + file.errorString());
        return;
    }

    setWindowTitle(file_name);
    QTextStream in(&file);
    QString text=in.readAll();
    ui->text_edit_area->setText(text);
    file.close();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString file_name=QFileDialog::getSaveFileName(this,"Save As");
    QFile file(file_name);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"Warning","Cannot save the file: "+file.errorString());
        return;
    }
    current_file=file_name;
    setWindowTitle(file_name);
    QTextStream out(&file);
    QString text=ui->text_edit_area->toPlainText();
    out<<text;
    file.close();
}


void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Printer Name");
    QPrintDialog print_dialog(&printer,this);
    if (print_dialog.exec() == QDialog::Rejected) {
        QMessageBox::warning(this,"Warning","Cannot access printer");
        return;
    }
    ui->text_edit_area->print(&printer);
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->text_edit_area->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->text_edit_area->paste();
}


void MainWindow::on_actionCut_triggered()
{
    ui->text_edit_area->cut();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->text_edit_area->undo();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->text_edit_area->redo();
}

