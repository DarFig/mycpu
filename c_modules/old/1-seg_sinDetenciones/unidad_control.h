#ifndef UNIDAD_CONTROL_H
#define UNIDAD_CONTROL_H

#include <stdint.h>
#include "utils.h"

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
    case 0x00 : return Nop;
    case 0x01 : return Mov;
    case 0x02 : return Ld;
    case 0x03 : return St;
    case 0x04 : return Beq;
    case 0x05 : return Nop;
    case 0x06 : return Nop;
    case 0x07 : return Nop;
    case 0x08 : return And;
    case 0x09 : return Or;
    case 0x0A : return Sum;
    case 0x0B : return Res;
    case 0x0C : return Rs1;
    case 0x0D : return Nop;
    case 0x0E : return Men;
    case 0x0F : return Equ;
    default : return Nop;
  }

}


#endif
