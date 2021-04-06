CC=g++
CFLAGS= -W -g -o
DEPS = FaultAttack.h BitsManips.h
OBJ = Main.o FaultAttack.o BitsManips.o
PROJECTNAME = FaultAttack

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $@ $<

$(PROJECTNAME): $(OBJ)
	$(CC) $(CFLAGS) $@ $^ 

clean:
	rm $(PROJECTNAME) *.o