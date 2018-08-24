#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->progressBar->setVisible(false);

    this->w = new Worker();
    w->moveToThread(&workerThread);
    connectActions();


}

MainWindow::~MainWindow()
{
    delete ui;
    workerThread.quit();
    workerThread.wait();
}

void MainWindow::connectActions(){
    connect(&workerThread, &QThread::finished, w, &QObject::deleteLater);
    connect(this, SIGNAL(loadFileMultiThreading()), this->w, SLOT(SLOT_work()));

    // While Loading

    connect(this->w, SIGNAL(rangeDetected(short,short)), this, SLOT(SLOT_rangeDetected(short,short)));
    connect(this->w, SIGNAL(loadedZ(int)), this, SLOT(SLOT_loadedZ(int)));

    // When finished Loading

    connect(this->w, SIGNAL(finishedLoading()), this, SLOT(SLOT_finishedLoading()));
}

void MainWindow::on_pushButton_pressed()
{
    // NO THREADS

    ui->progressBar->setVisible(true);

    std::ifstream file("/Users/ramirodiaz/Documents/Facultad/Thesis/Disección AT-CRAIEM/APELLIDO^NOMBRE_1211018564_49424_20111128/APELLIDO^NOMBRE_1211018564_49424_20111128.vol", std::ifstream::in | std::ifstream::binary | std::ifstream::ate);
    if (file.is_open())
    {
      file.seekg (0, std::ifstream::beg); //Me paro en el comienzo del archivo
      /**/
      short cantPlanosAxiales,nroPrimerFrame;
      encabezado e;
      file.read((char*)&cantPlanosAxiales, sizeof(cantPlanosAxiales)); //Leo el primer elemento del archivo (un short int indicando la cantidad de planos axiales)
      file.read((char*)&nroPrimerFrame, sizeof(nroPrimerFrame)); //Leo el segundo elemento del archivo (un short int indicando el nro del primer frame a leer)
      file.read((char*)&e, sizeof(e));//Leo el primer encabezado.
      /**/
      ui->progressBar->setRange(nroPrimerFrame, cantPlanosAxiales);

      short value=0;

      for(int z = 0; z < cantPlanosAxiales ; z++)
      {
          if(z > 0)
          {
              file.read((char*)&e, sizeof(e));    //TODO: Ver como mover el puntero del archivo sin tener que leer.
          }
           for(int y = 0; y < 512; y++)           //TODO: 512 es fijo? O puede ser informacion variable que debe ser leida de los stats? de la imagen (e)
           {
               for(int x = 0; x < 512; x++){
                   file.read((char*)&value, sizeof(short));
               }
           }
           ui->progressBar->setValue(z);
      }

      file.close();

    }
    else {
      QMessageBox msg;
      msg.setText("No se pude Abrir el archivo...");
      msg.exec();
    }
}

void MainWindow::on_pushButton_2_pressed()
{
    ui->progressBar->setVisible(true);
    workerThread.start();

    emit loadFileMultiThreading();

}

void MainWindow::SLOT_rangeDetected(short a, short b){
    ui->progressBar->setRange(a,b);
}

void MainWindow::SLOT_loadedZ(int z){
    ui->progressBar->setValue(z);
}

void MainWindow::SLOT_finishedLoading(){

}
