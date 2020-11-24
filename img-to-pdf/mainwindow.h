#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>
#include <QFileDialog>
#include <QPdfWriter>
#include <QTextDocument>
#include <QDirIterator>
#include <QDebug>
#include <QPainter>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_dirButton_clicked();

    void on_startButton_clicked();

    void on_setDefDirButton_clicked();

private:
    Ui::MainWindow *ui;
    QString str;
    QString imgFormats = "jpg png jpeg";

};
#endif // MAINWINDOW_H
