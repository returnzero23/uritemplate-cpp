CC=g++
TARGET=main
SRC=$(shell echo */*.cpp)
BUILDPATH=./build/
OBJ=$(SRC:$.cpp=$.o)
CFLAGS= -std=c++11
INCLOUDPATH= ./ext/json/include

.PHONY:clean

debug:
	$(CC) -g -c $(SRC) $(CFLAGS) -I $(INCLOUDPATH) -o $(OBJ)
	$(CC) -o $(TARGET) $(OBJ)
release:
	$(CC) -c $(SRC) $(CFLAGS)
	$(CC) -o $(TARGET) $(OBJ)
	make clean
clean:
	rm -fr *.o ./$(TARGET)