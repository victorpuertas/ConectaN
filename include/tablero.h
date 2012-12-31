/**
* @file tablero.h
* @author Victor M. Puertas Garcia.
*@version 0.00.05
* @brief Contiene las cabeceras de la clase tablero.
*/
#ifndef __TABLERO_H
#define __TABLERO_H
struct coordenadas
  {
    int fila;
    int columna;
  };

/**
* @class tablero
* @brief Clase tablero.
* Se encarga de manejar un tablero de juego.
*/
class tablero
{
  public:
  
/**
* @var int *fichas 
* @brief Puntero a un vector con las coordenadas de las n-fichas
* conectadas.
*/
   coordenadas *fichas;

/**
* @brief Contructor.
* Crea un tablero con los valores por defecto: 4 filas y 4 columnas. Se deben de conectar 3 fichas.
*/ 
  tablero();
  
/**
* @brief Contructor de copia.
* Crea un tablero a partir de otro.
*/ 
  tablero(const tablero &origen);
   
/**
* @brief Contructor.
* Crea un tablero con los valores pasados como argumentos.
* @param columnas Numero de columnas del tablero.
* @param filas Numero de filas del tablero.
* @param conecta Numero de fichas a conectar para ganar una partida.
*/ 
   tablero(int columnas,int filas,int conecta);

/**
* @brief Destructor.
*/
   ~tablero();
   
/**
* @brief Operador de asignacion.
* @return Objeto de tipo tablero.
*/
   tablero & operator=(const tablero & origen);
/**
* @brief Se encarga de realizar una insercion de ficha en el tablero. 
* @pre color debe ser 0 : negro           1 : blanco.
* @param color Color de la ficha.
* @param columna Columna donde se insertara la ficha.
* @return 0 : Se realizo el movimiento.
* @return 1 : Hay ganador de partida.
* @return 2 : La partida termino sin ganador.
* @return 3 : Columna completa.                                                            
*/ 
   int movimiento(int columna,int color);
   
/**
* @brief Elimina una ficha del tablero.
* Elimina una ficha del tablero SIN MOVER LAS FICHAS A LAS QUE AFECTE.
* @param col Numero de columna.
* @param fil Numero de fila.
*/      
   void deshacer_jugada(int fil,int col);   
 
/**
* @brief Se encarga de obtener la posicion de la ficha mas alta de una columna. 
* @param columna Columna de la que conocer la posicion.
* @return Posicion de la ultima ficha insertada.
*/
   int alto_columna(int columna); 
   
/**
* @brief Se encarga de obtener la posicion de la ficha mas alta con las coordenadas de
* pantalla. 
* @param columna Columna de la que conocer la posicion.
* @return Indice de desplazamiento en el vector de celdas de pantalla.
*/   
   int alto_columna_graf(int columna);
        
  private:
   int conecta_n;		//Conecta_n especifica las fichas a conectar.
   int color_actual;		//Almacena el color de fichas con el que trabaja.
   struct
   {
	int filas;
	int columnas;
	int **mt;
   }Matriz;

/**
* @brief Comprueba una jugada.
* Se encarga de comprobar si hay n-fichas conectadas despues de cada insercion.
* @return True  : Hay ganador. False : No hay ganador.
*/ 
   bool test();
   
/**
* @brief Inserta una ficha.
* Se encarga de insertar una ficha de un color en la matriz del tablero. 
* @param Col Numero de columnas.
* @param fil Numero de filas.
* @param color Color de la ficha a insertar.
*/
   void insertar(int col,int fila);
   
/**
* @brief Crea el tablero.
* Se encarga de crear la matriz del tablero. Este metodo es llamado por los
* constructores de la clase
* @param C Numero de columnas. Por defecto hay 4.
* @param f Numero de filas. Por defecto hay 4.
*/
   void CrearMatriz(int c=4, int f=4);
};
#endif
