#include "celda.h"



Celda::Celda() //constructor
{
  elemento = ' '; //celda vacia
};

Celda::Celda(char elem)  //constructor
{
  elemento = elem;
};

void Celda::setCelda(char elem)
{
  elemento = elem;
};

char Celda::getCelda()
{
  return(elemento);
};

