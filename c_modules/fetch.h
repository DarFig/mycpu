#ifndef FETCH_H
#define FETCH_H
#include <stdint.h>
#include "memoria.h"
#include "bancos.h"
#include "utils.h"

#define PCINI 0x0000
#define PCFIN 0xFFFF

//trabajemos con direccionamiento 32bits
static uint32_t pc = 0x0000;
//siguiente instruccion
static uint32_t instruccion = 0x0000;

//static int salto = 0;

//dir de salto
static uint32_t dir_salto = 0x0000;

//señal de control para el siguiente valor de pc
int pcSrc = 0;

uint32_t get_pc(){
  return pc;
}

void set_pc(int32_t new_pc){
  pc = new_pc;
}
void set_pcSrc(int32_t new_pcSrc){
  pcSrc = new_pcSrc;
}


/*void set_salto(int _salto){
  salto = _salto;
}*/

void set_dir_salto(int32_t _dir_salto){
  dir_salto = _dir_salto;
}

uint32_t get_instruccion_fech(){
  return instruccion;
}

void etapa_fetch_run(){
  //
  instruccion = get_contenido_mem(pc);
  //cargar en banco
  if(F_D_F.carga == 1){
    pc = multiplex_2(pc+4, dir_salto, pcSrc);
    F_D_F.instruccion = instruccion;
    F_D_F.pc4 = pc;
  }
  if(pc > PCFIN) pc = PCINI;
}



#endif
