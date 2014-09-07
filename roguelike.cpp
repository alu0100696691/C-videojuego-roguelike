#include "tablero.h"

int main()
{
  char fichero[] = "Mazmorra_30_30.dat";
  char tecla;
  
  
  
  
  
  
  
  
  
  system("clear");
    cout<<"                         *                *                   *     "<<endl;
    cout<<"             *                                     *                "<<endl;
    cout<<"     *              |           *             *        *         *  "<<endl;
    cout<<"          *        -+-                 *                            "<<endl;
    cout<<"       __           |      *             *          *        *      "<<endl;
    cout<<"   ___|  |   *     _|_              *    ____    ____               "<<endl;
    cout<<"   [_]|같|__      _| |_        *    |   |....|  |....|    *     *   "<<endl;     
    cout<<"      |     |   _|[] []|_    ___    |   |....|  | ___|__            "<<endl;
    cout<<"   [_]|  같 |__|_  ______|  |   |  |_|  |....|  || -- - |   *     * "<<endl;
    cout<<"      |________  |__     |  |# #|  |_|  |....|  || - -- |  _____    "<<endl;
    cout<<"   [_]| _____ |     |__[]|  |   |  |_|  |....|__|| -- - | |* * *|   "<<endl;
    cout<<"      | [___] |        |__  |# #|  |_|  |....|__|| -- -_|_|* * *|   "<<endl;
    cout<<"   [_]|       | 같        | |   |__| |__|....|  || ___|* *|* * *|   "<<endl;
    cout<<"      | _____ |           |__  #|_______|....|  | |* *|* *|* * *|   "<<endl;    
    cout<<"   [_]| [___] |       같     |__|_______|__  |  | |* *|* *|* * *|   "<<endl;
    cout<<"      |       |            __|_____________|__    |* *|* *|* * *|   "<<endl;
    cout<<"   [_]| _____ |  같      _|___________________|_  |* *|* *|* * *|   "<<endl;
    cout<<"      | [___] |         |_______________________|  ______________   "<<endl;
    cout<<"    __|_______|_________|_______________________| _________________ "<<endl;
    cout<<"   |_______________________________________________________________|"<<endl;
    cout<<"   |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
    cout<<"   ||||||||||||||||||||ROGUELIKE||||||||||||||||||||||||||||||||||||"<<endl;
    cout<<"   ||||||||||||PRACTICA 1 ALGORITMOS AVANZADOS||||||||||||||||||||||"<<endl;
    cout<<"   |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
    cout<<"   |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
    cout<<"   |||||||||Creado por: Jose Antonio Rodriguez leandro||||||||||||||"<<endl;
    cout<<"   |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"<<endl;
    
         
  cout << "\n\nFichero de donde se lee la mazmorra: " << fichero << endl;
  cout << "Pulse una tecla para continuar o X para cambiar nombre.\n";
  cin >> tecla;
  
  
  if(tecla == 'x' || tecla == 'X')
    cin >> fichero;
  
  
  
  Tablero mazmorra(fichero);
  
  system("clear");
     
  while(mazmorra.vidas() > 0 && mazmorra.amuleto() == FALSE)
  {
  mazmorra.mostrarMazmorra();
  mazmorra.ciclo();
  cout << "VIDAS: " << mazmorra.vidas();
  system("clear");
  
  }
  if(mazmorra.amuleto() == TRUE && mazmorra.vidas() >= 0)
    cout << "\nHA GANADO!!!!!" << endl;
  else
    cout << "\nHA PERDIDO." << endl;
  
  return 0;
};
