#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"

QString fileName;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionQuant_a,SIGNAL(triggered()),this,SLOT(obrir_about()));
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

    QString resultat = sendData(newDay,newCO2,newNO2,newLocation);
    //QString resultat = "Èxit";
    ui->textBrowser->insertPlainText(resultat);
}

void MainWindow::obrir_about()
{
    About *a = new About;
    a->exec();

    delete a;
}

QString MainWindow::sendData (QString day,double co2, double no2,QString location) {

    QLocale::setDefault(QLocale(QLocale::Catalan));
    QLocale locale; // Constructs a default QLocale

    QString CO2_text = locale.toString(co2, 'f', 2);
    QString NO2_text = locale.toString(no2, 'f', 2);

   QString execute;

   execute="java -jar " + fileName + " -d " + day + " -c " + CO2_text + " -n " + NO2_text + " -l " + location;

   weka.start(execute);
   weka.waitForFinished();
   QString resposta = weka.readAllStandardOutput();


   //QString resposta = day + " / " + CO2_text + " / " + NO2_text + " / " + location + " / " + fileName;

   return resposta;

}

void MainWindow::on_toolButton_clicked()
{

    fileName = QFileDialog::getOpenFileName(this,
            tr("Selecciona l'aplicació"), "",
            tr("Java Archive (*.jar);;Tots els fitxers (*)"));
    ui->executableTextEdit->setPlainText(fileName);

}
