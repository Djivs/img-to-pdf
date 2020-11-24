#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());
    QFile f("dir.txt");
    if(f.open(QIODevice::ReadOnly))
        str = f.readAll();
    QFile f1("class.txt");
    if(f1.open(QIODevice::ReadOnly))
        ui->classText->setText(f1.readAll());
    QFile f2("name.txt");
    if(f2.open(QIODevice::ReadOnly))
        ui->nameText->setText(f2.readAll());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_dirButton_clicked()
{
    QString str1 = QFileDialog::getExistingDirectory(0, "Directory Dialog", "/home/dmitriy");
    qDebug() << str1;
    QFile f("dir.txt");
    if(str1 != "" && f.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        str = str1;
        QTextStream out(&f);
        out << str;
    }
}

void MainWindow::on_startButton_clicked()
{
    QFile f2("class.txt");
    if(f2.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        QTextStream out(&f2);
        out << ui->classText->toPlainText();
    }
    QFile f1("name.txt");
    if(f1.open(QIODevice::ReadWrite | QIODevice::Truncate))
    {
        QTextStream out(&f1);
        out << ui->nameText->toPlainText();
    }
    QString filename = ui->classText->toPlainText()+"_"+ui->nameText->toPlainText()+"_"+ui->subjBox->currentText()+'_'+ui->dateEdit->date().toString("dd.MM.yyyy")+".pdf";
    qDebug() << filename << str;
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
    ui->statusbar->showMessage("Finished");
}
