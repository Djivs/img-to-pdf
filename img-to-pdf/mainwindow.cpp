#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    QFile f("txt/dir.txt");
    if(f.open(QIODevice::ReadOnly))
        str = f.readAll();
    f.close();
    f.setFileName("txt/class.txt");
    if(f.open(QIODevice::ReadOnly))
        ui->classText->setText(f.readAll());
    f.close();
    f.setFileName("txt/name.txt");
    if(f.open(QIODevice::ReadOnly))
        ui->nameText->setText(f.readAll());
    f.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_dirButton_clicked()
{
    QString str1 = QFileDialog::getExistingDirectory(0, "Directory Dialog", "/home/dmitriy");
    QFile f("txt/dir.txt");
    if(str1 != "" && f.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        str = str1;
        QTextStream out(&f);
        out << str;
    }
    f.close();
}

void MainWindow::on_startButton_clicked()
{
    QFile f("txt/class.txt");
    if(f.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        QTextStream out(&f);
        out << ui->classText->toPlainText();
    }
    f.close();
    f.setFileName("txt/name.txt");
    if(f.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        QTextStream out(&f);
        out << ui->nameText->toPlainText();
    }
    f.close();
    QString filename = ui->classText->toPlainText()+"_"+ui->nameText->toPlainText()+"_"+ui->subjBox->currentText()+'_'+ui->dateEdit->date().toString("dd.MM.yyyy")+".pdf";
    QPdfWriter pdfWriter(str +'/' + filename);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    QPainter painter(&pdfWriter);
    QDirIterator it(str, QDir::NoFilter);
    while (it.hasNext())
    {
        QFile f(it.next());
        if(f.open(QIODevice::ReadOnly))
        {
            if(imgFormats.indexOf(f.fileName().mid(f.fileName().size() - 3, 3)) != -1
            || imgFormats.indexOf(f.fileName().mid(f.fileName().size() - 4, 4)) != -1)
            {
                painter.drawImage(QRect(0,0,pdfWriter.logicalDpiX()*8,pdfWriter.logicalDpiY()*11.5), QImage(f.fileName()));
                if(it.hasNext())
                    pdfWriter.newPage();
            }
        }
    }
    f.close();
    ui->statusbar->showMessage("Finished");
}
