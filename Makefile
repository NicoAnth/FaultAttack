CC=g++
CFLAGS= -g -Wall
DEPS = FaultAttack.h BitsManips.h
OBJ = Main.o FaultAttack.o BitsManips.o
PROJECTNAME = FaultAttack

all: $(PROJECTNAME)

$(PROJECTNAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
 

clean:
	rm $(PROJECTNAME) *.o