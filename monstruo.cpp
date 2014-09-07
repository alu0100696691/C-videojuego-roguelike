#include "monstruo.h"

Enemigo::Enemigo()  //constructor
{
  posx_enemigo = 0;
  posy_enemigo = 0;
  vivo = TRUE;
};

int Enemigo::get_posx_enemigo()
{
  return(posx_enemigo);
};

void Enemigo::set_posx_enemigo(int x)
{
  posx_enemigo = x;
};

int Enemigo::get_posy_enemigo()
{
  return(posy_enemigo);
};
  
void Enemigo::set_posy_enemigo(int y)
{
  posy_enemigo = y;
};

bool Enemigo::get_vivo()
{
  return(vivo);
};

void Enemigo::set_vivo(bool v)
{
  vivo = v;
};

  