#ifndef BANCOREGISTROS_H
#define BANCOREGISTROS_H
#include <stdint.h>
#include <stdio.h>
#define MAX_REG 32
//static const uint32_t max_reg = 32;
static uint32_t banco [MAX_REG];

/*
Las direciones tienen que estar dentro del dominio de max_reg
*/
void w_port(uint8_t num_reg, uint32_t dato, int regWr){
  //printf("regWr  %#x\n", regWr );
  //printf("num_reg %#x\n", num_reg );
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
void print_contenido_BR_detalle(uint8_t num_reg_start, uint8_t num_reg_end){
  int aux = 0;
  for(int i = num_reg_start; i < num_reg_end; i++){
    printf("R%i: %#x --", i, banco[i]);
    aux++;
    if(aux>8){
      printf("\n");
      aux = 0;
    }
  }
  printf("\n");
}


#endif
