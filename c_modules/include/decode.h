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




int parar(){//una ves anyadido los adelantos solo nos dan problema los loads a distancia 1
  ///printf("Reg1 %#x, Reg2 %#x, %#x, ope %#x, opd %#x : \n", d_rs1, d_rs2,multiplex_2(D_E_E.d_rs2, d_rd_e, D_E_E.p_op.reDst), D_E_E.p_op.opCode, opCode);
  /*if((d_rs1 == multiplex_2(D_E_E.d_rs2, d_rd_e, D_E_E.p_op.reDst) && esProductor(D_E_E.p_op.opCode))||(d_rs1 == E_M_M.d_rd && esProductor(E_M_M.p_op.opCode))||( d_rs1 == M_W_W.d_rd && esProductor(M_W_W.p_op.opCode))) return 1;
  else if((d_rs2 == multiplex_2(D_E_E.d_rs2, d_rd_e, D_E_E.p_op.reDst)&& esProductor(D_E_E.p_op.opCode))||(d_rs2 == E_M_M.d_rd && esProductor(E_M_M.p_op.opCode))||( d_rs2 == M_W_W.d_rd && esProductor(M_W_W.p_op.opCode))) return 1;
  else return 0;*/
  //detenciones en los loads a distancia 1
  if(leeMemoria(D_E_E.p_op.opCode) && d_rs1 == multiplex_2(D_E_E.d_rs2, d_rd_e, D_E_E.p_op.reDst)) return 1;
  else if(leeMemoria(D_E_E.p_op.opCode) && d_rs2 == multiplex_2(D_E_E.d_rs2, d_rd_e, D_E_E.p_op.reDst)) return 1;
  else return 0;

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
  if(parar()) D_E_D.carga = 0;
  else D_E_D.carga = 1;
  printf("parar: %i , carga %i\n", parar(),D_E_D.carga);


  //escritura en D_E
  if(D_E_D.carga == 1){

    D_E_D.rs1 = rs1_d;
    D_E_D.rs2 = rs2_d;
    D_E_D.d_rd = d_rd_d;
    D_E_D.d_rs1 = d_rs1;
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
    //F_D_F = F_D_D;
    F_D_F.carga = 0;

    //pasar nop a D_E
    D_E_D.rs1 = 0;
    D_E_D.rs2 = 0;
    D_E_D.d_rd = 0;
    D_E_E.d_rs1 = 0;
    D_E_D.d_rs2 = 0;
    D_E_D.inmExt = 0;
    D_E_D.p_op = Nop;
  }

  etapa_execute_run();
}



#endif
