#ifndef BANCOS_H
#define BANCOS_H

#include <stdint.h>

struct banco_F_D{
  int carga;
  uint32_t instruccion;
};

struct banco_F_D F_D = {1, 0x0000};

#endif
