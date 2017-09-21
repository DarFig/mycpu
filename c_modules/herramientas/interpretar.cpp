/*
* Autor:  Dariel
* v2017.09.21
* Brinda la funcionalidad para que dado un fichero origen con código
* ensamblador referente al emulador se pueda pasar su contenido a los opcodes
* definidos y los escribe en otro fichero destino.
*
* gcc versión 6.3.1
* Compilar con: g++ -std=c++11 interpretar.cpp -o interpretar
*/


#include "interprete.h"
#include <iostream>

using namespace std;


int main(int argc, char *argv[]){
  if(argc != 3){
    cout<< "Forma de uso: " << argv[0] << " origen destino"<<endl;;
    return -1;
  }

  Interprete* miInt;
  miInt = new Interprete(argv[1], argv[2]);
  miInt->interpretar();
  delete(miInt);
  return 0;
}
