#ifndef BANCOREGISTROS_H
#define BANCOREGISTROS_H
#include <stdint.h>

static const uint32_t max_reg = 32;
static uint32_t banco [max_reg];

/*
Las dreciones tienen que esta dentro del dominio de max_reg
*/
void w_port(uint8_t num_reg, uint32_t dato){
  banco[num_reg] = dato;
}
uint32_t r_port(uint8_t num_reg){
  return banco[num_reg];
}


#endif
