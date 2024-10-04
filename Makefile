# Variables
CC = gcc
CFLAGS = -Wall -g
SRCDIR = src
OBJDIR = build
TARGET = my_program

# Busca todos los archivos .c en el directorio src
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Target para compilar todo
all: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Regla para compilar archivos .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Crear el directorio de objetos si no existe
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Limpiar archivos generados
clean:
	rm -rf $(OBJDIR) $(TARGET)
