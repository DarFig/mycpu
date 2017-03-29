#ifndef BANCOREGISTROS_H
#define BANCOREGISTROS_H
#include <stdint.h>
#include <stdio.h>
#define MAX_REG 32
//static const uint32_t max_reg = 32;
static uint32_t banco [MAX_REG];

/*
Las dreciones tienen que esta dentro del dominio de max_reg
*/
void w_port(uint8_t num_reg, uint32_t dato, int regWr){
  if(regWr == 1) banco[num_reg] = dato;
}
uint32_t r_port(uint8_t num_reg){
  return banco[num_reg];
}
void print_contenido_BR_detalle(){
  for(int i = 0; i < MAX_REG; i++){
    printf("R%i: %#x \n", i, banco[i]);
  }
}


#endif
