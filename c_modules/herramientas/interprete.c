/*
* Autor:  Dariel
* v2017.09.21
* Brinda la funcionalidad para que dado un fichero origen con código
* ensamblador referente al emulador se pueda pasar su contenido a los opcodes
* definidos y los escribe en otro fichero destino.
*
* gcc versión 6.3.1
*/

#include <stdio.h>
#include "interprete.h"

main(int argc, char *argv[]){
  if(argc != 3){
    fprintf(stderr, "Forma de uso: %s origen destino\n", arv[0]);
    exit(-1);
  }
  interpretar(argv[1], argv[2]);

  exit(0);
}
