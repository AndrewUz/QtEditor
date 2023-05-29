#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
    currentFile.clear();
    ui->textEdit->setText(QString());
}


void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open File", "C:/Users/Andrew/Documents", "All Files (*.*);; Text File (*.txt)");
    QFile file(filename);
    currentFile = filename;
    if (!file.open(QIODevice::ReadOnly | QFile :: Text))
    {
        if (file.errorString() != "No file name specified")
            QMessageBox::warning(this, "Warning", "Cannot open " + file.errorString());
        return;

    }

    setWindowTitle(filename);
    QTextStream in(&file);
    QString text = in.readAll();
    ui -> textEdit -> setText(text);
    file.close();

     }
void MainWindow::on_actionSave_As_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save as", "C:/Users/Andrew/Documents", "All Files (*.*);; Text File (*.txt)");
    QFile file(filename);

    if (!file.open(QFile::WriteOnly | QFile :: Text))
    {
        if (file.errorString() != "No file name specified")
            QMessageBox::warning(this, "Warning", "Cannot save " + file.errorString());
        return;

    }

     currentFile = filename;
     setWindowTitle(filename);
     QTextStream out(&file);
     QString text = ui->textEdit->toPlainText();
     out << text;
     file.close();

}


void MainWindow::on_actionPrint_triggered()
{
    QPrinter* printer;
    QPrintDialog printerDialog(printer, this);
    if (printerDialog.exec() == QDialog::Rejected)
    {
        QMessageBox::warning(this, "Warning", "Cannot Acces or print terminated");
        return;
    }

    ui->textEdit->print(printer);

}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

