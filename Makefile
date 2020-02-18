TARGETS = bin/affichage bin/test #bin/exemple
INCLUDE_DIR_SDL = -I/usr/include/SDL2

CC = g++
LD = g++
LDFLAGS = -lSDL2 -lSDL2_image #-lSDL2_ttf -lSDL2_mixer  
CCFLAGS = -Wall -c -ggdb

all: $(TARGETS)

bin/affichage: obj/mainAffichage.o obj/Image.o obj/Pixel.o
	$(LD) -o $@ $^ $(LDFLAGS) 

bin/test: obj/mainTest.o obj/Image.o obj/Pixel.o
	$(LD) -o $@ $^ $(LDFLAGS) $(INCLUDE_DIR_SDL)

obj/mainAffichage.o: src/mainAffichage.cpp src/Image.h src/Pixel.h
	$(CC) -o $@ $< $(CCFLAGS) $(INCLUDE_DIR_SDL)

obj/mainTest.o: src/mainTest.cpp src/Image.h src/Pixel.h
	$(CC) -o $@ $< $(CCFLAGS) $(INCLUDE_DIR_SDL)

obj/Image.o: src/Image.cpp src/Image.h src/Pixel.h
	$(CC) -o $@ $< $(CCFLAGS) $(INCLUDE_DIR_SDL)

obj/Pixel.o: src/Pixel.cpp src/Pixel.h
	$(CC) -o $@ $< $(CCFLAGS)

clean:
	rm obj/*.o $(TARGETS)
