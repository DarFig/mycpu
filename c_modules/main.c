#include "memoria.h"
#include "bancos.h"
#include "fetch.h"

#include <stdio.h>

//cargar a partir de 0x0 las instrucciones contenidas en rom
static void load_rom(){
;
}

int main(){
  mem_init();

  load_rom();
  print_contenido_mem_detalle(0x00, 0x08);
  char entrada = ' ';
  while(entrada != 'e'){
    //printf("%c\n", &entrada);
    etapa_fetch_run();//ejecutar un ciclo
    scanf("%c", &entrada);
  }

  //set_contenido_mem(0xfffc, 0x12f18404);

  //print_contenido_mem();
}
