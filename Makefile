# detrito, march 2009

CC = g++
CCFLAGS = 

#include /etc/make.conf

all:	exifclean exifcopy exifprint

exifclean: exifclean.o
	$(CC) $(CCFLAGS) -o exifclean exifclean.o -lexiv2

exifclean.o: exifclean.cpp
	$(CC) $(CCFLAGS) -c exifclean.cpp

exifcopy: exifcopy.o
	$(CC) $(CCFLAGS) -o exifcopy exifcopy.o -lexiv2

exifcopy.o: exifcopy.cpp
	$(CC) $(CCFLAGS) -c exifcopy.cpp

exifprint: exifprint.o
	$(CC) $(CCFLAGS) -o exifprint exifprint.o -lexiv2

exifprint.o: exifprint.cpp
	$(CC) $(CCFLAGS) -c exifprint.cpp

clean:
	rm -f exifclean exifclean.o exifcopy exifcopy.o exifprint exifprint.o

