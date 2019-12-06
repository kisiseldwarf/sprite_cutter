SRC=src/
OPT=-lm -g
EXEC=sprite_cutter

install:
	gcc $(SRC)main.c $(OPT) -o $(EXEC)

clean:
	rm $(EXEC)
