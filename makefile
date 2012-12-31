#-----------------------------------------------
#Fichero Make para la compilacion de Conecta N.
#-----------------------------------------------
CXX = g++

SRC = src
OBJ = obj
INCLUDE = include
LIB = lib
BIN = bin

# Opciones para compilar
CPPFLAGS = -c -g -I$(INCLUDE)

# Opciones para enlazar
LDFLAGS =  -L$(LIB) -lconf -ltablero -ljugadores -linterface -lSDL_gfx -lSDL -lpthread


all : interface configuracion tablero jugador conecta_n
#-------------------------------------------
#Creacion del la libreria de interface:
#-------------------------------------------
interface: $(OBJ)/interface.o
	ar rsv $(LIB)/libinterface.a $(OBJ)/interface.o

$(OBJ)/interface.o: $(SRC)/interface.cpp $(INCLUDE)/interface.h
	$(CXX) $(CPPFLAGS) $(SRC)/interface.cpp -o $(OBJ)/interface.o
	
#-------------------------------------------
#Creacion del la libreria de configuracion:
#-------------------------------------------
configuracion: $(OBJ)/configuracion.o
	ar rsv $(LIB)/libconf.a $(OBJ)/configuracion.o

$(OBJ)/configuracion.o: $(SRC)/configuracion.cpp $(INCLUDE)/configuracion.h
	$(CXX) $(CPPFLAGS) $(SRC)/configuracion.cpp -o $(OBJ)/configuracion.o
	
#-------------------------------------------
#Creacion del la libreria jugadores:
#-------------------------------------------
jugador: $(OBJ)/jugadores.o
	ar rsv $(LIB)/libjugadores.a $(OBJ)/jugadores.o

$(OBJ)/jugadores.o: $(SRC)/jugador.cpp $(INCLUDE)/jugador.h
	$(CXX) $(CPPFLAGS) $(SRC)/jugador.cpp -o $(OBJ)/jugadores.o

#-------------------------------------------
#Creacion del la libreria tablero:
#-------------------------------------------
tablero: $(OBJ)/tablero.o
	ar rsv $(LIB)/libtablero.a $(OBJ)/tablero.o

$(OBJ)/tablero.o: $(SRC)/tablero.cpp $(INCLUDE)/tablero.h
	$(CXX) $(CPPFLAGS) $(SRC)/tablero.cpp -o $(OBJ)/tablero.o
	
#-------------------------------------------
#Creacion del main:
#-------------------------------------------	
conecta_n: $(BIN)/conecta_n
$(BIN)/conecta_n: $(OBJ)/conecta_n.o $(LIB)/libconf.a $(LIB)/libtablero.a $(LIB)/libjugadores.a $(LIB)/libinterface.a
	$(CXX) $(OBJ)/conecta_n.o $(LDFLAGS) -o $(BIN)/conectaN

$(OBJ)/conecta_n.o: $(SRC)/main.cpp $(INCLUDE)/configuracion.h $(INCLUDE)/tablero.h $(INCLUDE)/jugador.h $(INCLUDE)/interface.h
	$(CXX) -c $(CPPFLAGS) $(SRC)/main.cpp -o $(OBJ)/conecta_n.o

#-------------------------------------------
#Creacion de la documentacion:
#-------------------------------------------
documentacion:	
	\doxygen
	
#-------------------------------------------
#Borrar los ficheros temporales:
#-------------------------------------------
clean:	
	\rm -rf $(SRC)/*.o $(OBJ)/*