#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"

QString fileName;
QString fileName2;
QString fileName3;

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
    ui->textBrowser->clear();
    QString newDay = ui->comboBox->currentText();
    double newPM10 = ui->doubleSpinBox_CO2->value();
    double newNO2 = ui->doubleSpinBox_NO2->value();
    double newTemp = ui->doubleSpinBox_Temp->value();
    QString newLocation;
    if(ui->comboBox_2->currentText()=="Palau Reial"){
        newLocation = "Palau_Reial";
    }
    else if(ui->comboBox_2->currentText()=="Torrent Gornal"){
        newLocation = "Torrente_Gornal";
    }
    else{
        newLocation = "Sants";
    }

    QString resultat = sendData(newDay,newNO2,newPM10,newTemp, newLocation);

    ui->textBrowser->insertPlainText(resultat);
}

void MainWindow::obrir_about()
{
    About *a = new About;
    a->exec();

    delete a;
}

QString MainWindow::sendData (QString day,double no2, double pm10, double temp, QString location) {

    QLocale::setDefault(QLocale(QLocale::English));
    QLocale locale; // Constructs a default QLocale

    QString PM10_text = locale.toString(pm10, 'f', 2);
    QString C_text = locale.toString(temp, 'f', 2);
    QString NO2_text = locale.toString(no2, 'f', 2);

   QString execute;

   execute="java -jar \"" + fileName + "\" -d " + day + " -p " + PM10_text +
           " -n " + NO2_text + " -t " + C_text + " -l " + location + " -m \"" + fileName2 + "\" -f \"" + fileName3 +"\"";

   weka.start(execute);
   weka.waitForFinished();
   QString resposta = weka.readAllStandardOutput();

   return resposta;

}

void MainWindow::on_toolButton_clicked()
{

    fileName = QFileDialog::getOpenFileName(this,
            tr("Selecciona l'aplicació"), "",
            tr("Java Archive (*.jar);;Tots els fitxers (*)"));
    //QString fileName = "\"" + file + "\"";
    ui->executableTextEdit->setPlainText(fileName);

}

void MainWindow::on_toolButton_2_clicked()
{
    fileName2 = QFileDialog::getOpenFileName(this,
            tr("Selecciona l'aplicació"), "",
            tr("Fitxer de model (*.model);;Tots els fitxers (*)"));
    ui->modelTextEdit->setPlainText(fileName2);
}

void MainWindow::on_toolButton_3_clicked()
{
    fileName3 = QFileDialog::getOpenFileName(this,
            tr("Selecciona l'aplicació"), "",
            tr("Fitxer ARFF (*.arff);;Tots els fitxers (*)"));
    ui->dataTextEdit->setPlainText(fileName3);
}
