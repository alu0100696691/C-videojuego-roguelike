#ifndef _tablero_H_
#define _tablero_H_



#include <iostream>
#include <fstream>    //fichero
#include <stdlib.h>  //exit
#include <stdio.h>  //NULL
#include <string.h>
#include <cstdlib>  //rand()
#include <time.h>
#include "protagonista.h"
#include "celda.h"
#include "monstruo.h"
#include <termios.h>  
#include <unistd.h> 




#define TRUE 1
#define FALSE 0 

using namespace std;

class Celda;
class Jugador;
class Enemigo;

class Tablero
{
private:
  int alto_tablero,ancho_tablero;
  int dim_x_1,dim_y_1,pos1x,pos1y,dim_x_2,dim_y_2,pos2x,pos2y,dim_x_3,dim_y_3,pos3x,pos3y;  //dimensiones habitaciones y posicion
  
  
  
public:
  Tablero();  //constructor sin argumentos
  Tablero(char *fichero);  //constructor leemos mazmorra desde fichero
  Tablero(int alto, int ancho);  // constructor crea mazmorra de forma aleatoria
  
  Celda **pCelda;   //puntero a clase Celda para guardar los elementos del tablero 
  Jugador *pProtagonista;  //puntero a clase protagonista
  Enemigo *pMonstruo;  //puntero a clase enemigo
  
  void crearMazmorra();  //creamos mazmorra de forma aleatoria
  void crearProtagonista();  //creamos el personaje del juego
  void crearMonstruos();     //tres monstruos por habitacion
  void moverMonstruos();    //movemos los monstruos
  
  void mostrarMazmorra();  //mostramos la mazmorra
  void habitaciones();  //para saber los tamannos de las habitaciones dim_x_2,dim_y_2, etc...
  void ciclo();  //esta es la funcion que permite mover el personaje y monstruos por el tablero
  void tecla(char );  //funcion complementaria de ciclo, para el movimiento del personaje
  
  int getAlto_tablero();
  int getAncho_tablero();
  int get_pos(int h, char c);   //devuelve posx de la habitacion h coordenada x,y
  int get_dim(int h, char c);   //devuelve dimensiones habitacion h coordenada x,y
  
  int getch(void);  //funcion para capturar una tecla sin enter y sin echo en pantalla
  int vidas();    //devuelve numero de vidas del protagonista
  bool amuleto();  //devuelve si protagonista a conseguido el amuleto
  void quita_vidas();  //nos quita vidas al protagonista si hay un monstruo cerca
  void mata_monstruo(int);
  
  
  ~Tablero();  //destructor
  
  
  
};



#endif
  