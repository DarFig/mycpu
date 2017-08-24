#ifndef UTILS_H
#define UTILS_H
#include <stdint.h>


struct operacion {
  uint8_t aluop;//solo usa 3bits
  int salto;
  int regWr;
  int reDst;
  int memW;
  int memR;//memToR = memR
  int aluSrc;//por ahora solo 0 o 1
  uint8_t opCode;
};

uint32_t multiplex_2(uint32_t in0, uint32_t in1, int selec){
  if(selec == 0)
    return in0;
  if(selec == 1)
    return in1;
  if(selec > 1)
    return 0;
}

uint32_t multiplex_4(uint32_t in0, uint32_t in1, uint32_t in2, uint32_t in3, int selec){
  if(selec == 0)
    return in0;
  if(selec == 1)
    return in1;
  if(selec == 2)
    return in2;
  if(selec == 3)
    return in3;
  if(selec > 3)
    return 0;
}


#endif
