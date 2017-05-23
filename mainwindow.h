#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void on_pushButton_clicked();
    void obrir_about();
    QString sendData (QString day, double co2, double no2, QString location, QString JARpath);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
