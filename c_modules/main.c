#include "memoria.h"

int main(){
  mem_init();
  set_contenido_mem(0xfffc, 0x04);
  print_contenido_mem();
}
