#ifndef WRITE_BANK_H
#define WRITE_BANK_H

#include "bancos.h"
#include "BancoRegistros.h"

//para escritura en medio ciclo llamar desde decode antes de la lectura
void etapa_writeBank_run(){
  //en cualquier caso la escritura depende del permiso regWr

  if(M_W_W.p_op.memR){
    //si es un load escribe la salida de memoria

    w_port(M_W_W.d_rd, M_W_W.mem_out, M_W_W.p_op.regWr);
  }else{
    //escribe la salida de alu
    
    w_port(M_W_W.d_rd, M_W_W.aluOut, M_W_W.p_op.regWr);
  }
}


#endif
