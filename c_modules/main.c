#include "memoria.h"
#include "bancos.h"
#include "fetch.h"

#include <stdio.h>

//cargar a partir de 0x0 las instrucciones contenidas en rom
static void load_rom(){
  /*
  mov r2, 2
  mov r5, 5
  nop
  nop
  sw r5, r0+inmd(C0)
  nop
  add r6,r2,r5
  */
  set_contenido_mem(0x00, 0x04020002);
  set_contenido_mem(0x04, 0x04050005);
  set_contenido_mem(0x08, 0x0);
  set_contenido_mem(0x0c, 0x0);
  set_contenido_mem(0x10, 0x0c0500C0);
  set_contenido_mem(0x14, 0x0);
  set_contenido_mem(0x18, 0x28453000);
  set_contenido_mem(0x1c, 0x0);
  set_pc(0x0);
}

int main(){
  mem_init();

  load_rom();
  /*printf("Instrucciones: \n");
  print_contenido_mem_detalle(0x00, 0x02c, get_pc());*/
  char entrada = ' ';
  while(entrada != 'e'){
    printf("Instrucciones: \n");
    print_contenido_mem_detalle(0x00, 0x2c, get_pc());
    //printf("%c\n", &entrada);
    etapa_fetch_run();//ejecutar un ciclo
    printf("Datos: \n");
    print_contenido_mem_detalle(0x00C0, 0x00CC);
    printf("Banco: \n");
    print_contenido_BR_detalle(0,7);
    scanf("%c", &entrada);
    //siguiente ciclo
    //copiar bancos de entrada en bacnos de salida
    F_D_D = F_D_F;
    D_E_E = D_E_D;
    E_M_M = E_M_E;
    M_W_W = M_W_M;
  }

  //set_contenido_mem(0xfffc, 0x12f18404);

  //print_contenido_mem();
}
