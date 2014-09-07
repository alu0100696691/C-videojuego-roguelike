#ifndef _celda_H_
#define _celda_H_



class Celda
{
private:
  char elemento;
public:
  Celda();
  Celda(char elem); //constructor 
  void setCelda(char elem);  //asignar valor a elemento
  char getCelda();   //devuelve valor celda
  
};

#endif