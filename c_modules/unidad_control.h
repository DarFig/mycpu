#ifndef UNIDAD_CONTROL_H
#define UNIDAD_CONTROL_H

#include <stdint.h>

struct operacion {
  uint8_t aluop;//solo usa 3bits
  int salto;
  int regWr;
  int reDst;
  int memW;
  int memR;//memToR = memR
  int aluSrc;
};
struct operacion Nop = {0x2,0,0,1,0,0,0};//000000
struct operacion Mov = {0x2,0,1,0,0,0,1};//000001
struct operacion Ld  = {0x2,0,1,0,0,1,1};//000010
struct operacion St  = {0x2,0,0,1,1,0,1};//000011
struct operacion Beq = {0x2,1,0,1,0,0,0};//000100
//000101
//000110
//000111
struct operacion And = {0x0,0,1,1,0,0,0};//001000
struct operacion Or  = {0x1,0,1,1,0,0,0};//001001 operador or
struct operacion Sum = {0x2,0,1,1,0,0,0};//001010 operador +
struct operacion Res = {0x3,0,1,1,0,0,0};//001011 operador -
struct operacion Rs1 = {0x4,0,1,1,0,0,0};//001100 devuelve rs1
//001101
struct operacion Men = {0x6,0,0,1,0,0,0};//001110 operador <
struct operacion Equ = {0x7,0,0,1,0,0,0};//001111 operador =

struct operacion run_control(uint8_t opCode){
  switch (opCode) {
    case 0x000000 : return Nop;
    case 0x000001 : return Mov;
    case 0x000010 : return Ld;
    case 0x000011 : return St;
    case 0x000100 : return Beq;
    case 0x000101 : return Nop;
    case 0x000110 : return Nop;
    case 0x000111 : return Nop;
    case 0x001000 : return And;
    case 0x001001 : return Or;
    case 0x001010 : return Sum;
    case 0x001011 : return Res;
    case 0x001100 : return Rs1;
    case 0x001101 : return Nop;
    case 0x001110 : return Men;
    case 0x001111 : return Equ;
    default : return Nop;
  }

}


#endif
