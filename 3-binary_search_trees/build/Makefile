CC 			= gcc
CFLAGS 		= -Wall -Wextra -g
#VPATH		= /$(realpath $(CURDIR))
PROJDIR		= $(realpath $(CURDIR))
SRC 		= BST_Part1_Akiel_Aries.c
TARGET 		= main
VERBOS 		= TRUE


all: compile run

compile:
	${CC} ${CFLAGS} ${SRC} -o $(TARGET)

run:
	./${TARGET}

clean:
	rm -f $(PROJDIR/*.o) $(TARGET) *~


