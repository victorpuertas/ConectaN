/**
\file tablero.cpp
\author Victor M. Puertas Garcia.
*@version 0.00.05
\brief Contiene la implementacion de la clase tablero.
*/
#include"tablero.h"
#include<iostream>
using namespace std;
/**
  @brief Contructor.
  Crea un tablero con los valores por defecto: 4 x 4.
*/ 
tablero::tablero()
{
  CrearMatriz();
  fichas=0;		//Puntero nulo.
  conecta_n=3;
  fichas=new coordenadas[conecta_n];
}

/**
@brief Contructor.
Crea un tablero con los valores pasados como argumentos.
@param Columnas Numero de columnas del tablero.
@param filas Numero de filas del tablero.
@param conecta Numero de fichas a conectar para ganar una partida.
*/ 
tablero::tablero(int columnas,int filas,int conecta)
{
  CrearMatriz(columnas,filas);
  fichas=0;		//Puntero nulo
  conecta_n=conecta;	//Nº de fichas a conectar para ganar.
  fichas=new coordenadas[conecta_n];
}

tablero::tablero(const tablero &origen)
{
  CrearMatriz(origen.Matriz.columnas,origen.Matriz.filas);
  fichas=0;						//Puntero nulo
  conecta_n=origen.conecta_n;				//Nº de fichas a conectar para ganar.
  
  //Copiamos los datos del tablero:
	for(int a=0;a<Matriz.filas;++a)
	   for(int b=0;b<Matriz.columnas;++b)
	       Matriz.mt[a][b]=origen.Matriz.mt[a][b];
}

void tablero::CrearMatriz(int c, int f)
{
	Matriz.mt= new int*[f];			//Creamos las filas.
	for(int i=0;i<f;++i)
		Matriz.mt[i]=new int[c];	//Creamos las columnas.
	Matriz.filas=f;				//Asignamos valores...
	Matriz.columnas=c;
	
	//Inicializamos todo a 2, marca de vacio:
	for(int a=0;a<Matriz.filas;++a)
	   for(int b=0;b<Matriz.columnas;++b)
	       Matriz.mt[a][b]=2;
}

tablero::~tablero()
{
  for(int i=0;i<Matriz.filas;++i)	
      delete [] Matriz.mt[i];
  delete [] Matriz.mt;
  
  //Eliminar el vector de las fichas seleccionadas:
  delete [] fichas;
}

tablero & tablero::operator=(const tablero & origen)
{
  int **mt_aux;
  mt_aux=Matriz.mt;
  
  CrearMatriz(origen.Matriz.columnas,origen.Matriz.filas);
  fichas=0;						//Puntero nulo
  conecta_n=origen.conecta_n;				//Nº de fichas a conectar para ganar.
  
  //Copiamos los datos del tablero:
	for(int a=0;a<Matriz.filas;++a)
	   for(int b=0;b<Matriz.columnas;++b)
	       Matriz.mt[a][b]=origen.Matriz.mt[a][b];
	       
  for(int i=0;i<Matriz.filas;++i)	
      delete [] mt_aux[i];
      
  delete [] mt_aux;
  cout<<"asigno valor\n";
  return(*this);
}

bool tablero::test()
{

  //Comprobacion por filas:
    for(int a=0;a<Matriz.filas;++a) 		//Recorre todas las filas.
  	for(int b=0;b<=(Matriz.columnas-conecta_n);++b)
	{  bool sub_test=false;
	   int cont=0;
	   for(int c=b;c<b+conecta_n;++c)
	   {
	      if(Matriz.mt[a][c]!=color_actual)
	         sub_test= true;
	      else
	        {
	         fichas[cont].fila=a;
		 fichas[cont].columna=c;
		 cont++;
		}
	   }
	   if(sub_test==false)
	      return true;
	} 
	
   //Comprobacion por columnas:
     for(int a=0;a<Matriz.columnas;++a) 	//Recorre todas las columnas.
  	for(int b=0;b<=(Matriz.filas-conecta_n);++b)
	{  bool sub_test=false;
	   int cont=0;
	   for(int c=b;c<b+conecta_n;++c)
	   {
	      if(Matriz.mt[c][a]!=color_actual)
	         sub_test= true;
	      else
	        {
	         fichas[cont].fila=c;
		 fichas[cont].columna=a;
		 cont++;
		}
	   }
	   if(!sub_test)
	      return true;
	}
 
       //Comprobamos por diagonales de izq-der:
       for(int a=Matriz.filas-1;a>=conecta_n-1;--a)
          for(int b=0;b<=Matriz.columnas-conecta_n;++b)
	     { bool sub_test=false;
	       int cont=0;
	       for(int c=0;c<conecta_n;++c)
	          if(Matriz.mt[a-c][b+c]!=color_actual)
		     sub_test=true;
		  else
	        {
	         fichas[cont].fila=a-c;
		 fichas[cont].columna=b+c;
		 cont++;
		}
	       if(!sub_test)
	          return true;
	     }
       //Comprobamos por diagonales de der-izq:
        for(int a=Matriz.filas-1;a>=conecta_n-1;--a)
          for(int b=Matriz.columnas-1;b>=conecta_n-1;--b)
	     { bool sub_test=false;
	       int cont=0;
	       for(int c=0;c<conecta_n;++c)
	          if(Matriz.mt[a-c][b-c]!=color_actual)
		     sub_test=true;
		  else
	          {
	           fichas[cont].fila=a-c;
		   fichas[cont].columna=b-c;
		   cont++;
		  }
	       if(!sub_test)
	          return true;
	     }
	return false;
}

int tablero::movimiento(int columna,int color)
{
  color_actual=color;
  //Comprobar si la columna esta llena:
  if(alto_columna(columna)==0)
    return 3;
  
  insertar(columna,alto_columna(columna)-1);
  
  //Comprobar si hay ganador:
  if(test())
    return 1;
  
  //comprobar si se lleno todo el tablero:
  for(int i=0;i<Matriz.columnas;++i)
       if(alto_columna(i)!=0)
         return 0;
  
  //Partida terminada sin ganador:
  return 2;
}

void tablero::insertar(int col,int fila)
{
    Matriz.mt[fila][col]=color_actual; 
}
int tablero::alto_columna(int columna)
{
	for(int i=0;i<Matriz.filas;++i)
 	    if(Matriz.mt[i][columna]!=2)
	       return i;
	return Matriz.filas;
}

int tablero::alto_columna_graf(int columna)
{
	for(int i=(Matriz.filas-1);i>=0;--i)
 	    if(Matriz.mt[i][columna]==2)
	       return (13-Matriz.filas)+i;
	       
	return 12-Matriz.filas;
}

void tablero::deshacer_jugada(int fil,int col)
{
  Matriz.mt[fil][col]=2; 
}
