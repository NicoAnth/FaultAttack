CC=g++
CFLAGS= -W -g -o
DEPS = FaultAttack.h 
OBJ = Main.o FaultAttack.o
PROJECTNAME = FaultAttack

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) $@ $<

$(PROJECTNAME): $(OBJ)
	$(CC) $(CFLAGS) $@ $^ 

clean:
	rm $(PROJECTNAME) *.o