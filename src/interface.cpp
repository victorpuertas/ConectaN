/**
\file interface.cpp
\author Victor M. Puertas Garcia.
*@version 0.00.05
\brief Contiene la implementacion de la clase interface.
*/
#include <string>
#include <iostream>
#include "configuracion.h"
#include "tablero.h"
#include "jugador.h"
#include "interface.h"
#include "SDL/SDL.h"
#include "SDL/SDL_gfxPrimitives.h"
#include "SDL/SDL_audio.h"
using namespace std;

/**
* @struct sample Contiene la informacion del buffer de audio.
*/
struct sample {
    //!Puntero al buffer de sonido.
    Uint8 *data;
    //!Posicion actual de reproduccion.
    Uint32 dpos;
    //!Espacio del buffer de sonido.
    Uint32 dlen;
} sounds;

 //Estructuras de sonido:
  SDL_AudioSpec wave;
  //!Puntero al buffer de audio.
  Uint8 *data;
  //!Espacio del buffer de audio.
  Uint32 dlen;
  //!Estructura para la conversion de audio.
  SDL_AudioCVT cvt;
  SDL_AudioSpec fmt;

interface::interface(conecta_conf config)
{
  //Resolucion 1024x768: un maximo de 12 bolas en altura y 10 tubos o columnas.
  resolucion_h=768; 
  resolucion_w=1024;
  conf_interna=config;
  
  //Iniciamos el vector de altura de bolas:
  int inicio=645;
  for(int i=11;i>=0;--i)
    {
      altura_bola[i]=inicio-50;
      inicio-=50;
    }
}

int interface::iniciar()
{
  //Iniciamos los modulos de la SDL:
  if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)<0)
     return 1;
     
  //Inicio del modo de video:
  buffer_blanco=SDL_SetVideoMode(resolucion_w,resolucion_h,32,SDL_SWSURFACE|SDL_ANYFORMAT|SDL_FULLSCREEN);
  
  if(buffer_blanco==0)
  {  
     SDL_Quit();
     return 2;
  }
  atexit(SDL_Quit); //Asegura que al terminar se cierra la SDL. 
  
  //Iniciamos las estructuras de audio:
  fmt.freq = 44100;
  fmt.format = AUDIO_S16;
  fmt.channels = 2;		// Mono: 1, Esterio: 2.
  fmt.samples = 4096; 
  fmt.callback = mixaudio;
  fmt.userdata = NULL;
  return 0;
}

int interface::presentacion()
{
  SDL_ShowCursor(SDL_DISABLE); //Desaparece el cursor.
 
  recursos=LeerImagenBMP(conf_interna.recursos+"/recursos.bmp");
  if(recursos==0)
    return 1;
   
  
  //Mostramos la firma: VPG.
  SDL_Rect origen,destino;
  origen.x=90;
  origen.y=195;
  origen.w=180;
  origen.h=80;
  
  destino.x=(resolucion_w/2)-(180/2);
  destino.y=(resolucion_h/2)-(80/2);
  destino.w=180;
  destino.h=80;

  efecto_apar_desa(recursos,&origen,buffer_blanco,&destino);
  SDL_ShowCursor(SDL_ENABLE);
  return 0;
}

void interface::menu()
{
  LimpiarVentana(buffer_blanco);
  SDL_Surface *fondo=LeerImagenBMP(conf_interna.recursos+"/conecta1.res");
  SDL_Surface *aux=crear_surface(buffer_blanco->w,buffer_blanco->h);
  
  SDL_Rect logo,opcion1,opcion2,opcion1_s,opcion2_s,destino,destino_aux;
  SDL_Event evento;
  int tecla;
  bool opcion=false; //Opcion seleccionada. False : Opcion1. True: Opcion 2.
  PlaySound(0);
  cargar_wav(conf_interna.recursos+"/menu.res");
  PlaySound(1); 
  
  //Logo:
  logo.x=764;
  logo.y=0;
  logo.w=300;
  logo.h=300;
  
  //opcion1: Nuevo juego
  opcion1.x=812;
  opcion1.y=330;
  opcion1.w=230;
  opcion1.h=53;
  
  //opcion2: Salir
  opcion2.x=812;
  opcion2.y=386;
  opcion2.w=88;
  opcion2.h=46;
  
  //opcion1 seleccionada: Nuevo juego
  opcion1_s.x=790;
  opcion1_s.y=446;
  opcion1_s.w=273;
  opcion1_s.h=53;
  
  //opcion2 seleccionada: Salir
  opcion2_s.x=790;
  opcion2_s.y=504;
  opcion2_s.w=133;
  opcion2_s.h=46;
 
     while(1)
     {
  	for(int i=0;i<1024;++i)
  	{
   	 destino.x=0-i;
   	 destino.y=0;
   	 destino.w=buffer_blanco->w;
   	 destino.h=buffer_blanco->h;
   	 volcar_lienzo(fondo,NULL,aux,&destino);
   	 destino.x=(0-i)+1024;
  	 volcar_lienzo(fondo,NULL,aux,&destino);
  	 destino.x=0;
  	 //Dibujar logo:
  	 destino_aux.x=(resolucion_w/2)-(logo.w/2);
  	 destino_aux.y=90;
  	 destino_aux.w=logo.w;
  	 destino_aux.h=logo.h;
  	 volcar_lienzo(recursos,&logo,aux,&destino_aux);
  	
	 //Obtenemos teclas
	 if (SDL_PollEvent(&evento)) 
         switch (evento.type) 
         {
           case SDL_KEYDOWN:    // Pulsamos una tecla
               tecla = (int)(evento.key.keysym.scancode);
	       
	       switch(tecla)
	       {
	         case 104:
		         opcion=true; 
		      break;
		 case 98:
		         opcion=false;
		      break;
		 case 108:
		 case 36: 
		         if(opcion)
			 {
			    cout<<"Conecta N 2005 ver:0.00.05\n(c) VPG - Víctor Puertas García, 2005\n";
			    cout<<"Desarrollado para la practica de MP2 de la ";
			    cout<<"Universidad de Granada.\n";
			    exit(0);
			 }
			 else
			 { //Liberar recursos utilizados:
			   SDL_FreeSurface(fondo);
			   SDL_FreeSurface(aux);
			   liberar_wav();
                           PlaySound(0);
			   return;
			 }
	       }
          break;
         }
	 
	 if(!opcion)
		          {
			    destino_aux.x=(resolucion_w/2)-(opcion1_s.w/2);
  	 		    destino_aux.y=500;
  	                    destino_aux.w=opcion1_s.w;
  	                    destino_aux.h=opcion1_s.h;
  	                    volcar_lienzo(recursos,&opcion1_s,aux,&destino_aux);
			    
			    destino_aux.x=(resolucion_w/2)-(opcion2.w/2);
  	 		    destino_aux.y=570;
  	                    destino_aux.w=opcion2.w;
  	                    destino_aux.h=opcion2.h;
  	                    volcar_lienzo(recursos,&opcion2,aux,&destino_aux);
			  }
	else
			  {
			    destino_aux.x=(resolucion_w/2)-(opcion1.w/2);
  	 		    destino_aux.y=500;
  	                    destino_aux.w=opcion1.w;
  	                    destino_aux.h=opcion1.h;
  	                    volcar_lienzo(recursos,&opcion1,aux,&destino_aux);  
		
			    destino_aux.x=(resolucion_w/2)-(opcion2_s.w/2);
  	 		    destino_aux.y=570;
  	                    destino_aux.w=opcion2_s.w;
  	                    destino_aux.h=opcion2_s.h;
  	                    volcar_lienzo(recursos,&opcion2_s,aux,&destino_aux);
			        
			  }
	 //Volcamos la imagen al lienzo principal:
	 DibujarImagen(aux,NULL,buffer_blanco,&destino);
	
   	}//fin del for.
     }//Fin del while.
    
}
void interface::dibujar_jugador(int jugador)
{
  SDL_Rect jugador1,jugador2,destino;
  
  //Titulo jugador1:
  jugador1.x=36;
  jugador1.y=565;
  jugador1.w=106;
  jugador1.h=34;
  
  //Titulo jugador2:
  jugador2.x=163;
  jugador2.y=563;
  jugador2.w=106;
  jugador2.h=34;
  
  destino.x=(resolucion_w/2)-(jugador1.w/2);
  destino.y=20;
  destino.w=106;
  destino.h=34;
    
  if(jugador==1)
   DibujarImagen(recursos,&jugador1,buffer_blanco,&destino); 
  else
   DibujarImagen(recursos,&jugador2,buffer_blanco,&destino); 
    
}

void interface::dibujar_ganadoras(coordenadas * bolas)
{
   
  for(int a=0;a<conf_interna.linea;++a)
  {
    //Localizamos las coordenadas de la columna:
    
    int ancho_tubo=80;
    int desplazamiento_ini=((resolucion_w-86)-((ancho_tubo+10)*numero_tubos))/2;
    int i=-1,desplazamiento=0;
    int columna;

    do{
         ++i;
         if(i==bolas[a].columna)
             columna=desplazamiento_ini+50+desplazamiento;
             
         desplazamiento+=ancho_tubo+10;
      }while(i< numero_tubos && i!=bolas[a].columna);
    
      SDL_Rect origen,destino_bola;
  
      origen.x=648;
      origen.y=418;
      origen.w=45;
      origen.h=44;
      
      destino_bola.x=columna+23; 
      destino_bola.y=(altura_bola[(12-conf_interna.filas)+bolas[a].fila])+90;
      destino_bola.w=45;
      destino_bola.h=44;
      DibujarImagen(recursos,&origen,buffer_blanco,&destino_bola);
      SDL_Delay(100);
      
  }//Fin del for.
  
}

int interface::efecto_apar_desa(SDL_Surface *src, SDL_Rect *c_src, SDL_Surface *dst, SDL_Rect *c_dst)
{
  //Establecemos el color transparente en el origen:
  if(SDL_SetColorKey(src,SDL_SRCCOLORKEY,SDL_MapRGB(src->format, 0, 0, 0))<0)
     return 1;
  

  for(int i=0;i<100;++i)
  {
    if(SDL_SetAlpha(src,SDL_SRCALPHA,i)<0)
       return 2;
    if(SDL_BlitSurface(src,c_src,dst,c_dst)<0)
       return 3;
    SDL_UpdateRect(dst,c_dst->x, c_dst->y, c_dst->w, c_dst->h);
    SDL_Delay(100);
  }
  SDL_SetAlpha(src,SDL_SRCALPHA,255);
  return 0;
}

SDL_Surface *interface::LeerImagenBMP(string fich)
{
  SDL_Surface *img;
  if (!(img=SDL_LoadBMP(fich.c_str())))
    return 0;
  return img;
}

void interface::DibujarImagen(SDL_Surface *src, SDL_Rect *c_src, SDL_Surface *dst, SDL_Rect *c_dst)
{
  
  SDL_SetColorKey(src,SDL_SRCCOLORKEY,SDL_MapRGB(src->format, 0, 0, 0));
  SDL_BlitSurface(src, c_src, dst, c_dst);
  SDL_UpdateRect(dst, c_dst->x,c_dst->y, c_dst->w, c_dst->h);
  SDL_SetColorKey(src,0,0);
}

SDL_Surface *interface::crear_surface(int width,int height)
{ 
  return(SDL_CreateRGBSurface(SDL_SWSURFACE|SDL_ANYFORMAT|SDL_FULLSCREEN,width,height,32,rmask, gmask, bmask, amask));
}


void interface::dibujar_tablero(int filas, int columnas)
{
	dibujar_fondo();
        dibujar_barra();
	dibujar_columnas();
	dibujar_barra_estado();
  	dibujar_titulos();
	tubos(columnas);  		     //Para esta resolucion el maximo es 10.
	
	cargar_wav(conf_interna.recursos+"/ambiente.res");
        PlaySound(1);
}

void interface::LimpiarVentana(SDL_Surface *ventana)
{
  int i;
  /* Set the screen to black */
  if ( SDL_LockSurface(ventana) == 0 ) {
    Uint32 black;
    Uint8 *pixels;
    black = SDL_MapRGB(ventana->format, 0, 0, 0);
    pixels = (Uint8 *)ventana->pixels;
    for ( i=0; i<ventana->h; ++i ) {
      memset(pixels, black,
              ventana->w*ventana->format->BytesPerPixel);
      pixels += ventana->pitch;
    }
    SDL_UnlockSurface(ventana);
  }
}

void interface::dibujar_columnas()
{ 
  SDL_Rect origen,destino;
  //columnas izq:
  origen.x=0;
  origen.y=70;
  origen.w=43;
  origen.h=205;
   for(int a=0;a<resolucion_w;a+=205)  //2 columnas a 33 pixel cada una.
      
       { 
         destino.x=0;
  	 destino.y=96+a;
  	 destino.w=43;
  	 destino.h=205;
	 DibujarImagen(recursos,&origen,buffer_blanco,&destino);
	}
   //columnas der:
  origen.x=44;
  origen.y=70;
  origen.w=43;
  origen.h=205;
   for(int a=0;a<resolucion_w;a+=205)  //2 columnas a 33 pixel cada una.
      
       { 
         destino.x=resolucion_w-40;
  	 destino.y=96+a;
  	 destino.w=43;
  	 destino.h=205;
	 DibujarImagen(recursos,&origen,buffer_blanco,&destino);
	}

}
void interface::dibujar_fondo()
{
  
  SDL_Rect origen,destino;
  origen.x=1;
  origen.y=0;
  origen.w=61;
  origen.h=61;
  //Dibujar mosaico fondo:
   for(int a=0;a<resolucion_h;a+=59)
      for(int b=0;b<resolucion_w;b+=59)
       { 
         destino.x=b;
  	 destino.y=a;
  	 destino.w=61;
  	 destino.h=61;
	 DibujarImagen(recursos,&origen,buffer_blanco,&destino);
	}
}
void interface::dibujar_barra()
{
  SDL_Rect origen,destino;
  //Bloques superiores:
  origen.x=62;
  origen.y=2;
  origen.w=33;
  origen.h=33;
   for(int a=0;a<2*33;a+=32)  //2 columnas a 33 pixel cada una.
      for(int b=0;b<resolucion_w;b+=32)
       { 
         destino.x=b;
  	 destino.y=a;
  	 destino.w=33;
  	 destino.h=33;
	 DibujarImagen(recursos,&origen,buffer_blanco,&destino);
	}
}

void interface::game_over()
{
  SDL_Rect origen,destino;
  
  origen.x=100;
  origen.y=45;
  origen.w=220;
  origen.h=35;
  
  destino.x=(resolucion_w/2)-(220/2);
  destino.y=(resolucion_h/2)-(35/2);
  destino.w=220;
  destino.h=35;
    
  DibujarImagen(recursos,&origen,buffer_blanco,&destino);
  
  /*PlaySound(conf_interna.recursos+"/gameover.wav",1);
  SDL_Delay(6000);
  PlaySound("",0);*/
}

void interface::tres_dos_uno()
{
  SDL_Rect origen,destino,fondo;
  SDL_Surface *aux;
  
  //Creamos un lienzo del tamaño del GO porque es el mas grande y copiamos el fondo
  //para despues sustituirlo.
  aux=crear_surface(178,180);
  
  fondo.x=(resolucion_w/2)-(178/2);
  fondo.y=(resolucion_h/2)-(180/2);
  fondo.w=178;
  fondo.h=180;
  SDL_BlitSurface(buffer_blanco,&fondo,aux,NULL);
  
  //Tres:
  origen.x=216;
  origen.y=274;
  origen.w=124;
  origen.h=166;
  
  destino.x=(resolucion_w/2)-(origen.w/2);
  destino.y=(resolucion_h/2)-(origen.h/2);
  destino.w=origen.w;
  destino.h=origen.h;
  
  DibujarImagen(recursos,&origen,buffer_blanco,&destino);
  SDL_Delay(1000);
  DibujarImagen(aux,NULL,buffer_blanco,&fondo);
  
  //Dos:
  origen.x=80;
  origen.y=280;
  origen.w=122;
  origen.h=155;
  
  destino.x=(resolucion_w/2)-(origen.w/2);
  destino.y=(resolucion_h/2)-(origen.h/2);
  destino.w=origen.w;
  destino.h=origen.h;
  
  DibujarImagen(recursos,&origen,buffer_blanco,&destino);
  SDL_Delay(1000);
  DibujarImagen(aux,NULL,buffer_blanco,&fondo);
  
  //Uno:
  origen.x=0;
  origen.y=285;
  origen.w=66;
  origen.h=155;
  
  destino.x=(resolucion_w/2)-(origen.w/2);
  destino.y=(resolucion_h/2)-(origen.h/2);
  destino.w=origen.w;
  destino.h=origen.h;
  
  DibujarImagen(recursos,&origen,buffer_blanco,&destino);
  SDL_Delay(1000);
  DibujarImagen(aux,NULL,buffer_blanco,&fondo);
  
  //Go:
  origen.x=394;
  origen.y=262;
  origen.w=178;
  origen.h=180;
  
  destino.x=(resolucion_w/2)-(origen.w/2);
  destino.y=(resolucion_h/2)-(origen.h/2);
  destino.w=origen.w;
  destino.h=origen.h;
  
  DibujarImagen(recursos,&origen,buffer_blanco,&destino);
  SDL_Delay(1000);
  DibujarImagen(aux,NULL,buffer_blanco,&fondo);
  SDL_FreeSurface(aux);
}

void interface:: ganador(int jugador)
{
 SDL_Rect origen,destino;
  
 if(jugador==1)
 { 
   //Jugador1: 
   origen.x=25;
   origen.y=467;
   origen.w=376;
   origen.h=77;
  
   destino.x=(resolucion_w/2)-(origen.w/2);
   destino.y=((resolucion_h/2)-(origen.h/2))-77;
   destino.w=origen.w;
   destino.h=origen.h;
  
   DibujarImagen(recursos,&origen,buffer_blanco,&destino);
   SDL_Delay(500);
  
  
   origen.x=345;
   origen.y=82;
   origen.w=336;
   origen.h=79;
  
   destino.x=(resolucion_w/2)-(origen.w/2);
   destino.y=((resolucion_h/2)-(origen.h/2))+79;
   destino.w=origen.w;
   destino.h=origen.h;
  
   DibujarImagen(recursos,&origen,buffer_blanco,&destino);
   SDL_Delay(500);
  }
  else  //Jugador 2
  {
   origen.x=25;
   origen.y=467;
   origen.w=376;
   origen.h=77;
  
   destino.x=(resolucion_w/2)-(origen.w/2);
   destino.y=((resolucion_h/2)-(origen.h/2))-77;
   destino.w=origen.w;
   destino.h=origen.h;
  
   DibujarImagen(recursos,&origen,buffer_blanco,&destino);
   SDL_Delay(500);
  
  
   origen.x=345;
   origen.y=169;
   origen.w=336;
   origen.h=79;
  
   destino.x=(resolucion_w/2)-(origen.w/2);
   destino.y=((resolucion_h/2)-(origen.h/2))+79;
   destino.w=origen.w;
   destino.h=origen.h;
  
   DibujarImagen(recursos,&origen,buffer_blanco,&destino);
   SDL_Delay(500);
  
  }
  ObtenerTecla();
}
void interface::RectanguloR(int x1, int y1, int x2, int y2,
              unsigned char r, unsigned char g, unsigned char b)
{
  boxRGBA(buffer_blanco, x1, y1, x2, y2, r, g, b, 255);
  SDL_UpdateRect(buffer_blanco, min(x1,x2), min(y1,y2), abs(x1-x2)+1, abs(y1-y2)+1);
}

int interface::ObtenerTecla()
{
  SDL_Event evento;
  int tecla;
  bool fin=false;
  while (!fin) {
    if (SDL_PollEvent(&evento)) {
      switch (evento.type) {
        case SDL_KEYDOWN:    // Pulsamos una tecla
          tecla = (int)(evento.key.keysym.scancode);
          fin = true;
        break;
      }
    }
  }
  return tecla;
}

void interface::dibujar_titulos()
{
  
  SDL_Rect origen,destino;
  
  //Titulo jugador1:
  origen.x=36;
  origen.y=565;
  origen.w=106;
  origen.h=34;
  
  destino.x=30;
  destino.y=10;
  destino.w=106;
  destino.h=34;
    
  DibujarImagen(recursos,&origen,buffer_blanco,&destino);
  
  //Titulo jugador2:
  origen.x=161;
  origen.y=563;
  origen.w=106;
  origen.h=34;
  
  destino.x=resolucion_w-106-30;
  destino.y=10;
  destino.w=106;
  destino.h=34;
    
  DibujarImagen(recursos,&origen,buffer_blanco,&destino);
  //Dibujar las bolas de cada jugador:
  //Bola azul:
  origen.x=620;
  origen.y=362;
  origen.w=45;
  origen.h=44;
  
  destino.x=156;
  destino.y=20;
  destino.w=45;
  destino.h=44;
  DibujarImagen(recursos,&origen,buffer_blanco,&destino);
  //Bola roja:
  origen.x=680;
  origen.y=362;
  origen.w=45;
  origen.h=44;
  
  destino.x=resolucion_w-106-30-50;
  destino.y=20;
  destino.w=45;
  destino.h=44;
  DibujarImagen(recursos,&origen,buffer_blanco,&destino);
}

void interface::escribir_numero(string numero,int x,int y)
{
  
  int desplazamiento=0;
  SDL_Rect origen,destino;
  for(int i=0;i<numero.length();++i)
     {
      
	 if(numero[i]=='0')
	 {      
  
 		origen.x=106;
  		origen.y=3;
  		origen.w=29;
  		origen.h=34;
  
  		destino.x=desplazamiento+x;
  		destino.y=y;
  		destino.w=29;
  		destino.h=34;
    
  		DibujarImagen(recursos,&origen,buffer_blanco,&destino);
         }	
	  
	 if(numero[i]=='1')
	 {      
  
 		origen.x=143;
  		origen.y=3;
  		origen.w=29;
  		origen.h=34;
  
  		destino.x=desplazamiento+x;
  		destino.y=y;
  		destino.w=29;
  		destino.h=34;
    
  		DibujarImagen(recursos,&origen,buffer_blanco,&destino);
         }	   
	 
	 if(numero[i]=='2')
	 {      
  
 		origen.x=177;
  		origen.y=3;
  		origen.w=29;
  		origen.h=34;
  
  		destino.x=desplazamiento+x;
  		destino.y=y;
  		destino.w=29;
  		destino.h=34;
    
  		DibujarImagen(recursos,&origen,buffer_blanco,&destino);
         }	     
	 
	 if(numero[i]=='3')
	 {      
  
 		origen.x=214;
  		origen.y=3;
  		origen.w=29;
  		origen.h=34;
  
  		destino.x=desplazamiento+x;
  		destino.y=y;
  		destino.w=29;
  		destino.h=34;
    
  		DibujarImagen(recursos,&origen,buffer_blanco,&destino);
         }	
	 
	 if(numero[i]=='4')
	 {      
  
 		origen.x=250;
  		origen.y=3;
  		origen.w=29;
  		origen.h=34;
  
  		destino.x=desplazamiento+x;
  		destino.y=y;
  		destino.w=29;
  		destino.h=34;
    
  		DibujarImagen(recursos,&origen,buffer_blanco,&destino);
         }	
	 
	 if(numero[i]=='5')
	 {      
  
 		origen.x=285;
  		origen.y=3;
  		origen.w=29;
  		origen.h=34;
  
  		destino.x=desplazamiento+x;
  		destino.y=y;
  		destino.w=29;
  		destino.h=34;
    
  		DibujarImagen(recursos,&origen,buffer_blanco,&destino);
         }	
	 
	 if(numero[i]=='6')
	 {      
  
 		origen.x=321;
  		origen.y=3;
  		origen.w=29;
  		origen.h=34;
  
  		destino.x=desplazamiento+x;
  		destino.y=y;
  		destino.w=29;
  		destino.h=34;
    
  		DibujarImagen(recursos,&origen,buffer_blanco,&destino);
         }	    
	 
	 if(numero[i]=='7')
	 {      
  
 		origen.x=357;
  		origen.y=3;
  		origen.w=29;
  		origen.h=34;
  
  		destino.x=desplazamiento+x;
  		destino.y=y;
  		destino.w=29;
  		destino.h=34;
    
  		DibujarImagen(recursos,&origen,buffer_blanco,&destino);
         }	                
       
       
       if(numero[i]=='8')
	 {      
  
 		origen.x=393;
  		origen.y=3;
  		origen.w=29;
  		origen.h=34;
  
  		destino.x=desplazamiento+x;
  		destino.y=y;
  		destino.w=29;
  		destino.h=34;
    
  		DibujarImagen(recursos,&origen,buffer_blanco,&destino);
         }
	 
	 if(numero[i]=='9')
	 {      
  
 		origen.x=429;
  		origen.y=3;
  		origen.w=29;
  		origen.h=34;
  
  		destino.x=desplazamiento+x;
  		destino.y=y;
  		destino.w=29;
  		destino.h=34;
    
  		DibujarImagen(recursos,&origen,buffer_blanco,&destino);
         }
	 
	 desplazamiento+=29;	    	    //Para mover el numero.
     }
  
}

string interface::inttochar(long int numero)
{
    string v_aux,salida;
    int contador=0;
    do
    {  
       v_aux=v_aux+(char)(48+(numero%10));
       numero=numero/10;
       contador++; 
    }while(numero!=0);
    
    //Cambiar el orden:
    int i;
    for(i=0;i<contador;++i)
    {
        salida=salida+v_aux[(contador-1)-i];
    }
    
    return salida;    
}    

void interface::escribir_puntos(int puntos1,int x,int y,int puntos2,int x2,int y2)
{
  string final,final2;
  
  if(puntos1<10)
     final="000";
  else   
    if(puntos1<100)
       final="00";
    else
      if(puntos1<1000)
        final="0";
	
  if(puntos2<10)
     final2="000";
  else   
    if(puntos2<100)
       final2="00";
    else
      if(puntos2<1000)
        final2="0";
        
  final=final+inttochar(puntos1);
  final2=final2+inttochar(puntos2);
  dibujar_barra();
  dibujar_titulos();   
  escribir_numero(final,x,y);
  escribir_numero(final2,x2,y2);
}

void interface::tubos(int numero)
{
  SDL_Rect origen,destino;
  int desplazamiento=0,desplazamiento_ini=0;
  numero_tubos=numero;
  coordenadas_tubos=new int[numero];
  origen.x=594;
  origen.y=267;
  origen.w=80;
  origen.h=81;
  
  desplazamiento_ini=((resolucion_w-86)-((origen.w+10)*numero))/2;
  // 86 : Tamaño de las calumnas laterales.
  // 10 : Desplazamiento entre tubo y tubo.
  
  for(int i=0;i< numero;++i)
  {		
     destino.x=desplazamiento_ini+50+desplazamiento;
     destino.y=95;
     destino.w=80;
     destino.h=81;
     coordenadas_tubos[i]=destino.x;
     DibujarImagen(recursos,&origen,buffer_blanco,&destino);
     
     desplazamiento+=origen.w+10;
  }
}

void interface::dibujar_barra_estado()
{
  SDL_Rect origen,destino;
  origen.x=62;
  origen.y=2;
  origen.w=33;
  origen.h=33;
  
      for(int b=0;b<resolucion_w;b+=32)
       { 
         destino.x=b;
  	 destino.y=resolucion_h-33;
  	 destino.w=33;
  	 destino.h=33;
	 DibujarImagen(recursos,&origen,buffer_blanco,&destino);
	}
}

void interface::escribir_estado(string texto)
{
  dibujar_barra_estado();
  Texto(10,resolucion_h-16,texto.c_str(),255,255,255);
}

void interface::Texto(int x, int y, const char *c,
             unsigned char r, unsigned char g, unsigned char b)
{
  stringRGBA(buffer_blanco, x, y, c, r, g, b, 255);
  SDL_UpdateRect(buffer_blanco, 0, 0, 0, 0);
}

void interface::hechar_bola(int color,int tubo_s,int fila)
{
  //Estructuras de coordenadas:
  // fondo_lienzo: Coordenadas de la columna en el lienzo original.
  SDL_Rect bola,tubo,fondo_lienzo,destino_bola,destino_tubo;
  
 
  
  //Lienzos utilizados:
  SDL_Surface *columna_org,*columna_trabajo;
  
  //Establecemos coordenadas del archivo de recursos:
  tubo.x=594;
  tubo.y=267;
  tubo.w=80;
  tubo.h=81;
  
  if(color==0)
  {
    bola.x=620;
    bola.y=362;
    bola.w=45;
    bola.h=44;
  }
  else
  {
    bola.x=680;
    bola.y=362;
    bola.w=45;
    bola.h=44;
  }
  
  //Establecemos coordenada destino con referencia en columna_trabajo:
  destino_tubo.x=0;
  destino_tubo.y=0;
  destino_tubo.w=80;
  destino_tubo.h=81;
  
  destino_bola.x=25; 
  destino_bola.y=90;//Alto del tubo90
  destino_bola.w=45;
  destino_bola.h=44;
  
  //Localizamos las coordenadas de la columna en la que se hecha la bola:
  int desplazamiento_ini=((resolucion_w-86)-((tubo.w+10)*numero_tubos))/2;
  int i=-1,desplazamiento=0;

  do{
       ++i;
       if(i==tubo_s)
       {
        fondo_lienzo.x=desplazamiento_ini+50+desplazamiento;
        fondo_lienzo.y=95;
        fondo_lienzo.w=80; //103
        fondo_lienzo.h=resolucion_h-fondo_lienzo.y;
        
	//Creamos los lienzos de trabajo:
	columna_org=crear_surface(fondo_lienzo.w,fondo_lienzo.h);
	columna_trabajo=crear_surface(fondo_lienzo.w,fondo_lienzo.h);
       }
     desplazamiento+=tubo.w+10;;
    
    }while(i< numero_tubos && i!=tubo_s);
  
  //Copiamos el fondo del lienzo original antes de dibujar la bola:
  SDL_BlitSurface(buffer_blanco, &fondo_lienzo, columna_org, NULL); 
  
  do
  { 
    //Dibujar el fondo en el lienzo de trabajo:
   // LimpiarVentana(columna_trabajo);
     volcar_lienzo(columna_org,NULL,columna_trabajo,NULL);
     //SDL_BlitSurface(columna_org,NULL,columna_trabajo,NULL);
     
    //Dibujar bola:
    volcar_lienzo(recursos,&bola,columna_trabajo, &destino_bola);
    
    //Dibujar tubo:
    volcar_lienzo(recursos,&tubo,columna_trabajo,&destino_tubo);
    
    //Bolcamos el el lienzo de trabajo al principal:
    DibujarImagen(columna_trabajo,NULL,buffer_blanco,&fondo_lienzo);
    
    
   /* //Obtener el pixel siguiente:
    int x_pixel=(fondo_lienzo.x+25)+(destino_bola.w/2);
    int y_pixel=destino_bola.y+destino_bola.h+95+7;
   
    ObtenerPunto(buffer_blanco,x_pixel,y_pixel,r,g,b);
    */
    SDL_Delay(8);
    destino_bola.y+=5; //Desplazamiento de la bola.
  
 
  }while(destino_bola.y<altura_bola[fila]);
  
  SDL_FreeSurface(columna_org);
  SDL_FreeSurface(columna_trabajo);
  SDL_Delay(conf_interna.tiempo);
}
void interface::cargar_wav(string archivo)
{
  if ( SDL_LoadWAV(archivo.c_str(), &wave, &data, &dlen) == NULL )         
        return;
}

void interface::liberar_wav()
{
 SDL_FreeWAV(data);
}

void interface::PlaySound(int opciones)
{   
    if(opciones==0)
       SDL_CloseAudio();
    else
    {
           
      /* ¡Abre el dispositivo de sonido y comienza a
       reproducir sonidos! */
      if ( SDL_OpenAudio(&fmt, NULL) < 0 ) 
       return;
       
      SDL_PauseAudio(0);
     
      /* Carga el archivo de sonido y lo convierte a
       estéreo 16 bits a 22kHz */
      
    
    
      SDL_BuildAudioCVT(&cvt, wave.format, wave.channels, wave.freq,AUDIO_S16, 1, 22050);
    
      SDL_LockAudio();
      sounds.data = data;
      sounds.dlen = dlen;
      sounds.dpos = 0;
      SDL_UnlockAudio(); 
    }
}

void mixaudio(void *unused, Uint8 *stream, int len)
{
    Uint32 amount;

           amount = (sounds.dlen-sounds.dpos);
           if ( amount > len ) 
           {
              amount = len;
           }
	   SDL_MixAudio(stream, &sounds.data[sounds.dpos],amount, SDL_MIX_MAXVOLUME);
           sounds.dpos +=amount;
	   
	    if(sounds.dpos>= sounds.dlen)
	    { 
	      SDL_LockAudio();
      	      sounds.data = data;
              sounds.dlen = dlen;
              sounds.dpos = 0;
      	      SDL_UnlockAudio();
	     }
	  
      
}

void interface::volcar_lienzo(SDL_Surface *src, SDL_Rect *c_src, SDL_Surface *dst, SDL_Rect *c_dst)
{
  SDL_SetColorKey(src,SDL_SRCCOLORKEY,SDL_MapRGB(src->format, 0, 0, 0));
  SDL_BlitSurface(src, c_src, dst, c_dst);
}

void interface::ObtenerPunto(SDL_Surface *ventana,int x, int y, Uint8 &r,  Uint8 &g,  Uint8 &b)
{
  int bpp = ventana->format->BytesPerPixel;
  Uint8 *p = (Uint8*)ventana->pixels + y*ventana->pitch + x*bpp;
  Uint32 color=0;

  // Bloqueamos la ventana si es necesario
  if (SDL_MUSTLOCK(ventana)) 
    if (SDL_LockSurface(ventana)<0) 
       exit(0);
    
  

  // Obtenemos punto
  switch (bpp) {
    case 1:
      color = *p;
      break;
    case 2:
      color = *(Uint16*)p;
      break;
    case 3:
      if (SDL_BYTEORDER==SDL_BIG_ENDIAN)
        color = p[0]<<16 | p[1]<<8 | p[2];
      else
        color = p[0] | p[1]<<8 | p[2]<<16;
      break;
    case 4:
      color = *(Uint32*)p;
      break;
  }

  // Desbloqueamos la ventana si es necesario
  if (SDL_MUSTLOCK(ventana)) 
    SDL_UnlockSurface(ventana);
  

  // Decodificamos el color en sus 3 componentes R, G y B
  SDL_GetRGB(color,ventana->format,&r,&g,&b);
}

int interface::ObtenerClick(int &x, int &y)
{
  SDL_Event evento;
  int boton;
  bool fin=false;
  while (!fin) {
    if (SDL_PollEvent(&evento)) {
      switch (evento.type) {
        case SDL_MOUSEBUTTONDOWN:    // Click de raton
          boton = (int)(evento.button.button);
          x = evento.button.x;
          y = evento.button.y;
          fin = true;
        break;
      }
    }
  }
  return boton;
}

int interface::obtener_columna()
{
  int x,y; //Coordenadas del raton.
  SDL_Rect origen,origen_,destino,destino_;
  
  if(ObtenerClick(x,y)==1)
     for(int i=0;i<numero_tubos;++i)
        if(x>=coordenadas_tubos[i] && x<(coordenadas_tubos[i]+80))
	   {
	        //Coordenadas de tubo:
		origen.x=594;
  		origen.y=267;
  		origen.w=80;
  		origen.h=81;
		
		//Coordenadas de tubo con colores invertidos:
  		origen_.x=683;
  		origen_.y=267;
  		origen_.w=80;
  		origen_.h=81;
  
  		destino.x=coordenadas_tubos[i];
  		destino.y=95;
  		destino.w=80;
  		destino.h=81;
		
		destino_.x=coordenadas_tubos[i]+13;
  		destino_.y=95;
  		destino_.w=80;
  		destino_.h=81;
    
  		DibujarImagen(recursos,&origen_,buffer_blanco,&destino_);
		SDL_Delay(20);
		DibujarImagen(recursos,&origen,buffer_blanco,&destino);
		SDL_Delay(20);
		DibujarImagen(recursos,&origen_,buffer_blanco,&destino_);
		SDL_Delay(20);
		DibujarImagen(recursos,&origen,buffer_blanco,&destino);
		return i;
	   }
return 0;
}
