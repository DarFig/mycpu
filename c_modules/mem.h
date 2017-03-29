#ifndef MEM_H
#define MEM_H

#include "memoria.h"
#include "bancos.h"

static uint32_t aluOut = 0x00000000;
static uint8_t d_rd = 0x00;
static uint32_t mem_out = 0x00000000;

void etapa_mem_run(){
    //leer E_M
    aluOut = E_M_M.aluOut;
    d_rd = E_M_M.d_rd;

    //r_w_memoria
    if(E_M_M.p_op.memW == 1){
      set_contenido_mem(aluOut, E_M_M.dato);
    }else if(E_M_M.p_op.memR == 1){
      mem_out = get_contenido_mem(aluOut);
    }

    //escritura en M_W
    M_W_M.aluOut = aluOut;
    M_W_M.d_rd = d_rd;
    M_W_M.p_op = E_M_M.p_op;
    M_W_M.mem_out = mem_out;

}

#endif
