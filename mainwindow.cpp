#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPalette>
#include <QColorDialog>
#include<QPainter>
#include <QCloseEvent>
#include <QMessageBox>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

    setWindowTitle("Editor");

    ui->menubar->setStyleSheet("QMenuBar { background-color: rgb(192, 192, 192)}");

    QPalette pl = ui->textEdit->palette();
    pl.setColor(QPalette::Base, Qt::white);
    pl.setColor(QPalette::Text, Qt::black);
    ui->textEdit->setPalette(pl);

    QFont font;
    font.setPointSize(12);
    ui->textEdit->setFont(font);

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

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(QFileDialog::getSaveFileName(this, "Print to", "C:/Users/Andrew/Documents", "Pdf (*.pdf)"));
    ui->textEdit->print(&printer);

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





void MainWindow::on_actionChange_Backround_Color_triggered()
{
    QPalette pl = ui->textEdit->palette();
    pl.setColor(QPalette::Base, QColorDialog::getColor(Qt::white, this));
    ui->textEdit->setPalette(pl);
}


void MainWindow::on_actionChange_Font_Color_triggered()
{
    QPalette pl = ui->textEdit->palette();
    pl.setColor(QPalette::Text, QColorDialog::getColor(Qt::white, this));
    ui->textEdit->setPalette(pl);
}


void MainWindow::on_actionSave_triggered()
{
    if (currentFile != "")
    {
        QFile file(currentFile);
        if (!file.open(QFile::WriteOnly | QFile :: Text))
        {
            if (file.errorString() != "No file name specified")
                QMessageBox::warning(this, "Warning", "Cannot save " + file.errorString());
            return;

        }
        QTextStream out(&file);
        QString text = ui->textEdit->toPlainText();
        out << text;
        file.close();
    }

    else
    {
        this->on_actionSave_As_triggered();
    }


}

void MainWindow::closeEvent(QCloseEvent *event)  // show prompt when user wants to close app
{
    event->ignore();
    auto answer = QMessageBox::question(this, "Close Confirmation", "Save before exit?", QMessageBox::Yes | QMessageBox::No |QMessageBox::Cancel );
    if (QMessageBox::Yes == answer)
    {
        this->on_actionSave_triggered();
        event->accept();
    }

    if (QMessageBox::No == answer)
        event->accept();
    else
        return;
}


void MainWindow::on_actionChange_Font_Size_triggered()
{
    ui->textEdit->setFont(QFontDialog::getFont(0, ui->textEdit->font()));
}

