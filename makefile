
CC = wla-6502
CFLAGS = -o
LD = wlalink
LDFLAGS = -v -s

SFILES = main.s
IFILES = 
OFILES = main.o

all: $(OFILES) makefile
	$(LD) $(LDFLAGS) linkfile game.rom

main.o: main.s
	$(CC) $(CFLAGS) main.o main.s


$(OFILES): $(HFILES)


clean:
	rm -f $(OFILES) core *~ game.rom game.sym
