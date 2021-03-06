#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QPdfWriter>
#include <QDirIterator>
#include <QDebug>
#include <QPainter>
#include <QDesktopServices>
#include <QImageReader>

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

private:
    Ui::MainWindow *ui;
    QString dir;
    bool flip = 1;

};
#endif // MAINWINDOW_H
