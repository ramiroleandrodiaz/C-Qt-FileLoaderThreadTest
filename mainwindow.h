#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProgressBar>
#include <QThread>
#include <QMessageBox>
#include <string>
#include <fstream>

#include "worker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_pressed();
    void on_pushButton_2_pressed();

public slots:
    void SLOT_rangeDetected(short a, short b);
    void SLOT_loadedZ(int z);
    void SLOT_finishedLoading();

private:
    Ui::MainWindow *ui;
    QThread workerThread;
    Worker *w;

    void connectActions();

signals:
    void loadFileMultiThreading();
};

#endif // MAINWINDOW_H
