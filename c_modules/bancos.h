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

struct banco_F_D F_D_F = {1, 0x0000};
struct banco_F_D F_D_D = {1, 0x0000};
struct banco_D_E D_E_D = {1,0x0,0x00,0x00,0x00000000,Nop};
struct banco_D_E D_E_E = {1,0x0,0x00,0x00,0x00000000,Nop};

#endif
