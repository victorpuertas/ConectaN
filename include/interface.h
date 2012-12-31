/**
* @file interface.h
* @author Victor M. Puertas Garcia.
* @version 0.00.05
* @date Mayo - 2005
* @brief Contiene las cabeceras de la clase interface, encargada de la parte
* grafica.
*/
#ifndef __INTERFACE_H
#define __INTERFACE_H

#include <string>
#include <iostream>
#include "configuracion.h"
#include "tablero.h"
#include "jugador.h"
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_audio.h"

/**
* @brief Mezcla el audio.
* Funcion que es llamada en segundo plano para incorporar el sonido al stream de audio.
*/
extern void mixaudio(void *unused, Uint8 *stream, int len);

//Atributos para los lienzos de dibujo
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    #define rmask 0xff000000
    #define gmask 0x00ff0000
    #define bmask 0x0000ff00
    #define amask 0x000000ff
#else
    #define rmask 0x000000ff
    #define gmask 0x0000ff00
    #define bmask 0x00ff0000
    #define amask 0xff000000
#endif
using namespace std;

/**
* @class interface
* @brief Clase tablero.
* Se encarga de manejar la parte grafica de Conecta N.
*/
class interface
{
  public:
/**
* @var resolucion_h 
* Resolucion vertical de la pantalla. Utilizada: 768. 
*/
  int resolucion_h;
/**
* @var resolucion_w
* Resolucion horizontal de pantalla. Utilizada: 1024.
*/
  int resolucion_w; //Resolucion de pantalla.
/**
* @brief Constructor.
* Inicia los valores por defecto de la clase.
* @param config Estructura de configuracion.
*/
  interface(conecta_conf config);
  
/**
* @brief Inicia el modo grafico.
* Inicia los modulos video y audio de la SDL. El modo de video utilizado es 1024 x 768. La
* estructura de sonido es iniciada para archivos WAV con una frecuencia de 44100 Hz con 2
* canales (estereo) y con un formato de 16 bit. Se establece tambien la funcion que se 
* ejecutara en segundo plano para mezclar el buffer de audio con el stream de audio.
* @return 0 : No huvo ningun problema.
* @return 1 : Error al iniciar los modulos de la SDL.
* @return 2 : Error al iniciar el modo grafico establecido.
*/
     int iniciar();
     
/**
* @brief Muestra la presentacion.
* Muestra la presentacion y carga el archivo de recursos con todos los graficos necesarios
* para el juego.
* @return 0 : No huvo ningun problema.
* @return 1 : Error.
*/
     int presentacion();

/**
* @brief Muestra el menu del juego.
* Muestra el menu con las opciones de comenzar juego o salir. Este metodo es llamado en el
* bucle del juego.
*/      
     void menu();
/**
* @brief Crea un tablero grafico de juego.
* Crea un tablero grafico de juego con las filas y columnas especificadas.
* @param filas Filas del tablero.
* @param columnas Columnas del tablero.
*/     
     void dibujar_tablero(int filas, int columnas);
/**
* @brief Muestra el fin de juego en el lienzo de pantalla.
*/          
     void game_over();

/**
* @brief Muestra la cuentra atras para el comienzo en el lienzo de pantalla.
*/          
     void tres_dos_uno();         

/**
* @brief Muestra el jugador ganador en el lienzo de pantalla.
* @param jugador 1 - Jugador 1. \n
*		 2 - Jugador 2.
*/    
     void ganador(int jugador); 

/**
* @brief Obtiene el tubo pulsado por el usuario.
* @return Columna seleccionada por el usuario. Esta sera utilizada posteriormente para
* realizar un movimiento en la clase tablero.
*/  
     int obtener_columna();
    
/**
* @brief Animacion de caer la bola desde un tubo.
* @param color Color de la bola:\n
*			0 : Azul\n 
*			1 : Rosa.
* @param tubo Tubo o columna en el que hechar la bola.
* @param fila Fila en la que para la bola.
*/   
     void hechar_bola(int color,int tubo,int fila);
     
/**
* @brief Devuelve la tecla pulsada.
* @return Codigo de la tecla pulsada.
*/         
     int ObtenerTecla();
  
/**
* @brief Escribe los puntos de un jugador en el lienzo de pantalla.
* @param puntos1 Puntos del jugador 1.
* @param x Coordenada x de pantalla para mostrar los puntos del jugador 1.
* @param y Coordenada y de pantalla para mostrar los puntos del jugador 1.
* @param puntos2 Puntos del jugador 2.
* @param x2 Coordenada x de pantalla para mostrar los puntos del jugador 2.
* @param y2 Coordenada y de pantalla para mostrar los puntos del jugador 2.
*/         
     void escribir_puntos(int puntos1,int x,int y,int puntos2,int x2,int y2);
     
/**
* @brief Escribe mensajes de estado en el lienzo de pantalla.
* @param texto Mensaje de estado.
*/         
     void escribir_estado(string texto);  
     
/**
* @brief Marca la combinacion de bolas ganadoras de la partida en el lienzo de pantalla.
* @param bolas Vector que contiene las coordenadas de la combinacion ganadora.
* @pre Debe de haber un ganador de partida para que el vector de coordenadas sea valido.
*/              
     void dibujar_ganadoras(coordenadas * bolas);      
     
/**
* @brief Dibuja el turno del jugador en el lienzo de pantalla.
* @param jugador Jugador del que deseas mostrar el turno.\n
* Valores:\n 
* 		1 - Jugador 1.\n
* 		2 - Jugador 2.
*/   
     void dibujar_jugador(int jugador);
/**
* @brief Reproduce un archivo WAV.
* Reproduce el sonido contenido en el buffe de sonido.
* @param opciones Opciones para la reproduccion de sonido. \n
* 1 : Comenzar la reproduccion.\n
* 0 : Para la reproduccion actual y cierra el dispositivo de audio.
* @pre El archivo debe estar cargado con el metodo cargar_wav.
*/             
     void PlaySound(int opciones);   

/**
* @brief Carga un archivo WAV.
* Carga un archivo de audio en el buffer de sonido.
* @param archivo Nombre del archivo a cargar.
*/                 
     void cargar_wav(string archivo);
     
/**
* @brief Libera el buffer de audio previamente cargado.
* Libera el buffer de audio.
*/             
     void liberar_wav();

/**
* @brief Convierte un numero a string.
* @param numero Entero a convertir.
*/         
     string inttochar(long int numero);
               
  private:
     
     conecta_conf conf_interna;	    //Permite leer la configuracion.		
     
     int numero_tubos;		    //Numero de tubos que se dibujan.
     int altura_bola[12];
     int *coordenadas_tubos;
     
     //Lienzo de pantalla principal: buffer_blanco.
     SDL_Surface *buffer_blanco,*recursos;
      
/**
* @brief Efecto: Aparece y desaparace una imagen.
* Efecto: Aparece y desaparace una imagen mediante el color Alpha.
* @param src Buffer orifen que contiene una imagen.
* @param c_src Coordenadas del cuadro que se copiara al destino.
* @param dst Buffer destino.
* @param c_dst Coordenadas del cuadro destino.
* @return 0 Ningun problema.
* @return 1 Error al asignar el color transparente.
* @return 2 Error al asignar el canal Alpha.
* @return 3 Error al realizar el Blit.
*/
     int efecto_apar_desa(SDL_Surface *src, SDL_Rect *c_src, SDL_Surface *dst, SDL_Rect *c_dst);
     
/**
* @brief Efecto: Aparece y desaparace una imagen.
* Efecto: Aparece y desaparace una imagen mediante el color Alpha.
* @param fich Cadena que contiene la direccion del fichero de imagen. Los formatos
* permitidos son los soportados por la SDL.
* @return Buffer de pantalla.
*/
     SDL_Surface *LeerImagenBMP(string fich);

/**
* @brief Mezcla una imagen en pantalla.
* Efecto: Aparece una imagen en pantalla.
* Color Transparente: Negro.
* @param src Buffer orifen que contiene una imagen.
* @param c_src Coordenadas del cuadro que se copiara al destino.
* @param dst Buffer destino.
* @param c_dst Coordenadas del cuadro destino.
*/
     void DibujarImagen(SDL_Surface *src, SDL_Rect *c_src, SDL_Surface *dst, SDL_Rect *c_dst);

/**
* @brief Mezcla una imagen en pantalla sin actualizar el lienzo principal.
* Color Transparente: Negro.
* @param src Buffer orifen que contiene una imagen.
* @param c_src Coordenadas del cuadro que se copiara al destino.
* @param dst Buffer destino.
* @param c_dst Coordenadas del cuadro destino.
*/     
     void volcar_lienzo(SDL_Surface *src, SDL_Rect *c_src, SDL_Surface *dst, SDL_Rect *c_dst);     
/**
* @brief Crea un buffer de pantalla.
* Crea un SDL_Surface.
* @param width Ancho del buffer.
* @param height Largo del buffer.
* @return Buffer de pantalla.
*/
     SDL_Surface *crear_surface(int width,int height);

/**
* @brief Borra un buffer de pantalla.
*/
     void LimpiarVentana(SDL_Surface *ventana);   
 
/**
* @brief Dibuja un rectangulo.
*/
     void RectanguloR(int x1, int y1, int x2, int y2,unsigned char r, unsigned char g, unsigned char b);
     
/**
* @brief Dibuja las columnas laterales del tablero de juego.
*/
     void dibujar_columnas();

/**
* @brief Dibuja el mosaico de fondo del tablero.
*/     
     void dibujar_fondo();

/**
* @brief Dibuja las barras de comunicaciones de la puntuacion...
*/     
     void dibujar_barra();
     
/**
* @brief Dibuja los titulos basicos en pantalla.
*/    
     void dibujar_titulos();
     
/**
* @brief Dibuja numeros en un lienzo.
* @param numero Numero a dibujar.
* @param y Coordenada Y.
*/        
     void escribir_numero(string numero,int x,int y);
     
/**
* @brief Dibuja tubos para hechar la bola.
* @param numero Numero de tubos.
*/             

     void tubos(int numero);
   
/**
* @brief Dibuja la barra de estado.
*/    
     void dibujar_barra_estado();   
     
     void Texto(int x, int y, const char *c,
             unsigned char r, unsigned char g, unsigned char b);    
	     
/**
* @brief Dibuja la barra de estado.
*/ 
     	
   
/**
* @brief Obtiene un punto de color de un lienzo.
*/      
     void ObtenerPunto(SDL_Surface *ventana,int x, int y,unsigned char &r, unsigned char &g, unsigned char &b);
 
/**
  * @brief Espera hasta que se pulsa uno de los botones del rat�
  * @param x coordenada horizontal (columna) del rat� en el momento de la pulsaci�
  * @param y coordenada vertical (fila) del rat� en el momento de la pulsaci�
  * @return un entero que codifica el bot� pulsado (1=izquierdo, 2=central, 3=derecho)
  * @post Las coordenadas del rat� en el momento de la pulsaci� se obtienen en (@a x, @a y)
  */
     int ObtenerClick(int &x, int &y);
};
#endif
