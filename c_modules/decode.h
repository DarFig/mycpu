#ifndef DECODE_H
#define DECODE_H

#include <stdint.h>
#include "bancos.h"

//con 32 registros definidos direccionaremos con 5 de los 8 bits
static uint8_t rs1 = 0x00;
static uint8_t rs2 = 0x00;
static uint8_t rd = 0x00;

//todo: unidad de control

//todo: unidad de riesgos

void etapa_decode_run(){
  uint32_t inst;
  //leer de banco
  inst = F_D.instruccion;
  

}



#endif
