#ifndef INTERPRETE_H
#define INTERPRETE_H
/*
* Autor:  Dariel
* v2017.09.19
* Brinda la funcionalidad para que dado un fichero origen con código
* ensamblador referente al emulador se pueda pasar su contenido a los opcodes
* definidos y los escribe en otro fichero destino.
*
* gcc versión 6.3.1
*/

#include <stdio.h>
//#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "itoa.h"


int flag_ld = 0; //flag que marca operaciones tipo lw
int flag_st = 0; //flag que marca operaciones tipo st
int flag_beq = 0; //también el beq
int flag_nop = 0;

/*
* dado la secuencia de caracteres correspondientes a una operación
* devuelve el "operation code" asociado a ella
*/
static char* obtener_opcode_instruccion(char * operacion){
  //utilizamos un opcode de 6bits por lo que dos son siempre 0
  //pero por el número de operaciones implementadas cuatro serán 0
  if(strcmp(operacion, "nop") == 0){
     flag_nop = 1;
     return "000000";
   }
  if(strcmp(operacion, "mov") == 0){
    flag_noRd = 1;
    return "000001";
  }
  if(strcmp(operacion, "lw") == 0){
    flag_ld = 1;
    return "000010";
  }
  if(strcmp(operacion, "sw") == 0){
    flag_st = 1;
    return "000011";
  }
  if(strcmp(operacion, "beq") == 0){
    flag_beq = 1;
    return "000100";
  }
  if(strcmp(operacion, "and") == 0) return "001000";
  if(strcmp(operacion, "or") == 0) return "001001";
  if(strcmp(operacion, "sum") == 0) return "001010";
  if(strcmp(operacion, "res") == 0) return "001011";
  if(strcmp(operacion, "rs1") == 0) return "001100";
  if(strcmp(operacion, "<") == 0) return "001101";
  if(strcmp(operacion, "=") == 0) return "001111";
  return "-1";
}

/*
* dado la secuencia de caracteres correspondientes a un registro o un
* inmd(constante de hasta 16bits) devuelve el "operation code" asociado a el
*/
static char* obtener_opcode_registro(char * registro){
  if(registro[0] == "r")
    int reg_aux = atoi(&registro[1]);//obtenemos el número de registro
  return itoa(reg_aux, 2);
}

/*
* Dado un fichero origen [file_org] con código ensamblador referente al emulador
* "traduce" su contenido a los opcodes definidos y los escribe en otro fichero
* destino [file_dest]
*/
void interpretar(const char *file_org, const char *file_dest){
  FILE *forigen;
  FILE *fdestino;
  char caracter;
  char *cadena = "";
  char *operacion = "";
  char *registro_uno = "";
  char *registro_dos = "";
  char *registro_tres = "";
  int num_reg = 1;

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
    //hasta fin de fichero
    //también se podrían usar streams
    //me lo miraré luego xD(seguro lo olvido)
    cadena = "";
    while(caracter != " " && (fread(&caracter, sizeof caracter, 1, forigen)>0)){
      //leer hasta el primer espacio
      cadena += caracter;
    }

    if(strcmp((operacion = obtener_opcode_instruccion(cadena)) , "-1")){
      fclose (forigen);
      fclose (fdestino);
      exit -1;
    }
    cadena = "";

    while(caracter != "\n" && (fread(&caracter, sizeof caracter, 1, forigen)>0)){
      //leer hasta fin de linea
      while(caracter != " " && (fread(&caracter, sizeof caracter, 1, forigen)>0)){
        cadena += caracter;
      }
      if(num_reg == 1) registro_uno = cadena;
      else if(num_reg == 2) registro_dos = cadena;
      else registro_tres = cadena;
      num_reg++;
      cadena = "";
    }

    registro_uno = obtener_opcode_registro(registro_uno);
    registro_dos = obtener_opcode_registro(registro_dos);
    if(num_reg == 4) registro_tres = obtener_opcode_registro(registro_tres);
    num_reg = 1;


    //Reconstruir cadena utilizando los flags como info del tipo de operacion
    // y el orden de los registros
    if(flag_ld == 1){
      for(int i = 0; strlen(registro_uno) < 6; i++)registro_uno = "0"+registro_uno;
      for(int i = 0; strlen(registro_dos) < 6; i++)registro_dos = "0"+registro_dos;
      for(int i = 0; strlen(registro_tres) < 12; i++)registro_tres = "0"+registro_tres;
                        //      rs1         +     rs2      +     inmd
      cadena = operacion + registro_dos + registro_uno + registro_tres;
    }else if(flag_st == 1){
      for(int i = 0; strlen(registro_uno) < 6; i++)registro_uno = "0"+registro_uno;
      for(int i = 0; strlen(registro_tres) < 6; i++)registro_tres = "0"+registro_tres;
      for(int i = 0; strlen(registro_dos) < 12; i++)registro_dos = "0"+registro_dos;
                          //      rs1         +     rs2      +     inmd
      cadena = operacion + registro_uno + registro_tres + registro_dos;
    }else if(flag_beq == 1){
      cadena = operacion + registro_uno + registro_dos + registro_tres;
    else if(flag_nop){
      cadena = "00000000000000000000000000000000";
    }else{
      for(int i = 0; strlen(registro_uno) < 6; i++)registro_uno = "0"+registro_uno;
      for(int i = 0; strlen(registro_tres) < 6; i++)registro_tres = "0"+registro_tres;
      for(int i = 0; strlen(registro_dos) < 6; i++)registro_dos = "0"+registro_dos;
                        //      rs1         +     rs2      +     rd
      cadena = operacion + registro_dos + registro_tres + registro_uno;
    }
    //escribir en el fichero destino
    fwrite(&cadena, sizeof caracter, 1, fdestino);

    //reset flags
    flag_ld = 0;
    flag_st = 0;
    flag_beq = 0;
    flag_nop = 0;
  }


  fclose (forigen);
  fclose (fdestino);
}






#endif
