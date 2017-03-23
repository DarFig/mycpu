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
void set_contenido_mem(int32_t direccion, int8_t contenido){
  mem[direccion]=contenido;
}
void print_contenido_mem(){
  int32_t aux = 0x00000000;
  for(int i = 0; i < mem_max; i++){
    aux = 0xFF000000*mem[i]+ 0xFF0000*mem[i+1] + 0xFF00*mem[i+2] + mem[i+3];
    printf("%#x : %d %d %d %d : %#x\n", i, mem[i], mem[i+1], mem[i+2], mem[i+3],aux);
    i+=3;
  }
}


#endif
