#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QProgressBar>
#include <QMessageBox>
#include <string>
#include <fstream>

typedef struct{
    short frame; // frame: InstanceNumber.
    short alto, ancho; //cantidad de pixeles.
    short min, max; //valor min y max de la intensidad de la imagen: Hounsfield units.
    float dX, dY, dZ; // dx=dy (mqm) por ej 0.65mm. dz: valor absoluto.
} encabezado;

class Worker : public QObject
{
    Q_OBJECT

public:
    Worker();

public slots:
    void SLOT_work();

signals:
    void rangeDetected(short a, short b);
    void loadedZ(int z);
    void finishedLoading();
};

#endif // WORKER_H
