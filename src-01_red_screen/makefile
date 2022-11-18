
CC = wla-6502
CFLAGS = -o
LD = wlalink
LDFLAGS = -v -s

SFILES = main.s
IFILES =
OFILES = main.o

all: $(OFILES) makefile
	$(LD) $(LDFLAGS) linkfile game.a26

main.o: main.s
	$(CC) $(CFLAGS) main.o main.s


$(OFILES): $(HFILES)


clean:
	rm -f $(OFILES) core *~ game.a26 game.sym
