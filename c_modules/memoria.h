#ifndef MEMORIA_H
#define MEMORIA_H

#include <stdint.h>
#include <stdio.h>

#include "utils.h"
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

static uint32_t get_mem_big_endian(uint8_t B3, uint8_t B2, uint8_t B1, uint8_t B0){
  return (B3 << 24) | (B2 << 16) | (B1 << 8) | B0;
}

/*
direccion debe ser valida dentro del espacio de memoria y estar alineada como
un múltiplo de 4
*/
uint32_t get_contenido_mem(uint32_t direccion){
  return get_mem_big_endian(mem[direccion+3], mem[direccion+2], mem[direccion+1], mem[direccion]);
  //return (mem[direccion+3] << 24) | (mem[direccion+2] << 16) | (mem[direccion+1] << 8) | mem[direccion];
}

static void set_contenido(uint32_t direccion, uint8_t contenido){
  mem[direccion]=contenido;
}

/*
direccion debe ser valida dentro del espacio de memoria y estar alineada como
un múltiplo de 4
*/
void set_contenido_mem(uint32_t direccion, uint32_t data){
  set_contenido(direccion, (data & 0xFF));
  set_contenido(direccion+1, (data >> 8 )& 0xFF);
  set_contenido(direccion+2, (data >> 16)& 0xFF);
  set_contenido(direccion+3, (data >> 24)& 0xFF);

}


void print_contenido_mem(){
  uint32_t unsigned aux = 0x00000000;
  for(int i = 0; i < mem_max; i+=4){
    aux = get_mem_big_endian(mem[i+3], mem[i+2], mem[i+1], mem[i]);
    //printf("%#x : %#x %#x %#x %#x : %#x\n", i, mem[i], mem[i+1], mem[i+2], mem[i+3],aux);
    printf("%#x : %#x\n", i,aux);
  }
}
void print_contenido_mem_detalle(){
  uint32_t unsigned aux = 0x00000000;
  for(int i = 0; i < mem_max; i+=4){
    aux = get_mem_big_endian(mem[i+3], mem[i+2], mem[i+1], mem[i]);
    printf("%#x : %#x %#x %#x %#x : %#x\n", i, mem[i], mem[i+1], mem[i+2], mem[i+3],aux);
  }
}
void mode(){
  printf("big-endian");
}


#endif
