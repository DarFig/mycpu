#ifndef DECODE_H
#define DECODE_H

#include <stdint.h>
#include "bancos.h"
#include "BancoRegistros.h"
extern void set_pcSrc(int32_t new_pcSrc);
extern void set_dir_salto(int32_t _dir_salto);
//con 32 registros definidos direccionaremos con 5 de los 8 bits
static uint8_t d_rs1 = 0x00; //direcciones
static uint8_t d_rs2 = 0x00;
static uint8_t d_rd = 0x00;
static int32_t pc4 = 0x00000000;
//datos
static uint16_t inmed = 0x0000;
static uint32_t inmExt = 0x00000000;
//datos
static uint8_t rs1 = 0x00;
static uint8_t rs2 = 0x00;
//código de operacion
static uint8_t opCode = 0x00;

static int salto = 0;//la unidad de control lo pone a 1



//todo: unidad de control


//todo: unidad de riesgos

void etapa_decode_run(){
  uint32_t inst;
  //leer de banco F_D
  inst = F_D.instruccion;
  pc4 = F_D.pc4;
  //decodificar
  opCode = (inst >> 24) & 0xFC;
  d_rs1 = (inst >> 20) & 0x3E;
  d_rs2 = (inst >> 16) & 0x1F;
  d_rd = (inst >> 8) & 0xF8;
  inmed = inst & 0xFFFF;
  inmExt = inmed;

  //escritura en BR

  //leer operandos
  rs1 = r_port(d_rs1);
  rs2 = r_port(d_rs2);

  //unidad de control

  //detectar riesgos


  //escritura en D_E
  if(D_E.carga == 1){
    D_E.rs1 = rs1;
    D_E.rs2 = rs2;
    D_E.d_rd = d_rd;
    D_E.inmExt = inmExt;

    //salto
    if(salto == 1 && rs1 == rs2){
      set_dir_salto(pc4 + inmExt);
      set_pcSrc(1);
    }
  }else{
    //pasar nop a D_E
    D_E.rs1 = 0;
    D_E.rs2 = 0;
    D_E.d_rd = 0;
    D_E.inmExt = 0;
  }
}



#endif
