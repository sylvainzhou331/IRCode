DIR_INC = ./include
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_BIN = ./

SRC =  $(wildcard ${DIR_SRC}/*.cpp)
OBJ = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${SRC})) main.cpp

TARGET = main

BIN_TARGET = ${DIR_BIN}/${TARGET}

CC = g++
CFLAGS = -g -Wall -I${DIR_INC}

${BIN_TARGET}:${OBJ}
	$(CC) $(OBJ) -o $@
${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp
	$(CC) $(CFLAGS) -c  $< -o $@
.PHONY:clean
clean:
	rm -rf ${DIR_OBJ}/*.o