#include "memoria.h"
#include "bancos.h"
#include <stdio.h>


//cargar a partir de 0x0 las instrucciones contenidas en rom
static void load_rom(){
;
}

int main(){
  mem_init();

  load_rom();
  char* entrada;
  while(entrada != "exit"){
    printf("%s\n", entrada);
    scanf("%s", entrada);
  }

  //set_contenido_mem(0xfffc, 0x12f18404);

  print_contenido_mem();
}
