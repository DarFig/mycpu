#ifndef INTERPRETE_H
#define INTERPRETE_H


#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint8_t obtener_opcode(char * operacion){
  //utilizamos un opcode de 6bits por lo que dos son siempre 0
  //pero por el número de operaciones implementadas cuatro serán 0
  if(strcmp(operacion, "nop") == 0) return 0x00;//00 0000
  if(strcmp(operacion, "mov") == 0) return 0x01;//00 0001
  if(strcmp(operacion, "lw") == 0) return 0x02;//00 0010
  if(strcmp(operacion, "sw") == 0) return 0x03;//00 0011
  if(strcmp(operacion, "beq") == 0) return 0x04;//00 0100
  if(strcmp(operacion, "and") == 0) return 0x08;//00 1000
  if(strcmp(operacion, "or") == 0) return 0x09;//00 1001
  if(strcmp(operacion, "sum") == 0) return 0x0a;//00 1010
  if(strcmp(operacion, "res") == 0) return 0x0b;//00 1011
  if(strcmp(operacion, "rs1") == 0) return 0x0c;//00 1100
  if(strcmp(operacion, "<") == 0) return 0x0d;//00 1101
  if(strcmp(operacion, "=") == 0) return 0x0f;//00 1111
}

void transcribir(const char *file_org, const char *file_dest){
  FILE *forigen;
  FILE *fdestino;
  char caracter;
  char *cadena = "";
  //char *subcadena = "";


  if((forigen = fopen(file_org, "r")) == NULL){
    //apertura fichero origen
    perror(file_org);
    exit(-1);
  }
  if((fdestino = fopen(file_dest, "w")) == NULL){
    //apertura o creación fichero destino
    perror(file_dest);
    exit(-1);
  }

  while(fread(&caracter, sizeof caracter, 1, forigen)>0){
    //también se podrían usar streams
    //me lo miraré luego xD

    while(caracter != " "){
      //leer hasta el primer espacio
      cadena += caracter;
    }
    //subcadena =

    cadena = "";

  }


  fclose (forigen);
  fclose (fdestino);
}






#endif //INTERPRETE_H
