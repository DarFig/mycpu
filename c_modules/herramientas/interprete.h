#pragma once
/*
* Autor:  Dariel
* v2017.09.21
* Brinda la funcionalidad para que dado un fichero origen con código
* ensamblador referente al emulador se pueda pasar su contenido a los opcodes
* definidos y los escribe en otro fichero destino.
*
* gcc versión 6.3.1
* Compilar con: g++ -std=c++11 interpretar.cpp -o interpretar
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
        if(operacion.compare( "nop")==0){
           flag_nop = 1;
           return "000000";
         }
        if(operacion.compare( "mov")==0){
          flag_ld = 1;
          return "000001";
        }
        if(operacion.compare("lw")==0){
          flag_ld = 1;
          return "000010";
        }
        if(operacion.compare( "sw") ==0){
          flag_st = 1;
          return "000011";
        }
        if(operacion.compare( "beq")==0 ){
          flag_beq = 1;
          return "000100";
        }
        if(operacion.compare("and") ==0) return "001000";
        if(operacion.compare("or") ==0) return "001001";
        if(operacion.compare("add")==0 || operacion.compare("sum")==0) return "001010";
        if(operacion.compare("res") ==0) return "001011";
        if(operacion.compare( "rs1")==0) return "001100";
        if(operacion.compare("<") ==0) return "001101";
        if(operacion.compare("=") ==0) return "001111";
        return "000000";
      }


      /*
      * dado la secuencia de caracteres correspondientes a un registro o un
      * inmd(constante de hasta 16bits) devuelve el "operation code" asociado a el
      */
      string obtener_opcode_registro(string registro){
        int num;
        registro = registro.substr(registro.find("r")+1);
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
    size_t found;
    string linea;
    string operacion="", registro_uno="", registro_dos="", registro_tres="";
    while(getline(this->forigen,linea)){
      //substrings
      found = linea.find(" ");
      operacion = linea.substr(0, found);
      linea = linea.substr(found+1);

      found = linea.find(" ");
      registro_uno = linea.substr(0, found);
      linea = linea.substr(found+1);

      found = linea.find(" ");
      registro_dos = linea.substr(0, found);
      linea = linea.substr(found+1);

      found = linea.find(" ");
      registro_tres  = linea.substr(0, found);

      //obtener opcodes <<paso a binarios>>
      operacion = this->obtener_opcode_instruccion(operacion);
      registro_uno = this->obtener_opcode_registro(registro_uno);
      registro_dos = this->obtener_opcode_registro(registro_dos);
      registro_tres = this->obtener_opcode_registro(registro_tres);

      //Reconstruir cadena utilizando los flags como info del tipo de operacion
      // y el orden de los registros
      if(flag_ld == 1){
        for(int i = 0; registro_uno.length() < 5; i++)registro_uno = "0" + registro_uno;
        for(int i = 0; registro_dos.length() < 5; i++)registro_dos = "0" + registro_dos;
        for(int i = 0; registro_tres.length() < 16; i++)registro_tres = "0" + registro_tres;
        linea = operacion + registro_dos + registro_uno + registro_tres;
      }else if(flag_st == 1){
        for(int i = 0; registro_uno.length() < 5; i++)registro_uno = "0" + registro_uno;
        for(int i = 0; registro_tres.length() < 5; i++)registro_tres = "0" + registro_tres;
        for(int i = 0; registro_dos.length() < 16; i++)registro_dos = "0" + registro_dos;
        linea = operacion +  registro_uno + registro_tres + registro_dos;
      }else if(flag_beq){
        for(int i = 0; registro_uno.length() < 5; i++)registro_uno = "0" + registro_uno;
        for(int i = 0; registro_dos.length() < 5; i++)registro_dos = "0" + registro_dos;
        for(int i = 0; registro_tres.length() < 16; i++)registro_tres = "0" + registro_tres;
        linea = operacion + registro_uno + registro_dos + registro_tres;
      }else if(flag_nop){
        linea = "00000000000000000000000000000000";
      }else{
        for(int i = 0; registro_uno.length() < 5; i++)registro_uno = "0" + registro_uno;
        for(int i = 0; registro_dos.length() < 5; i++)registro_dos = "0" + registro_dos;
        for(int i = 0; registro_tres.length() < 5; i++)registro_tres = "0" + registro_tres;
        linea = operacion + registro_dos + registro_tres + registro_uno + "00000000000";
      }


      fdestino << linea<< endl;
      linea ="";
      //reset flags
      flag_ld = 0;
      flag_st = 0;
      flag_beq = 0;
      flag_nop = 0;

    }

    this->forigen.close();
    this->fdestino.close();
  }
};
