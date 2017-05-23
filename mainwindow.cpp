#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString newDay = ui->comboBox->currentText();
    double newCO2 = ui->doubleSpinBox_CO2->value();
    double newNO2 = ui->doubleSpinBox_NO2->value();
    QString newLocation = ui->comboBox_2->currentText();
    QString newJARPath;


    //QString resultat = sendData(newDay,newCO2,newNO2,newLocation,newJARPath);
    QString resultat = "Èxit";
    ui->textBrowser->insertPlainText(resultat);
}

void MainWindow::obrir_about()
{
    About *a = new About;
    a->exec();

    delete a;
}

QString MainWindow::sendData (QString day,double co2, double no2,QString location, QString jarpath) {

   QString resposta = day + "/" + co2 + "/" + no2 + "/" + location + "/" + jarpath;

   return resposta;

}


