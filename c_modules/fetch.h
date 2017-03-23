#ifndef FETCH_H
#define FETCH_H
#include <stdint.h>
#include "memoria.h"

static int32_t pc = 0x0000;//trabajemos con direccionamiento 32bits
static int32_t instruccion = 0x0000;
static int carga_pc = 1;
static int salto = 0;
static int32_t dir_salto = 0x0000;

int32_t get_pc(){
  return pc;
}
void set_pc(int32_t new_pc){
  pc = new_pc;
}

void set_carga_pc(int _carga){
  carga_pc = _carga;
}
void set_salto(int _salto){
  salto = _salto;
}
void set_dir_salto(int32_t _dir_salto){
  dir_salto = _dir_salto;
}

int32_t get_instruccion(){
  return instruccion;
}

void etapa_run(){
  //
  instruccion = get_contenido_mem(pc);
  pc+4;
  //cargar en banco
}



#endif
