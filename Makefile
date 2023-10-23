# Compilador y opciones
CC = gcc
CFLAGS = -Wall
LDFLAGS = -lpng -ljpeg

SRCS = main_code_proyecto.c gray_scale_jpeg.c gray_scale_png.c rotate_jpeg.c rotate_png.c

TARGET = proyecto_c

# Definición del target
$(TARGET): $(SRCS)
        # Comando para compilar y crear el ejecutable
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
        # Imprime confirmación en la consola
	@echo "Compilación completada. Ejecutable creado: proyecto_c"

# Regla phony para limpiar el ejecutable
.PHONY: clean
clean:
	rm -f proyecto_c
