/**
* @file configuracion.h
* @author Victor M. Puertas Garcia.
* @version 0.0
* @brief Contiene las cabeceras de la clase configuracion.
*/
#ifndef __CONFIG_H
#define __CONFIG_H
#include <fstream>
#include <string>
using namespace std;

/**
* @struct conecta_conf Contiene la configuracion.
*/
struct conecta_conf
{
  //! Ruta de los archivos de imagen.
  string recursos;
  //! Especifica el estilo seleccionado.
  string tema;
  //! Nombre del JUGADOR 1.
  string jugador1;
  //! Nombre del JUGADOR 2.
  string jugador2;
  //! Tiempo de espera despues de cada movimiento. En Milisegundos.
  int tiempo;
  //! Numero de filas del tablero.
  int filas;
  //! Numero de columnas del tablero.
  int columnas;
  //! Numero de fichas a conectar para ganar.
  int linea;
  //! Numero de fichas que se insertan en cada turno.
  int Nfichas;
  //! Nivel del JUGADOR 1.
  int nivel1;
  //! Nivel del JUGADOR 2.
  int nivel2;
  //! Jugador que comienza una partida.
  int turno;
};

/**
* @class configuracion
* @brief Clase configuracion.
* Se encarga de obtener los parametros de configuracion de un archivo.
*/
class configuracion
{
 public:
/**
*@brief Obtiene los parametros de configuracion del archivo.
*Se encarga de abrir un archivo de configuracion y obtener sus parametros. Por defecto
*el archivo de configuracion se llama: config.cfg situado en /config
*@param nombre Cadena que contiene la ruta del archivo de configuracion.
*@return Una esttructura con la configuracion. En caso de error la devuelve con
* el codigo de error en el campo turno. Valores:
*@return 100 Error durante la apertura del archivo.
*@return 101 La cebecera del archivo de configuracion no es correcta.
*/ 
      conecta_conf actualizar(string nombre);
};
#endif
