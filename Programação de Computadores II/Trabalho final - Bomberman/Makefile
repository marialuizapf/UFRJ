CC      := gcc
CFLAGS  := -Wall -Iinclude
LDFLAGS := -lraylib -lm

# Fontes e objetos
SRC := $(wildcard src/*.c) main.c
OBJ     := $(SRC:.c=.o)

# Executável de saída
TARGET  := bin/bomberman

.PHONY: all clean fclean

all: $(TARGET)

# Regra para linkar o executável
$(TARGET): $(OBJ)
	@mkdir -p bin
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS) -o $(TARGET)

# Regra genérica para compilar .c em .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Remove objetos gerados
clean:
	rm -f $(OBJ)

# Limpeza completa (objetos + executável)
fclean: clean
	rm -f $(TARGET)

# Executar o jogo no terminal do MSYS2
# 1-  cd /c/Users/maria/OneDrive/Documents/GitHub/UFRJ/Programação\ de\ Computadores\ II/Trabalho\ final\ -\ Bomberman
# 2-  mingw32-make
# 3-  ./bin/bomberman.exe

