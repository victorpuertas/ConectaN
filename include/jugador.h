/**
* @file jugador.h
* @author Victor M. Puertas Garcia.
* @version 0.00.05
* @date Mayo - 2005
* @brief Contiene las cabeceras de la clase jugador.
*/
#ifndef __JUGADOR_H
#define __JUGADOR_H

#include<string>
#include<cstdlib>
#include<ctime>
#include"configuracion.h"
#include"tablero.h"
#include "interface.h"

using namespace std;

/**
* @class jugadores
* @brief Clase jugador.
* Se encarga de manejar a los jugadores.
*/
class jugadores
{
  public:

/**
* @struct jugador Contiene la informacion de un jugador.
*/
  struct jugador
  {
    //! Nombre del jugador.
    string nombre;
    //! Nivel del jugador. \n \n 
    //! Nivel 0 : Moviento manual.\n
    //! Nivel 1 : Insercion automatica aleatoria.\n
    //! Nivel 2 : Insercion automatica con inteligencia minima.  
    int nivel;	
    //! Puntos acumulados.   
    int puntos;
  };
     
/**
* @brief Contructor.
* Crea una instancia de jugadores.
* @param config Estructura de configuracion.
* @param graf Objeto de tipo interface que conntiene los metodos para controlar la 
* parte grafica.
*/  
  jugadores(conecta_conf config,interface &graf);

/**
* @brief Contructor para MODO TEXTO.
* Crea una instancia de jugadores.
* @param config Estructura de configuracion.
*/    
  jugadores(conecta_conf config);
  
/**
* @brief Contiene el turno del jugador.
* @return 1 Turno del jugador 1.
* @return 2 Turno del jugador 2.
*/
   int turno_actual();
   
  /**
* @brief Establece el tablero de juego.
* Especifica el tablero de juego para los jugadores.
* @param campo Especifica el objeto tablero con el que trataran los jugadores.
*/  
  void set_tablero(tablero * campo);

/**
* @brief Informacion del jugador.
* Devuelve informacion del jugador seleccionado.
* @pre El parametro jugador debe ser 1 o 2, dependiendo del jugador del que se 
* desee obtener la informacion.
*/
   jugador info(int player);

/**
* @brief Realiza una jugada.
* Realiza una insercion de ficha por parte del jugador actual.\n Una vez
* terminada la jugada se cambia automaticamente el turno.
* @return 0 : Se realizo la jugada.
* @return 1 : Hay ganador de partida.
* @return 2 : La partida termino sin ganador.
* @return 3 : Columna completa.
* @return 4 : Se ha producido un error.
*/
   int jugada();
   
  
  private:
  
  bool modo_texto;
  int turno_interno;
  jugador player1,player2;	//Informacion de los jugadores.
  conecta_conf cof_interna;
  tablero *zona_juego;		//Tablero con el que jugar.
  interface *graficos;		//Interface grafica.
  int fichas_hechadas;	//Numero de fichas que ha hechado un jugador en el turno.
  
/**
* @brief Cambia de turno.
* Cambia el turno actual. 
*/
  void cambiar_turno();

/**
* @brief Genera una columna.
* Genera un numero columna aleatoria del tablero. 
*/
  int columna_aleatoria();
  
/**
* @brief Genera una columna.
* Genera un numero columna con un nivel de inteligencia. 
*/
  int heuristica(int jugador);
  
/**
* @brief Incrementa la puntuacion.
* Incrementa la puntuacion del jugador con seguridad.De esta forma al llegar a la puntuacion
* maxima, se inicializa. 
* @param puntos Numero de puntos a incrementar.
* @param jugador Jugador al que se le incrementan los puntos. \n
* 1 : Jugador 1. \n
* 2 : Jugador 2.
*/
  void add_point(int puntos,int jugador);  
};
#endif
