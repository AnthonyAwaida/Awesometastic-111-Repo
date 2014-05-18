SRC = slug_mem.c memtest.c
EXE = memtest
OBJ = memtest.o

all : ${EXE}

${EXE} : ${SRC}
	gcc -c ${SRC}
	gcc -o ${EXE} ${OBJ}
	- rm ${OBJ}
	
clean :
	- rm ${OBJ}
