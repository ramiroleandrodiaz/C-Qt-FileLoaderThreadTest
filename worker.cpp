#include "worker.h"

Worker::Worker()
{

}

void Worker::SLOT_work(){
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

      emit rangeDetected(nroPrimerFrame, cantPlanosAxiales);

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
           emit loadedZ(z);
      }

      file.close();
      emit finishedLoading();
    }
    else {
      QMessageBox msg;
      msg.setText("No se pude Abrir el archivo...");
      msg.exec();
    }
}
