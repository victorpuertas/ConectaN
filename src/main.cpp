/**
*@file main.cpp
*@author Victor M. Puertas Garcia.
*@version 0.00.05
*@brief Contiene la implementacion de Conecta_n.
*/
#include <iostream>
#include <string>
#include "configuracion.h"
#include "tablero.h"
#include "jugador.h"
#include "interface.h"

using namespace std;

/**
* @brief Comienza una partida en modo grafico.
* @param mi_configuracion Estructura de configuracion.
* @param entorno_graf Funciones para manejar graficos del juego.
* @param player Jugadores del tablero.
*/
void comenzar_partida(conecta_conf mi_configuracion,interface & entorno_graf,jugadores & player)
{
 tablero panel_juego(mi_configuracion.columnas,mi_configuracion.filas,mi_configuracion.linea);
  
 //Etablecemos el tablero de juego con el que trabajaran los jugadores:
  player.set_tablero(&panel_juego);
  
  entorno_graf.dibujar_tablero(mi_configuracion.filas,mi_configuracion.columnas);
  entorno_graf.escribir_estado("Conecta N 2005. (c) 2005, Victor Puertas. vpg12@correo.ugr.es");   
  entorno_graf.escribir_puntos((player.info(1)).puntos,30,45,(player.info(2)).puntos,entorno_graf.resolucion_w-106-30,45);  
  
  int salida;
  entorno_graf.tres_dos_uno();
  do
  {
         salida=player.jugada(); 
     
  }while(salida==0);

  if(salida==1)
  {
    entorno_graf.dibujar_ganadoras(panel_juego.fichas);
    entorno_graf.ganador(player.turno_actual());    
  }
}
/**
* @brief Comienza una partida sin entorno grafico en la que solo aparecen los puntos
* obtenidos por cada jugador en la consola.
* @param mi_configuracion Estructura de configuracion.
* @param player Jugadores del tablero.
*/
void partida_texto(conecta_conf mi_configuracion,jugadores & player)
{
  tablero panel_juego(mi_configuracion.columnas,mi_configuracion.filas,mi_configuracion.linea);
  
 //Etablecemos el tablero de juego con el que trabajaran los jugadores:
  player.set_tablero(&panel_juego);
   
  int salida;
 
  do
  {
         salida=player.jugada(); 
     
  }while(salida==0);
}


/**
* @brief Bloque de comienzo de Conecta N.
* @param num_arg Numero de argumentos pasados desde la consola.
* @param arg Vector de cadenas de caracteres que contiene los argumentos pasados.
*/
int main(int num_arg, char * arg[])
{
  conecta_conf mi_configuracion; //Estructura que contiene la configuracion.
  configuracion conf_general;
  jugadores::jugador player_info;
  int partidas; 		//Numero de partidas a jugar en modo texto.
  
  //Cargamos configuracion
  mi_configuracion=conf_general.actualizar("../config/config.cfg");
  switch(mi_configuracion.turno)
  {
    case 100:
      cout<<"ERROR: en la apertura de archivo.\n";
      exit(0);
      
    case 101:
      cout<<"ERROR: archivo de configuración corrupto.\n";
      exit(0);
  }
  
  
  
  //Iniciamos objetos:
  interface entorno_graf(mi_configuracion);
  jugadores player_texto(mi_configuracion);  
  jugadores player(mi_configuracion,entorno_graf);
  
  
  if(num_arg==2)
  {
    
       
    partidas=atoi(arg[1]);
    cout<<"---------------------------------------\n";
    cout<<"     Modo texto de Conecta N 2005\n";
    cout<<"---------------------------------------\n";
    cout<<"Número de partidas a jugar: "<<partidas<<endl<<endl<<"Resultados:\n";
    
    if(mi_configuracion.nivel1<1 || mi_configuracion.nivel2<1)
      {
        cout<<"Para jugar en modo texto es necesario que el nivel de los jugadores sea\n";
	cout<<"1 o 2.\n\n";
      }
    else
    {
     while(partidas>0)
     {
      partida_texto(mi_configuracion,player_texto);
      partidas--;
     }   
     cout<<"\tNombre\t\tNivel\tPuntos\n";
     cout<<"\t"<<(player_texto.info(1)).nombre<<"\t\t"<<(player_texto.info(1)).nivel<<"\t"<<(player_texto.info(1)).puntos<<endl;
    
     cout<<"\t"<<(player_texto.info(2)).nombre<<"\t\t"<<(player_texto.info(2)).nivel<<"\t"<<(player_texto.info(2)).puntos<<endl<<endl;
    
     cout<<"Conecta N 2005 ver:0.00.05\n(c) VPG - Víctor Puertas García, 2005\n";
     cout<<"Desarrollado para la practica de MP2 de la ";
     cout<<"Universidad de Granada.\n";
    }//Fin del la condicion del nivel.
   } 
  else
  {     
    //Iniciamos la parte grafica:
    entorno_graf.iniciar();
    entorno_graf.presentacion();
    while(1)
    {
      entorno_graf.menu();
      comenzar_partida(mi_configuracion,entorno_graf,player);
    }   
  }
  
  return 0; 
}
