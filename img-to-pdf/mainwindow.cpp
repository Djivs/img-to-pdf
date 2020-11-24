#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    str = QFileDialog::getExistingDirectory(0, "Directory Dialog", "/home/dmitriy");
    qDebug() << str;
}

void MainWindow::on_pushButton_clicked()
{
    QString filename = "11И_Трифонов_"+ui->comboBox->currentText()+ui->dateEdit->date().toString("dd.MM.yyyy")+".pdf";
    QPdfWriter pdfWriter(str +'/' + filename);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    QPainter painter(&pdfWriter);
    QDirIterator it(str, QDir::NoFilter);
    while (it.hasNext()) {
        QFile f(it.next());
        if(f.open(QIODevice::ReadOnly))
        {
            QFileInfo info(f);
            if(imgFormats.indexOf(info.completeSuffix()) != -1)
            {
                painter.drawPixmap(QRect(0,0,pdfWriter.logicalDpiX()*8.3,pdfWriter.logicalDpiY()*11.7), QPixmap(f.fileName()));
                if(it.hasNext())
                    pdfWriter.newPage();
            }
        }
    }


}
