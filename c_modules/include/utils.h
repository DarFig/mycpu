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
int esProductor(uint8_t opCode){
  //devuelve 1 si el opcode pertenece a una productora
  switch (opCode) {
    case 0x01 : return 1;//Mov;
    case 0x02 : return 1;//Ld;
    case 0x08 : return 1;//And;
    case 0x09 : return 1;//Or;
    case 0x0A : return 1;//Sum;
    case 0x0B : return 1;//Res;
    case 0x0C : return 1;//Rs1;
    case 0x0E : return 1;//Men;
    case 0x0F : return 1;//Equ;
    default : return 0;
  }
}
int leeMemoria(uint8_t opCode){
  //devuelve 1 si el opcode pertenece a una lectora de memoria
  //por ahora solo tenemos el load
  switch (opCode) {
    case 0x02 : return 1;//Ld;
    default : return 0;
  }
}
int escrMemoria(uint8_t opCode){
  //devuelve 1 si el opcode pertenece a una escritura en memoria
  //por ahora solo tenemos el store
  switch (opCode) {
    case 0x03 : return 1;//st;
    default : return 0;
  }
}
int movRs2(uint8_t opCode){
  //devuelve 1 si el opcode pertenece a una mov a rs2
  //por ahora solo tenemos el mov
  switch (opCode) {
    case 0x01 : return 1;//mov;
    default : return 0;
  }
}

#endif
