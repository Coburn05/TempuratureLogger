logger: logger.o
	g++ -Wall logger.o -o logger

logger.o: logger.cpp
	g++ -Wall -c logger.cpp

clean:
	rm -f logger.o logger

all: logger
