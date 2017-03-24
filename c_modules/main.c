#include "memoria.h"

int main(){
  mem_init();
  //set_contenido_mem(0xfffc, 0x04);
  //set_contenido_mem(0xfffd, 0x84);
  //set_contenido_mem(0xfffe, 0xF1);
  //set_contenido_mem(0xffff, 0x12);
  set_contenido_mem(0xfffc, 0x12f18404);

  print_contenido_mem();
}
