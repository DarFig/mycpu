#ifndef BANCOS_H
#define BANCOS_H

#include <stdint.h>
#include "unidad_control.h"
#include "utils.h"
struct banco_F_D{
  int carga;
  uint32_t instruccion;
  uint32_t pc4;
};

struct banco_D_E{
  int carga;
  uint8_t rs1;
  uint8_t rs2;
  uint8_t d_rd;
  uint32_t inmExt;
  //señales de control
  struct operacion p_op;
};
struct banco_E_M{
  uint32_t aluOut;
  uint8_t d_rd;
  //señales de control
  struct operacion p_op;
};

//dobles banco, al final del ciclo copiar de banco de entrada a salida
struct banco_F_D F_D_F = {1, 0x0000};
struct banco_F_D F_D_D = {1, 0x0000};

struct banco_D_E D_E_D = {1,0x00,0x00,0x00,0x00000000,Nop};
struct banco_D_E D_E_E = {1,0x00,0x00,0x00,0x00000000,Nop};

struct banco_E_M E_M_E = {0x00000000,0x00,Nop};
struct banco_E_M E_M_M = {0x00000000,0x00,Nop};


#endif
