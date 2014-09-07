#include "tablero.h"



using namespace std;

Tablero::Tablero()  //constructor
{
  
};

Tablero::Tablero(char *fichero)
{
  fstream fi;
  fi.open(fichero, ios::in);  //abrimos fichero para lectura
  dim_x_1=dim_y_1=pos1x=pos1y=dim_x_2=dim_y_2=pos2x=pos2y=dim_x_3=dim_y_3=pos3x=pos3y=0;  //inicializamos a cero posiciones de la habitaciones
  if (!fi)
  {
    throw "Error leyendo fichero";
    exit(1);
  }
  
  char linea[100];  //donde guardamos los caracteres leidos por el fichero  
  int fila=0;
  int colum=0;
  
  fi.getline(linea,100,'\n');  //leemos una linea hasta salto de linea
  colum = strlen(linea);  //numero de caracteres en cada fila
  colum--;
  fila++;
  
  while(fi.getline(linea,100,'\n'))
    fila++;  //numero de filas del fichero
      
     
  alto_tablero=fila;
  ancho_tablero=colum;
  
  pCelda = new Celda *[fila];   //construimos la matriz
  for(int i=0;i<colum;i++)
    pCelda[i] = new Celda[colum];
  
  fi.clear();
  fi.seekg(0, ios::beg);  //comienzo del fichero
  fila = 0;
  
  while (fi.getline(linea,100,'\n'))  //vamos leyendo las lineas del fichero
  {
    for(int i = 0;i<colum;i++)  //vamos llenando la matriz pcelda
      pCelda[fila][i].setCelda(linea[i]);
      
    fila++;  
  }
  if(!fi.eof()) //si al terminar eof distinto de eof
	throw "Error al leer el fichero";
  
  fi.close(); //cerramos el fichero
  
  habitaciones();  //obtenemos posiciones de las habitaciones
  crearProtagonista();
  crearMonstruos();
  
  
  
};

Tablero::Tablero(int alto, int ancho)
{
  alto_tablero=alto;
  ancho_tablero=ancho;
  
  pCelda = new Celda *[alto];   //construimos la matriz
  for(int i=0;i<ancho;i++)
    pCelda[i] = new Celda[ancho];
  
  crearMazmorra();  //creamos mazmorra de forma aleatoria
  
};

void Tablero::crearMazmorra()
{
  cout << "crearMazmorra" << endl;
};

void Tablero::mostrarMazmorra()
{
  
  for(int i = 0;i<alto_tablero;i++)
    for(int j = 0;j<ancho_tablero;j++)
    {
      if(ancho_tablero-j == 1)  //salto de linea
	cout << endl;
      cout << pCelda[i][j].getCelda();
    }
    
     
};

void Tablero::habitaciones()  //dimensiones y posicion de las distintas habitaciones
{
  int contx=0;
  int conty=0;
  for(int i = 0;i<alto_tablero;i++) {
    for(int j = 0;j<ancho_tablero;j++)
    {
      if(pCelda[i][j].getCelda() == '*' && (pCelda[i][j+1].getCelda() == '*' || pCelda[i][j+1].getCelda() == '+')  && (pCelda[i+1][j].getCelda() == '*' || pCelda[i+1][j].getCelda() == '+') )  //esquina habitacion
      { 
	if(pos1x == 0)  //habitacin 1
	{
	pos1x = i+1;
	pos1y = j+1;
	contx=0;
	conty=0;
	
	for(int z = j; pCelda[i][z].getCelda() != ' ';z++) 
	{ //buscamos el ancho           
	  conty++;  
	  dim_y_1=conty-3;  
	}
        for(int k = i; pCelda[k][j].getCelda() != ' ';k++) 
	{ //buscamos el alto
	  contx++;
	  dim_x_1=contx-3;	  
	}
	}
	else if(pos2x == 0) //habitacion 2
	{
	  pos2x = i+1;
	  pos2y = j+1;
	  contx=0;
	  conty=0;
	  
	  for(int z = j; pCelda[i][z].getCelda() != ' ';z++)  //buscamos el ancho
          {	    
	    conty++;
	    dim_y_2=conty-3;
	  }
          for(int k = i; pCelda[k][j].getCelda() != ' ';k++)  //buscamos el alto
          {
	    contx++;
	    dim_x_2=contx-3;	    
	  }
	}
	else if(pos3x == 0) //habitacion 3
	{
	  pos3x = i+1;
	  pos3y = j+1;
	  contx=0;
	  conty=0;
	  
	  for(int z = j; pCelda[i][z].getCelda() != ' ';z++)  //buscamos el ancho
          {	    
	    conty++;
	    dim_y_3=conty-3;
	  }
	  for(int k = i; pCelda[k][j].getCelda() != ' ';k++)  //buscamos el alto
          {
	    contx++;
	    dim_x_3=contx-3;	    
	  }
	  
	}
      }
    }
  }
  
};

void Tablero::crearProtagonista()
{
  pProtagonista = new Jugador();  //puntero apunta a objeto de la clase jugador
  
  for(int i = 0;i<alto_tablero;i++) {
    for(int j = 0;j<ancho_tablero;j++)
    {
      if(pCelda[i][j].getCelda() == 'X')  //ponemos el protagonista en la puerta de entrada
      {
	pCelda[i][j].setCelda('@');
	pProtagonista->set_posx_jugador(i); //coordenadas x,y del jugador
	pProtagonista->set_posy_jugador(j);
      }
    }
  }
};

void Tablero::crearMonstruos()
{
  pMonstruo = new Enemigo[9];  //nueve monstruos
  srand (time(NULL));  //semilla ramdon con el time del sistema
  int pos1 = 0;
  int pos2 = 0;
  int cont = 0;  //variable contador de monstruos
  int hab = 1;  //variable contador de habitacion
  //colocamos los monstruos de forma aleatoria por las habitaciones
  
    for(int i = 0;i<3;i++)
    { 
      for(int j = 0;j<3;j++)
      {
	pos1 = rand() % get_dim(hab, 'x') + 1;  //x aleatoria	
	pos2 = rand() % get_dim(hab, 'y') + 1;  //y aleatoria
	while( (pCelda[pos1+get_pos(hab, 'x')][pos2+get_pos(hab, 'y')].getCelda() ) != ' ')  //mientras no encontremos una celda vacia no metemos el bicho
	{
	  pos1 = rand() % get_dim(hab, 'x') + 1;  //x aleatoria	
	  pos2 = rand() % get_dim(hab, 'y') + 1;  //y aleatoria	  
	}	  
	pMonstruo[cont].set_posx_enemigo(pos1+get_pos(hab, 'x'));
	pMonstruo[cont].set_posy_enemigo(pos2+get_pos(hab, 'y'));
	pCelda[pMonstruo[cont].get_posx_enemigo()][pMonstruo[cont].get_posy_enemigo()].setCelda('O');  //pintamos el bicho
	cont++;  //siguiente monstruo
      }
      hab++;  //siguiente habitacion
    }
   
   
};
  
void Tablero::moverMonstruos()  //mover monstruos
{
  int pos1 = 0;
  int pos2 = 0;
  int cont = 0;  //variable contador de monstruos
  int hab = 1;  //variable contador de habitacion
  //colocamos los monstruos de forma aleatoria por las habitaciones
  
  for(int i = 0;i<9;i++)
    pCelda[pMonstruo[i].get_posx_enemigo()][pMonstruo[i].get_posy_enemigo()].setCelda(' '); //borramos los bichos de la antigua posicion
  
    for(int i = 0;i<3;i++)
    { 
      for(int j = 0;j<3;j++)
      {
	pos1 = rand() % get_dim(hab, 'x') + 1;  //x aleatoria	
	pos2 = rand() % get_dim(hab, 'y') + 1;  //y aleatoria
	while( (pCelda[pos1+get_pos(hab, 'x')][pos2+get_pos(hab, 'y')].getCelda() ) != ' ')  //mientras no encontremos una celda vacia no metemos el bicho
	{
	  pos1 = rand() % get_dim(hab, 'x') + 1;  //x aleatoria	
	  pos2 = rand() % get_dim(hab, 'y') + 1;  //y aleatoria	  
	}	  
	pMonstruo[cont].set_posx_enemigo(pos1+get_pos(hab, 'x'));
	pMonstruo[cont].set_posy_enemigo(pos2+get_pos(hab, 'y'));
	if(pMonstruo[cont].get_vivo() == TRUE)
	  pCelda[pMonstruo[cont].get_posx_enemigo()][pMonstruo[cont].get_posy_enemigo()].setCelda('O');  //pintamos el bicho
	cont++;  //siguiente monstruo
      }
      hab++;  //siguiente habitacion
    }
    
};
  
  


  
int Tablero::getAlto_tablero()
{
  return(alto_tablero);
};

int Tablero::getAncho_tablero()
{
  return(ancho_tablero);
};

int Tablero::get_pos(int h, char c)   //devuelve posx de la habitacion h coordenada x,y
{
  if(c == 'x')  // pos de x
  {
    switch(h)
    {
      case 1:
	return(pos1x);
	break;
      case 2:
	return(pos2x);
	break;
      case 3:
	return(pos3x);
	break;
    }
  }
  else if(c == 'y')
  {
    switch(h)
    {
      case 1:
	return(pos1y);
	break;
      case 2:
	return(pos2y);
	break;
      case 3:
	return(pos3y);
	break;
    }
  }
};
	
int Tablero::get_dim(int h, char c) 	//devuelve dimensiones habitacion h coordenada x,y  
{
  if(c == 'x')  // pos de x
  {
    switch(h)
    {
      case 1:
	return(dim_x_1);
	break;
      case 2:
	return(dim_x_2);
	break;
      case 3:
	return(dim_x_3);
	break;
    }
  }
  else if(c == 'y')
  {
    switch(h)
    {
      case 1:
	return(dim_y_1);
	break;
      case 2:
	return(dim_y_2);
	break;
      case 3:
	return(dim_y_3);
	break;
    }
  }
};

int Tablero::getch(void)
{
  
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
    
};

void Tablero::ciclo()
{
  int tecl;
  tecl = getch();
  
 
    switch(tecl)
    {
      case 'w':
	tecla('w');
	break;       
      case 's':
	tecla('s');
	break;
      case 'a':
	tecla('a');  
	break;
      case 'd':
	tecla('d');
	break;
	
    }
  moverMonstruos();   //actualizamos posicion 
  quita_vidas();   //funcion que quita vidas al protagonista si hay un bicho cerca
  
  
};

void Tablero::tecla(char tecla)
{
  char norte,sur, este, oeste;   //donde guardamos lo que hay alrededor de la posicion del protagonista
  norte = pCelda[pProtagonista->get_posx_jugador()-1][pProtagonista->get_posy_jugador()].getCelda();
  sur = pCelda[pProtagonista->get_posx_jugador()+1][pProtagonista->get_posy_jugador()].getCelda();
  este = pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()+1].getCelda();
  oeste = pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()-1].getCelda();
  
  switch(tecla)
  {
    case 'w':  //subir
    switch(norte)
    {
      case '&':
	  pProtagonista->set_posx_jugador(pProtagonista->get_posx_jugador()-1);
	  pCelda[pProtagonista->get_posx_jugador()+1][pProtagonista->get_posy_jugador()].setCelda(' ');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  pProtagonista->set_Amuleto(TRUE);
	  break;	
      case ' ':
	if(sur == '#' && este != '#' && oeste != '#')
	{
	  pProtagonista->set_posx_jugador(pProtagonista->get_posx_jugador()-1);
	  pCelda[pProtagonista->get_posx_jugador()+1][pProtagonista->get_posy_jugador()].setCelda('+');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	}
	else if(sur != '#' && este != '#' && oeste != '#')
	{
	  pProtagonista->set_posx_jugador(pProtagonista->get_posx_jugador()-1);
	  pCelda[pProtagonista->get_posx_jugador()+1][pProtagonista->get_posy_jugador()].setCelda(' ');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	}
	break;
      case '+':
	if(sur == '+')
	{
	  pProtagonista->set_posx_jugador(pProtagonista->get_posx_jugador()-1);
	  pCelda[pProtagonista->get_posx_jugador()+1][pProtagonista->get_posy_jugador()].setCelda('#');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	}
	else if(sur == '#')
	{
	  pProtagonista->set_posx_jugador(pProtagonista->get_posx_jugador()-1);
	  pCelda[pProtagonista->get_posx_jugador()+1][pProtagonista->get_posy_jugador()].setCelda('#');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	}
	else if(sur == ' ')
	{
	  pProtagonista->set_posx_jugador(pProtagonista->get_posx_jugador()-1);
	  pCelda[pProtagonista->get_posx_jugador()+1][pProtagonista->get_posy_jugador()].setCelda(' ');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	}
	break;
      case '#':
	if(sur == '#')
	{
	  pProtagonista->set_posx_jugador(pProtagonista->get_posx_jugador()-1);
	  pCelda[pProtagonista->get_posx_jugador()+1][pProtagonista->get_posy_jugador()].setCelda('#');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	}
	else if(sur == '+')
	{
	  pProtagonista->set_posx_jugador(pProtagonista->get_posx_jugador()-1);
	  pCelda[pProtagonista->get_posx_jugador()+1][pProtagonista->get_posy_jugador()].setCelda('#');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	}
	else if(sur == ' ' && este != '#' && oeste != '#')
	{
	  pProtagonista->set_posx_jugador(pProtagonista->get_posx_jugador()-1);
	  pCelda[pProtagonista->get_posx_jugador()+1][pProtagonista->get_posy_jugador()].setCelda('+');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	}
	else if(sur == ' ' && este == '#' || oeste == '#')
	{
	  pProtagonista->set_posx_jugador(pProtagonista->get_posx_jugador()-1);
	  pCelda[pProtagonista->get_posx_jugador()+1][pProtagonista->get_posy_jugador()].setCelda('#');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	}
	break;
    }
    break;
    case 's':  //bajar
      switch(sur)
      {
	case '&':
	  pProtagonista->set_posx_jugador(pProtagonista->get_posx_jugador()+1);
	  pCelda[pProtagonista->get_posx_jugador()-1][pProtagonista->get_posy_jugador()].setCelda(' ');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  pProtagonista->set_Amuleto(TRUE);
	  break;
	case ' ':
	if(norte == '#' && este != '#' && oeste != '#')
	{
	  pProtagonista->set_posx_jugador(pProtagonista->get_posx_jugador()+1);
	  pCelda[pProtagonista->get_posx_jugador()-1][pProtagonista->get_posy_jugador()].setCelda('+');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	}
	else if(norte != '#' && este != '#' && oeste != '#')
	{
	  pProtagonista->set_posx_jugador(pProtagonista->get_posx_jugador()+1);
	  pCelda[pProtagonista->get_posx_jugador()-1][pProtagonista->get_posy_jugador()].setCelda(' ');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	}
	break;
      case '+':
	if(norte == '+')
	{
	  pProtagonista->set_posx_jugador(pProtagonista->get_posx_jugador()+1);
	  pCelda[pProtagonista->get_posx_jugador()-1][pProtagonista->get_posy_jugador()].setCelda('#');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	}
	else if(norte == '#')
	{
	  pProtagonista->set_posx_jugador(pProtagonista->get_posx_jugador()+1);
	  pCelda[pProtagonista->get_posx_jugador()-1][pProtagonista->get_posy_jugador()].setCelda('#');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	}
	else if(norte == ' ')
	{
	  pProtagonista->set_posx_jugador(pProtagonista->get_posx_jugador()+1);
	  pCelda[pProtagonista->get_posx_jugador()-1][pProtagonista->get_posy_jugador()].setCelda(' ');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	}
	break;
      case '#':
	if(norte == '#')
	{
	  pProtagonista->set_posx_jugador(pProtagonista->get_posx_jugador()+1);
	  pCelda[pProtagonista->get_posx_jugador()-1][pProtagonista->get_posy_jugador()].setCelda('#');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	}
	else if(norte == '+')
	{
	  pProtagonista->set_posx_jugador(pProtagonista->get_posx_jugador()+1);
	  pCelda[pProtagonista->get_posx_jugador()-1][pProtagonista->get_posy_jugador()].setCelda('#');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	}
	else if(norte == ' ' && este != '#' && oeste != '#')
	{
	  pProtagonista->set_posx_jugador(pProtagonista->get_posx_jugador()+1);
	  pCelda[pProtagonista->get_posx_jugador()-1][pProtagonista->get_posy_jugador()].setCelda('+');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	}
	else if(norte == ' ' && este == '#' || oeste == '#')
	{
	  pProtagonista->set_posx_jugador(pProtagonista->get_posx_jugador()+1);
	  pCelda[pProtagonista->get_posx_jugador()-1][pProtagonista->get_posy_jugador()].setCelda('#');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	}
	break;
    }
    break;
      case 'd':  //este
      switch(este)
      {
	case '&':
	  pProtagonista->set_posy_jugador(pProtagonista->get_posy_jugador()+1);
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()-1].setCelda(' ');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  pProtagonista->set_Amuleto(TRUE);
	  break;
	case ' ':
	  if(oeste == '#' && norte != '#' && sur != '#')
	  {
	  pProtagonista->set_posy_jugador(pProtagonista->get_posy_jugador()+1);
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()-1].setCelda('+');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  }
	  else if(oeste != '#' && norte != '#' && sur != '#')
	  {
	  pProtagonista->set_posy_jugador(pProtagonista->get_posy_jugador()+1);
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()-1].setCelda(' ');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  }
	  break;
	case '+':
	  if(oeste == ' ')
	  {
	  pProtagonista->set_posy_jugador((pProtagonista->get_posy_jugador())+1);
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()-1].setCelda(' ');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  }
	  else if(oeste == '#')
	  {
	  pProtagonista->set_posy_jugador((pProtagonista->get_posy_jugador())+1);
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()-1].setCelda('#');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  }
	  break;
	case '#':
	  if(oeste == '+')
	  {
	  pProtagonista->set_posy_jugador(pProtagonista->get_posy_jugador()+1);
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()-1].setCelda('#');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  }
	  else if(oeste == '#')
	  {
	  pProtagonista->set_posy_jugador(pProtagonista->get_posy_jugador()+1);
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()-1].setCelda('#');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  }
	  else if(oeste == ' ' && norte != '#' && sur != '#')
	  {
	  pProtagonista->set_posy_jugador(pProtagonista->get_posy_jugador()+1);
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()-1].setCelda('+');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  }
	  else if(oeste == ' ' && norte == '#' || sur == '#')
	  {
	  pProtagonista->set_posy_jugador(pProtagonista->get_posy_jugador()+1);
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()-1].setCelda('#');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  }
	  else if(oeste == '+')
	  {
	  pProtagonista->set_posy_jugador(pProtagonista->get_posy_jugador()+1);
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()-1].setCelda('#');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  }
	  break;
      }
      break;
      case 'a':  //oeste
      switch(oeste)
      {
	case '&':
	  pProtagonista->set_posy_jugador(pProtagonista->get_posy_jugador()-1);
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()+1].setCelda(' ');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  pProtagonista->set_Amuleto(TRUE);
	  break;
	case ' ':
	  if(este == '#' && norte != '#' && sur != '#')
	  {
	  pProtagonista->set_posy_jugador(pProtagonista->get_posy_jugador()-1);
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()+1].setCelda('+');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  }
	  else if(este != '#' && norte != '#' && sur != '#')
	  {
	  pProtagonista->set_posy_jugador(pProtagonista->get_posy_jugador()-1);
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()+1].setCelda(' ');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  }
	  break;
	case '+':
	  if(este == ' ')
	  {
	  pProtagonista->set_posy_jugador((pProtagonista->get_posy_jugador())-1);
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()+1].setCelda(' ');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  }
	  else if(este == '#')
	  {
	  pProtagonista->set_posy_jugador((pProtagonista->get_posy_jugador())-1);
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()+1].setCelda('#');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  }
	  break;
	case '#':
	  if(este == '+')
	  {
	  pProtagonista->set_posy_jugador(pProtagonista->get_posy_jugador()-1);
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()+1].setCelda('#');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  }
	  else if(este == '#')
	  {
	  pProtagonista->set_posy_jugador(pProtagonista->get_posy_jugador()-1);
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()+1].setCelda('#');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  }
	  else if(este == ' ' && norte != '#' && sur != '#')
	  {
	  pProtagonista->set_posy_jugador(pProtagonista->get_posy_jugador()-1);
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()+1].setCelda('+');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  }
	  else if(este == ' ' && norte == '#' || sur == '#')
	  {
	  pProtagonista->set_posy_jugador(pProtagonista->get_posy_jugador()-1);
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()+1].setCelda('#');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  }
	  else if(este == '+')
	  {
	  pProtagonista->set_posy_jugador(pProtagonista->get_posy_jugador()-1);
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()+1].setCelda('#');
	  pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()].setCelda('@');
	  }
	  break;
      }
      break;
	  
	    
	    
	  
  }
};  
	  

void Tablero::quita_vidas()
{
  int vidas = 0;
  bool espada;
  vidas = pProtagonista->get_Vida();
  espada = pProtagonista->get_espada();
  
  if(espada == TRUE)
  {  
      if((pCelda[pProtagonista->get_posx_jugador()-1][pProtagonista->get_posy_jugador()].getCelda()) == 'O' )  //norte 
      {
	pCelda[pProtagonista->get_posx_jugador()-1][pProtagonista->get_posy_jugador()].setCelda(' '); //limpiamos bicho
	pProtagonista->set_espada(FALSE);  // SE QUEDA SIN ESPADA
	for(int i = 0;i<9;i++)
	{  //ahora buscamos al monstruo
	  if( (pProtagonista->get_posx_jugador()-1) == pMonstruo[i].get_posx_enemigo() && pProtagonista->get_posy_jugador() == pMonstruo[i].get_posy_enemigo())
	   mata_monstruo(i);
	}	
      }
      else if((pCelda[pProtagonista->get_posx_jugador()+1][pProtagonista->get_posy_jugador()].getCelda()) == 'O' )  //sur
      {
	pCelda[pProtagonista->get_posx_jugador()+1][pProtagonista->get_posy_jugador()].setCelda(' '); //limpiamos bicho
	pProtagonista->set_espada(FALSE);  // SE QUEDA SIN ESPADA
	for(int i = 0;i<9;i++)
	{
	  if( (pProtagonista->get_posx_jugador()+1) == pMonstruo[i].get_posx_enemigo() && pProtagonista->get_posy_jugador() == pMonstruo[i].get_posy_enemigo())
	   mata_monstruo(i);
	}
	
      }
	
      else if((pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()+1].getCelda()) == 'O' )  //este
      {
	pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()+1].setCelda(' '); //limpiamos bicho
	pProtagonista->set_espada(FALSE);  // SE QUEDA SIN ESPADA
	for(int i = 0;i<9;i++)
	{
	  if( (pProtagonista->get_posx_jugador()) == pMonstruo[i].get_posx_enemigo() && pProtagonista->get_posy_jugador()+1 == pMonstruo[i].get_posy_enemigo())
	  mata_monstruo(i);
	}
	
      }  
      else if((pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()-1].getCelda()) == 'O' )   //oeste
      {
	pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()-1].setCelda(' '); //limpiamos bicho
	pProtagonista->set_espada(FALSE);  // SE QUEDA SIN ESPADA
	for(int i = 0;i<9;i++)
	{
	  if( (pProtagonista->get_posx_jugador()) == pMonstruo[i].get_posx_enemigo() && pProtagonista->get_posy_jugador()-1 == pMonstruo[i].get_posy_enemigo())
	   mata_monstruo(i);
	}
	
      }    
  }
  else if(espada == FALSE)
  {
    
    if((pCelda[pProtagonista->get_posx_jugador()-1][pProtagonista->get_posy_jugador()].getCelda()) == 'O' )  //norte 
      pProtagonista->set_Vida(vidas-1); 
    else if((pCelda[pProtagonista->get_posx_jugador()+1][pProtagonista->get_posy_jugador()].getCelda()) == 'O' )  //sur
      pProtagonista->set_Vida(vidas-1); 
    else if((pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()+1].getCelda()) == 'O' )  //este
      pProtagonista->set_Vida(vidas-1);
    else if((pCelda[pProtagonista->get_posx_jugador()][pProtagonista->get_posy_jugador()-1].getCelda()) == 'O' )   //oeste
      pProtagonista->set_Vida(vidas-1); 
  }
  
}; 

void Tablero::mata_monstruo(int i)
{
  pMonstruo[i].set_vivo(FALSE);
};
  

  

int Tablero::vidas()
{
  return(pProtagonista->get_Vida());
};

bool Tablero::amuleto()
{
  return(pProtagonista->get_Amuleto());
};


Tablero::~Tablero()
{
  for(int i=0;i<ancho_tablero;i++)
    delete[] pCelda[i];
  delete[] pCelda;
  delete pProtagonista;
  delete[] pMonstruo;
  
};




  