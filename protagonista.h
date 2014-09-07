#ifndef _protagonista_H_
#define _protagonista_H_

#include "tablero.h"

using namespace std;



class Jugador
{
private:
  int vida;  //vida del protagonista
  bool amuleto; //el protagonista tiene el amuleto?
  bool espada;  //el protagonista tiene o no espada mata bicho
  int posx_jugador; //coordenadas x,y del jugador
  int posy_jugador; 
public:
  Jugador();  //constructor
  int get_Vida();
  void set_Vida(int v);
  bool get_Amuleto();
  void set_Amuleto(bool a);
  bool get_espada();
  void set_espada(bool e);
  int get_posx_jugador();
  void set_posx_jugador(int x);
  int get_posy_jugador();
  void set_posy_jugador(int y);
};

#endif
