#include "protagonista.h"


Jugador::Jugador()
{
  vida = 5;
  amuleto = FALSE;
  espada = TRUE;
  posx_jugador=0; //coordenadas x,y del jugador
  posy_jugador=0; 
  
};

int Jugador::get_Vida()
{
  return(vida);
};

void Jugador::set_Vida(int v)
{
  vida = v;
};

bool Jugador::get_Amuleto()
{
  return(amuleto);
};

void Jugador::set_Amuleto(bool a)
{
  amuleto = a;
};

int Jugador::get_posx_jugador()
{
  return(posx_jugador);
};

void Jugador::set_posx_jugador(int x)
{
  posx_jugador = x;
};

int Jugador::get_posy_jugador()
{
  return(posy_jugador);
};

void Jugador::set_posy_jugador(int y)
{
  posy_jugador = y;
};

bool Jugador::get_espada()
{
  return(espada);
};
  
void Jugador::set_espada(bool e)
{
  espada = e;
};



	