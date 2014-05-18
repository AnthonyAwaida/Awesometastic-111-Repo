SRC = slug_mem.c memtest.c
EXE = memtest
OBJ = memtest.o slug_mem.o

all : ${EXE}

${EXE} : ${SRC}
	gcc -o memtest memtest.c -lm slug_mem.c
	
clean :
	- rm ${OBJ}

run :
	make clean
	./${EXE}