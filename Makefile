CC=g++

CFLAGS=  -lmenu -lform -lcurses -g -Wall
UI=curses
CFILES=src/*.cpp 
HFILES=src/*.h
all : ponka-snake
 
ponka-snake :	$(CFILES) $(HFILES) 
		$(CC) $(CFLAGS) $(CFILES) -o	ponka-snake
clean : 
	rm *.o ponka-snake
