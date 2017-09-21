#pragma once
/*
* Autor:  Dariel
* v2017.09.21
* Brinda la funcionalidad para que dado un fichero origen con código
* ensamblador referente al emulador se pueda pasar su contenido a los opcodes
* definidos y los escribe en otro fichero destino.
*
* gcc versión 6.3.1
*/
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "itoa.h"

using namespace std;


class Interprete {
private:
      ifstream forigen;
      ofstream fdestino;
      int flag_ld = 0; //flag que marca operaciones tipo lw
      int flag_st = 0; //flag que marca operaciones tipo st
      int flag_beq = 0; //también el beq
      int flag_nop = 0;

      /*
      * dado la secuencia de caracteres correspondientes a una operación
      * devuelve el "operation code" asociado a ella
      */
      string obtener_opcode_instruccion(string operacion){
        //utilizamos un opcode de 6bits por lo que dos son siempre 0
        //pero por el número de operaciones implementadas cuatro serán 0
        if(operacion.compare( "nop") == 0){
           flag_nop = 1;
           return "000000";
         }
        if(operacion.compare( "mov") == 0){
          flag_ld = 1;
          return "000001";
        }
        if(operacion.compare("lw") == 0){
          flag_ld = 1;
          return "000010";
        }
        if(operacion.compare( "sw") == 0){
          flag_st = 1;
          return "000011";
        }
        if(operacion.compare( "beq") == 0){
          flag_beq = 1;
          return "000100";
        }
        if(operacion.compare("and") == 0) return "001000";
        if(operacion.compare("or") == 0) return "001001";
        if(operacion.compare("sum") == 0) return "001010";
        if(operacion.compare("res") == 0) return "001011";
        if(operacion.compare( "rs1") == 0) return "001100";
        if(operacion.compare("<") == 0) return "001101";
        if(operacion.compare("=") == 0) return "001111";
        return "-1";
      }


      /*
      * dado la secuencia de caracteres correspondientes a un registro o un
      * inmd(constante de hasta 16bits) devuelve el "operation code" asociado a el
      */
      string obtener_opcode_registro(string registro){
        int num;
        //char buffer[32];

        if( registro.substr(0, 1).compare( "r"))
          registro.erase(registro.begin());
        num = atoi(registro.c_str());
        string a = itoa(num, 2);
        return a;
      }
public:

  Interprete(const char *file_org, const char *file_dest){
    this->forigen.open(file_org);
    this->fdestino.open(file_dest);
  }
  ~Interprete(){

  }


  /*
  * Dado un fichero origen con código ensamblador referente al emulador
  * "traduce" su contenido a los opcodes definidos y los escribe en otro fichero
  * destino 
  */
  void interpretar(){
    string linea;
    while(getline(this->forigen,linea)){
      fdestino << linea;

    }

    this->forigen.close();
    this->fdestino.close();
  }
};
