CC 			= gcc
CFLAGS 		= -g -Wall
SRCFILES	= main.c bubbleSort.c insertionSort.c selectionSort.c
OBJFILES 	= main.o bubbleSort.o insertionSort.o selectionSort.o
TARGET 		= main

all: $(TARGET)

$(TARGET) : ${OBJFILES}
	${CC} ${CFLAGS} ${SRCFILES} -o $(TARGET) ${OBJFILES}

clean:
	rm -f $(OBJFILES) $(TARGET) *~

