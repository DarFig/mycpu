#ifndef MEMORIA_H
#define MEMORIA_H

#include <stdint.h>
#include <stdio.h>

static const int32_t mem_max = 0xFFFF; //máxima dir de memoria, inicializada por defecto
volatile int8_t mem [mem_max];

void mem_init(){
  for(int i = 0; i < mem_max; i++){
    mem[i]= 0x0000;
  }
}

int32_t get_mem_max(){
  return mem_max;
}
int32_t get_contenido_mem(int32_t direccion){
  return mem[direccion];
}
void print_contenido_mem(){
  for(int i = 0; i < mem_max; i++){
    printf("%#x : %d %d %d %d \n", i, mem[i], mem[i+1], mem[i+2], mem[i+3]);
    i+=3;
  }
}


#endif
