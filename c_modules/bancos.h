#ifndef BANCOS_H
#define BANCOS_H

#include <stdint.h>

struct banco_F_D{
  int carga;
  uint32_t instruccion;
  uint32_t pc4;
};
struct banco_D_E{
  int carga;
  static uint8_t rs1;
  static uint8_t rs2;
  static uint8_t d_rd;
  static uint32_t inmExt;
  //todo: señales de control

};

struct banco_F_D F_D = {1, 0x0000};
struct banco_D_E D_E;//todo: inicializacion a 0

#endif
