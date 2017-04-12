#ifndef EXECUTE_H
#define EXECUTE_H

#include <stdint.h>
#include "bancos.h"
#include "utils.h"
#include "mem.h"


static uint32_t rs1 = 0x00000000;
static uint32_t rs2 = 0x00000000;
static uint32_t rA = 0x00000000;
static uint32_t rB = 0x00000000;

static uint32_t aluOut_e = 0x00000000;
static uint8_t d_rd_e = 0x00;
static uint32_t inmExt = 0x00000000;

static int flagX = 0;//1 if rs1 < rs2
static int flagZ = 0;//1 if rs1 = rs2

uint32_t alu(uint8_t aluOp, uint32_t rs1, uint32_t rs2){

  if(aluOp == 0x000){ //and
    return rs1 & rs2;
  }else if(aluOp == 0x001){//or
    return rs1 | rs2;
  }else if(aluOp == 0x011){//-
    return rs1 - rs2;
  }else if(aluOp == 0x100){//rs1
    return rs1;
  }if(aluOp == 0x110){//<
    if(rs1 < rs2) flagX = 1;
    return rs1;
  }if(aluOp == 0x111){//=
    if(rs1 == rs2) flagZ = 1;
    return rs1;
  }else{//+ por defecto 0x010
    return (rs1 + rs2);
  }

}

void etapa_execute_run(){
  //leer de banco D_E
  rs1 = D_E_E.rs1;
  rs2 = D_E_E.rs2;
  d_rd_e = D_E_E.d_rd;
  inmExt = D_E_E.inmExt;

  //pasar a alu
  rA = rs1;//sin adelantos
  rB = multiplex_2( rs2, inmExt ,D_E_E.p_op.aluSrc);
  aluOut_e = alu(D_E_E.p_op.aluop, rA, rB);

  //escritura en E_M
  E_M_E.aluOut = aluOut_e;
  E_M_E.d_rd = multiplex_2(D_E_E.d_rs2, d_rd_e, D_E_E.p_op.reDst);


  E_M_E.dato = rs2;
  
  E_M_E.p_op = D_E_E.p_op;

  etapa_mem_run();
}

#endif
