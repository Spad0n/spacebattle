CFLAGS = -O3 `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_ttf -lSDL2_mixer -lm

INC = sdl2-light.h
SRC = main.c sdl2-light.c entities.c graphics.c sdl2-ttf-light.c sdl2-audio.c menu.c timer.c
OBJ = $(SRC:%.c=%.o)
TSRC = tests.c sdl2-light.c entities.c graphics.c sdl2-ttf-light.c sdl2-audio.c menu.c timer.c
TOBJ = $(TSRC:%.c=%.o)

PROG = spacebattle

%.o: %.c $(INC)
	gcc $(CFLAGS) -c $<

spacebattle: $(OBJ)
	gcc $(CFLAGS) $(OBJ) $(LDFLAGS) -o $@

# using the command `make tests`
tests: $(TOBJ)
	gcc $(CFLAGS) $(TOBJ) $(LDFLAGS) -o $(PROG)

doc: $(PROG)
	doxygen ./$(PROG)
	make -C latex

clean:
	rm -f *~ *.o $(PROG)
	rm -rf latex html
