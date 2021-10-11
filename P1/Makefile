# Compilador
CC = g++

# FLAGS
# -g incluye información de debug
# -Wall añade los warnings
# -std=c++17 indica que seguimos el estándar de C++17
CFLAGS = -std=c++17 -g -Wall

# TARGET: el fichero ejecutable que queremos construir
TARGET = IA_P1

# OBJFILE: ficheros fuente con extensión .o
OBJFILES = main.o functions.o taxi.o world.o

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES)

clean:
	$(RM) *.o $(TARGET)






