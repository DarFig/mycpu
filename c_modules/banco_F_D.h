#ifndef BANCO_F_D_H
#define BANCO_F_D_H

#include <stdint.h>

static bool carga = 1;
static uint32_t instruccion = 0x0000;
void set_instruccion(int32_t _instruccion){
  if(carga)
    instruccion = _instruccion;
}
uint32_t get_instruccion(){
  return instruccion;
}

#endif
