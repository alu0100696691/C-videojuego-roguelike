#ifndef _monstruo_H_
#define _monstruo_H_

#include "tablero.h"

using namespace std;



class Enemigo
{
private:
  int posx_enemigo; //coordenadas x,y del enemigo
  int posy_enemigo;
  bool vivo;  //esta vivo o muerto
public:
  Enemigo();  //constructor
  int get_posx_enemigo();
  void set_posx_enemigo(int x);
  int get_posy_enemigo();
  void set_posy_enemigo(int y);
  bool get_vivo();
  void set_vivo(bool v);
  ~Enemigo() {}
};

#endif