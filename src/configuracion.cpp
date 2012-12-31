/**
@file configuracion.cpp
@author Victor M. Puertas Garcia.
@version 0.0
@brief Contiene la implementacion de la clase configuracion.
*/
#include <fstream>
#include <string>
#include"configuracion.h"
using namespace std;

conecta_conf configuracion::actualizar(string nombre)
{
    conecta_conf config;
    string buffer,seccion;
    
    ifstream archivo(nombre.c_str());
    if(archivo.fail())
      { 
       config.turno=100;
       return config;
      }
    //Comprobar la marca de cabecera:
    getline(archivo,buffer);
    seccion=buffer.substr(0,12);
    if(seccion.find("CFG-CONECTAN")==string::npos)
       {
        config.turno=101;
	return config;
       }
    //Obtener los valores de configuracion:
    while(!archivo.eof())
    {  
      //Obtencion de una linea de configuracion:Crea un tablero con los valores por defecto: 4 x 4.
      getline(archivo,buffer);
      //interpretacion de los datos:
      
      if(nombre[0]!='#')
      {
   
  	seccion=buffer.substr(0,11);
	;
	
	  if(seccion.find("Recursos")!=string::npos)
	  {
	    if(buffer[8]=='=')
	    {
	       config.recursos=buffer.substr(9,buffer.length()-9);
	    }
	  }
	  else
	    if(seccion.find("Tema")!=string::npos)
	    {
	    	if(buffer[4]=='=')
	    	{
	      	 config.tema=buffer.substr(5,buffer.length()-5);
	    	}
	    }
	    else 
	      if(seccion.find("Tiempo")!=string::npos)
	      {
	      	if(buffer[6]=='=')
	    	{
	      	 config.tiempo=atoi(buffer.substr(7,buffer.length()-7).c_str());
	    	}
	      }
	      else 
	        if(seccion.find("Dimensiones")!=string::npos)
	  	{
		  if(buffer[11]=='=')
	    	  {
	      	   int pos_space;
		   string cadena_filas;
		   
		   pos_space=buffer.find(" ")-1;
		   config.columnas=atoi(buffer.substr(12,pos_space).c_str());
		   
		   cadena_filas=buffer.substr(pos_space+1,buffer.length()-(pos_space+1));
		   config.filas=atoi(cadena_filas.substr(0,cadena_filas.find(" ")-1).c_str());
	    	  if(config.columnas>10)
		     config.columnas=10;
		  if(config.filas>12)
		     config.filas=12;   
		  }
		}
		else
	          if(seccion.find("Linea")!=string::npos)	
		  {
		    if(buffer[5]=='=')
	    	    {
	      	     config.linea=atoi(buffer.substr(6,buffer.length()-6).c_str());
	    	    }
		  }
		  else  
		    if(seccion.find("Nfichas")!=string::npos)
		    {
		      if(buffer[7]=='=')
	    		{
	      	 	 config.Nfichas=atoi(buffer.substr(8,buffer.length()-8).c_str());
	    		 if(config.Nfichas>(config.linea-2))
			    config.Nfichas=config.linea-2;
			}	
		    }
		    else
	              if(seccion.find("Jugador1")!=string::npos)
		      {
		        if(buffer[8]=='=')
	    		{
	      	 	 config.jugador1=buffer.substr(9,buffer.length()-9);
	    		}
		      }
		      else
	                if(seccion.find("Nivel1")!=string::npos)
			{
			  if(buffer[6]=='=')
	    		  {
	      	 	   config.nivel1=atoi(buffer.substr(7,buffer.length()-7).c_str());
			   if(config.nivel1<0 || config.nivel1>3)
			      config.nivel1=0;
	    	          }
			}
			else
	                  if(seccion.find("Jugador2")!=string::npos)
			  {
			   if(buffer[8]=='=')
	    		   {
	      	            config.jugador2=buffer.substr(9,buffer.length()-9);
			    
	    	           }
			  }
			  else
		            if(seccion.find("Nivel2")!=string::npos)
			    {
			     if(buffer[6]=='=')
	    		     {
	      	              config.nivel2=atoi(buffer.substr(7,buffer.length()-7).c_str());
	    	              if(config.nivel2<0 || config.nivel2>3)
			      config.nivel2=0;
			     }
			    }
			    else
	  		      if(seccion.find("Turno")!=string::npos)
			      {
			       if(buffer[5]=='=')
	    			{
	      	 		 config.turno=atoi(buffer.substr(6,buffer.length()-6).c_str());
	    			}
			      }
	}
  }  
    return  config;
}
