/**
\file jugador.cpp
\author Victor M. Puertas Garcia.
\version 0.00.05
\brief Contiene la implementacion de la clase jugador.
*/
#include <string>
#include <cstdlib>
#include <ctime>
#include "configuracion.h"
#include "tablero.h"
#include "jugador.h"

using namespace std;

jugadores::jugadores(conecta_conf config,interface &graf)
{
  cof_interna=config;
  //Se establece la semilla aleatoria:
  srand(time(0));
  
  //Se obtienen configuraciones:
  
     player1.nombre=config.jugador1;
     player1.nivel=config.nivel1;
     player1.puntos = 0;
     
     player2.nombre=config.jugador2;
     player2.nivel=config.nivel2;
     player2.puntos = 0;
     
     fichas_hechadas=0;
     
     graficos=&graf;
     
     turno_interno=config.turno;
     modo_texto=false;
}

jugadores::jugadores(conecta_conf config)
{
  cof_interna=config;
  //Se establece la semilla aleatoria:
  srand(time(0));
  
  //Se obtienen configuraciones:
  
     player1.nombre=config.jugador1;
     player1.nivel=config.nivel1;
     player1.puntos = 0;
     
     player2.nombre=config.jugador2;
     player2.nivel=config.nivel2;
     player2.puntos = 0;
     
     fichas_hechadas=0;
     
     graficos=0;
     
     turno_interno=config.turno;
     modo_texto=true;
}

jugadores::jugador jugadores::info(int player)
{

  if(player==1)
    return player1;
  else
    return player2;
}

void jugadores::set_tablero(tablero *campo)
{
  zona_juego=campo;
}

int jugadores::columna_aleatoria()
{
 
  //Ver las columnas libre:
  int contador=0;
  for(int i=0;i<cof_interna.columnas;++i)
       if((*zona_juego).alto_columna(i)>0)
         contador++;
  
   int * libres=new int [contador],cont=0,aleatorio;
	 
    
       for(int i=0;i<cof_interna.columnas;++i)
         if((*zona_juego).alto_columna(i)>0)
          {  
	    libres[cont]=i;
            cont++;
	  }
   
   aleatorio=(int)(rand()/(RAND_MAX+1.0)*(contador));
   aleatorio=libres[aleatorio];
   delete [] libres;
  return(aleatorio);
}

int jugadores::jugada()
{

  //Color del player 1: negro 0, player 2: blanco 1.
  
  int salida;
  switch(turno_interno)
  {
//========================================PLAYER1========================================= 
     case 1:
          if(!modo_texto)
	    graficos->escribir_estado("Turno del JUGADOR 1: " +cof_interna.jugador1 +" NIVEL: " + (*graficos).inttochar(cof_interna.nivel1));
          int columna;						//Player 1.
          switch(player1.nivel)
          {
	    //******************************NIVEL 0*******************************
	    case 0:
	       do
	       {
	        columna=graficos->obtener_columna();
	        salida=(*zona_juego).movimiento(columna,0);
	       }while(salida==3);
	       
	       fichas_hechadas++;
	       
	       switch(salida)
	        {
	          case 0:          //Se realizo el movimiento.
		   (*graficos).hechar_bola(0,columna,(*zona_juego).alto_columna_graf(columna));
		   add_point(1,1);
		   //Escribimos los puntos en pantalla.
		   (*graficos).escribir_puntos(player1.puntos,30,45,player2.puntos,(*graficos).resolucion_w-106-30,45);   
                   
		   
		   if(fichas_hechadas==cof_interna.Nfichas)
		       {
		         fichas_hechadas=0;
			 cambiar_turno();
			 
		       } 
		   break;
		  case 1:         //Hay ganador de partida.
		   (*graficos).hechar_bola(0,columna,(*zona_juego).alto_columna_graf(columna));
		   add_point(20,1);
		   //Escribimos los puntos en pantalla.
		   (*graficos).escribir_puntos(player1.puntos,30,45,player2.puntos,(*graficos).resolucion_w-106-30,45);   
		   
		   
		   fichas_hechadas=0;
		   break;
	        }
	       return salida;
	    
	    //******************************NIVEL 1*******************************  
	    case 1:
	       do{
	          columna=columna_aleatoria();
		  salida=(*zona_juego).movimiento(columna,0);
		 }while(salida==3);
 
		 fichas_hechadas++;
	       
	       switch(salida)
	        {
	          case 0:          //Se realizo el movimiento.
		   if(!modo_texto)
		     (*graficos).hechar_bola(0,columna,(*zona_juego).alto_columna_graf(columna));
		     
		   add_point(1,1);
		   //Escribimos los puntos en pantalla.
		   if(!modo_texto)
		   (*graficos).escribir_puntos(player1.puntos,30,45,player2.puntos,(*graficos).resolucion_w-106-30,45);   
                   
		   
		   if(fichas_hechadas==cof_interna.Nfichas)
		       {
		         fichas_hechadas=0;
			 cambiar_turno();
			 
		       } 
		   break;
		  case 1:         //Hay ganador de partida.
		   if(!modo_texto)
		     (*graficos).hechar_bola(0,columna,(*zona_juego).alto_columna_graf(columna));
		   
		   add_point(20,1);
		   //Escribimos los puntos en pantalla.
		   if(!modo_texto)
		   (*graficos).escribir_puntos(player1.puntos,30,45,player2.puntos,(*graficos).resolucion_w-106-30,45);   
		   
		   
		   fichas_hechadas=0;
		   break;
	        }
		  return salida; 
            //******************************NIVEL 2******************************* 
	    case 2:
	       do{
	           columna=heuristica(1);
		   salida=(*zona_juego).movimiento(columna,0);
		 }while(salida==3);
		 
		 fichas_hechadas++;
		 switch(salida)
	         {
	          case 0:          //Se realizo el movimiento.
		   if(!modo_texto)
		     (*graficos).hechar_bola(0,columna,(*zona_juego).alto_columna_graf(columna));
		   
		   add_point(1,1);
		   //Escribimos los puntos en pantalla.
		   if(!modo_texto)
		     (*graficos).escribir_puntos(player1.puntos,30,45,player2.puntos,(*graficos).resolucion_w-106-30,45);   
                   
		   
		   if(fichas_hechadas==cof_interna.Nfichas)
		       {
		         fichas_hechadas=0;
			 cambiar_turno();
			 
		       } 
		   break;
		  case 1:         //Hay ganador de partida.
		   if(!modo_texto)
		     (*graficos).hechar_bola(0,columna,(*zona_juego).alto_columna_graf(columna));
		   
		   add_point(20,1);
		   //Escribimos los puntos en pantalla.
		   if(!modo_texto)
		   (*graficos).escribir_puntos(player1.puntos,30,45,player2.puntos,(*graficos).resolucion_w-106-30,45);   
		   
		   
		   fichas_hechadas=0;
		   break;
	         }
		  return salida; 
	       
	  }
	 break;
//====================================PLAYER 2===========================================
    case 2:	
          if(!modo_texto)
	    graficos->escribir_estado("Turno del JUGADOR 2: "+cof_interna.jugador2+" NIVEL: " + (*graficos).inttochar(cof_interna.nivel2));
    	  switch(player2.nivel)
          {
	    //******************************NIVEL 0*******************************
	    case 0:
	       do
	       {
	        columna=graficos->obtener_columna();
	        salida=(*zona_juego).movimiento(columna,1);
	       }while(salida==3);
	       
	       fichas_hechadas++;
	       
	       switch(salida)
	        {
	          case 0:          //Se realizo el movimiento.
		   (*graficos).hechar_bola(1,columna,(*zona_juego).alto_columna_graf(columna));
		   add_point(1,2);
		   //Escribimos los puntos en pantalla.
		   (*graficos).escribir_puntos(player1.puntos,30,45,player2.puntos,(*graficos).resolucion_w-106-30,45);   
		   
		   
		   if(fichas_hechadas==cof_interna.Nfichas)
		       {
		         fichas_hechadas=0;
			 cambiar_turno();
			 
		       } 
		   break;
		  case 1:         //Hay ganador de partida.
		   (*graficos).hechar_bola(1,columna,(*zona_juego).alto_columna_graf(columna));
		   add_point(20,2);
		   //Escribimos los puntos en pantalla.
		   (*graficos).escribir_puntos(player1.puntos,30,45,player2.puntos,(*graficos).resolucion_w-106-30,45);   
		   
		   
		   fichas_hechadas=0;
		   break;
	        }
	       return salida;
	       
	    //******************************NIVEL 1*******************************  
	    case 1:
	       do{
	          columna=columna_aleatoria();
		  salida=(*zona_juego).movimiento(columna,1);
		 }while(salida==3);
		 
		 fichas_hechadas++;
	       
	       switch(salida)
	        {
	          case 0:          //Se realizo el movimiento.
		   if(!modo_texto)
		     (*graficos).hechar_bola(1,columna,(*zona_juego).alto_columna_graf(columna));
		   add_point(1,2);
		   //Escribimos los puntos en pantalla.
		   if(!modo_texto)
		     (*graficos).escribir_puntos(player1.puntos,30,45,player2.puntos,(*graficos).resolucion_w-106-30,45);   
		   
		   
		   if(fichas_hechadas==cof_interna.Nfichas)
		       {
		         fichas_hechadas=0;
			 cambiar_turno();
			 
		       } 
		   break;
		  case 1:         //Hay ganador de partida.
		   if(!modo_texto)
		     (*graficos).hechar_bola(1,columna,(*zona_juego).alto_columna_graf(columna));
		   
		   add_point(20,2);
		   //Escribimos los puntos en pantalla.
		   if(!modo_texto)
		     (*graficos).escribir_puntos(player1.puntos,30,45,player2.puntos,(*graficos).resolucion_w-106-30,45);   
		   
		   
		   fichas_hechadas=0;
		   break;
	        }
		  return salida; 
	    //******************************NIVEL 2******************************* 
	    case 2:
	       do{
	           columna=heuristica(2);
		   salida=(*zona_juego).movimiento(columna,1);
		 }while(salida==3);

		 fichas_hechadas++;
		 
		 switch(salida)
	         {
	          case 0:          //Se realizo el movimiento.
		   if(!modo_texto)
		     (*graficos).hechar_bola(1,columna,(*zona_juego).alto_columna_graf(columna));
		   
		   add_point(1,2);
		   //Escribimos los puntos en pantalla.
		   if(!modo_texto)
		     (*graficos).escribir_puntos(player1.puntos,30,45,player2.puntos,(*graficos).resolucion_w-106-30,45);   
                   
		   
		   if(fichas_hechadas==cof_interna.Nfichas)
		       {
		         fichas_hechadas=0;
			 cambiar_turno();
			 
		       } 
		   break;
		  case 1:         //Hay ganador de partida.
		   if(!modo_texto)
		     (*graficos).hechar_bola(1,columna,(*zona_juego).alto_columna_graf(columna));
		   
		   add_point(20,2);
		   //Escribimos los puntos en pantalla.
		   if(!modo_texto)
		     (*graficos).escribir_puntos(player1.puntos,30,45,player2.puntos,(*graficos).resolucion_w-106-30,45);   
		   
		   
		   fichas_hechadas=0;
		   break;
	         }
		  return salida; 
		 
	  }
  }
  return 4;
}

void jugadores::cambiar_turno()
{
  if(turno_interno==1) 
      turno_interno=2;
  else
      turno_interno=1;
}

int jugadores::turno_actual()
{
  return(turno_interno);
}

int jugadores::heuristica(int jugador)
{
 
  //Ver las columnas libre:
  int contador=0;
  for(int i=0;i<cof_interna.columnas;++i)
       if((*zona_juego).alto_columna(i)>0)
         contador++;
  
   int * libres=new int [contador],cont=0;
    
   for(int i=0;i<cof_interna.columnas;++i)
         if((*zona_juego).alto_columna(i)>0)
          {  
	    libres[cont]=i;
            cont++;
	  }
 
 int color=0,color_contrario=1; //Color 0 es el jugador 1.
 int aux; //Contiene la columna seleccionada.
 if(jugador==2)
 {
    color=1;
    color_contrario=0;
 }
 
 
 //Comprobar las posibilidades de ganancia del jugador pasado como argumento:
    for(int i=0; i<cont;++i)
    {  
      if((*zona_juego).movimiento(libres[i],color)==1) 
      {
	(*zona_juego).deshacer_jugada((*zona_juego).alto_columna(libres[i]),libres[i]);
	aux=libres[i];
	delete [] libres;
	return aux;
      }
      (*zona_juego).deshacer_jugada((*zona_juego).alto_columna(libres[i]),libres[i]);
    }
 
       
 //Comprobar las posibilidades de ganancia del jugador contrario:
     for(int i=0; i<cont;++i)
    {  
      if((*zona_juego).movimiento(libres[i],color_contrario)==1) 
      {
	(*zona_juego).deshacer_jugada((*zona_juego).alto_columna(libres[i]),libres[i]);
	aux=libres[i];
	delete [] libres;
	return aux;
      }
      (*zona_juego).deshacer_jugada((*zona_juego).alto_columna(libres[i]),libres[i]);
    }
    delete [] libres;
 return columna_aleatoria();
}

void jugadores::add_point(int puntos,int jugador)
{
  if(jugador==1)
  {
    player1.puntos+=puntos;
    if(!modo_texto)
      if(player1.puntos>=9999)
         player1.puntos=0;
  }
  else
  {
    player2.puntos+=puntos;
    
    if(!modo_texto)
      if(player2.puntos>=9999)
         player2.puntos=0;
  }
}
