#ifndef MEMORIA_H
#define MEMORIA_H

#include <stdint.h>
#include <stdio.h>
/*
Este módulo de memoria trabaja por defecto en big-endian.
Ejemplo:
para el dato: 0x12f18404 el orden de almacenamiento en memoria sería
04 84 f1 12 -> estando el 04 en la posición inferior en memoria
*/

static const uint32_t mem_max = 0xFFFF; //máxima dir de memoria, inicializada por defecto
volatile uint8_t mem [mem_max];

void mem_init(){
  for(int i = 0; i < mem_max; i++){
    mem[i]= 0x0000;
  }
}

uint32_t get_mem_max(){
  return mem_max;
}

uint32_t get_contenido_mem(int32_t direccion){
  return mem[direccion];
}

void set_contenido_mem(int32_t direccion, int8_t contenido){
  mem[direccion]=contenido;
}

void print_contenido_mem(){
  uint32_t unsigned aux = 0x00000000;
  for(int i = 0; i < mem_max; i++){
    aux = (mem[i+3] << 24) | (mem[i+2] << 16) | (mem[i+1] << 8) | mem[i];
    printf("%#x : %#x %#x %#x %#x : %#x\n", i, mem[i], mem[i+1], mem[i+2], mem[i+3],aux);
    i+=3;
  }
}

void mode(){
  printf("big-endian");
}


#endif
