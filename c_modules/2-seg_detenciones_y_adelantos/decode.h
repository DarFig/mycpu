#ifndef DECODE_H
#define DECODE_H

#include <stdint.h>
#include "bancos.h"
#include "BancoRegistros.h"
#include "unidad_control.h"
#include "utils.h"
#include "write_bank.h"
#include "execute.h"



extern void set_pcSrc(int32_t new_pcSrc);
extern void set_dir_salto(int32_t _dir_salto);
//con 32 registros definidos direccionaremos con 5 de los 8 bits

static uint8_t d_rs1 = 0x00; //direcciones
static uint8_t d_rs2 = 0x00;
static uint8_t d_rd_d = 0x00;
static int32_t pc4 = 0x00000000;
//datos
static uint16_t inmed = 0x0000;
static uint32_t inmExt_d = 0x00000000;
//datos
static uint32_t rs1_d = 0x00000000;
static uint32_t rs2_d = 0x00000000;
//código de operacion
static uint8_t opCode = 0x00;

struct operacion p_op;

static int salto = 0;//la unidad de control lo pone a 1


int esProductor(uint8_t opCode){
  //devuelve 1 si el opcode pertenece a una productora
  switch (opCode) {
    case 0x01 : return 1;//Mov;
    case 0x02 : return 1;//Ld;
    case 0x08 : return 1;//And;
    case 0x09 : return 1;//Or;
    case 0x0A : return 1;//Sum;
    case 0x0B : return 1;//Res;
    case 0x0C : return 1;//Rs1;
    case 0x0E : return 1;//Men;
    case 0x0F : return 1;//Equ;
    default : return 0;
  }
}

int parar(){
  if((d_rs1 == E_M_E.d_rd && esProductor(opCode))||( d_rs1 == M_W_M.d_rd)) return 1;
  else if((d_rs2 == E_M_E.d_rd && esProductor(opCode))||( d_rs2 == M_W_M.d_rd)) return 1;
  else return 0
}


void etapa_decode_run(){
  uint32_t inst;
  //leer de banco F_D
  inst = F_D_D.instruccion;
  pc4 = F_D_D.pc4;
  //decodificar
  opCode = (inst >> 26);
  d_rs1 = (inst >> 21)&0x1F;
  d_rs2 = (inst >> 16) & 0x1F;
  d_rd_d = (inst >> 11) & 0x1F;
  inmed = inst & 0xFFFF;
  inmExt_d = inmed;

  //escritura en BR
  etapa_writeBank_run();//esto equivale a escritura en medio ciclo
                        //y lectura en la otra mitad

  //leer operandos
  rs1_d = r_port(d_rs1);
  rs2_d = r_port(d_rs2);
  //unidad de control
  p_op = run_control(opCode);
  salto = p_op.salto;
  //detectar riesgos
  //D_E_D.carga = 1;
  if(para()) D_E_D.carga = 1;
  else D_E_D.carga = 0;


  //escritura en D_E
  if(D_E_D.carga == 1){
    D_E_D.rs1 = rs1_d;
    D_E_D.rs2 = rs2_d;
    D_E_D.d_rd = d_rd_d;
    D_E_D.d_rs2 = d_rs2;
    D_E_D.inmExt = inmExt_d;
    D_E_D.p_op = p_op;
    //dar carga al fetch
    F_D_F.carga = 1;
    //salto
    if(salto == 1 && rs1_d == rs2_d){
      //set_dir_salto(pc4 + inmExt_d);
      set_dir_salto(inmExt_d);//saltar al inmediato extendido
      set_pcSrc(1);
    }
  }else{
    //quitar carga al FETCH_H
    F_D_F.carga = 0;
    //pasar nop a D_E
    D_E_D.rs1 = 0;
    D_E_D.rs2 = 0;
    D_E_D.d_rd = 0;
    D_E_D.d_rs2 = 0;
    D_E_D.inmExt = 0;
    D_E_D.p_op = Nop;
  }

  etapa_execute_run();
}



#endif
