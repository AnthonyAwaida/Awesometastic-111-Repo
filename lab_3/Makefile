SRC = slug_mem.c memtest.c
TST1 = memtest
TST2 = memtest2
OBJ = memtest.o slug_mem.o

all : ${TST1} ${TST2}

${TST1} : ${SRC}
	gcc -o memtest memtest.c -lm slug_mem.c

${TST2} : ${SRC}
	gcc -o memtest2 memtest2.c -lm slug_mem.c
	
clean :
	- rm ${TST1} ${TST2} ${OBJ} 2>/dev/null

run_1 :
	- rm ${OBJ} 2>/dev/null
	./${TST1}

run_2 :
	- rm ${OBJ} 2>/dev/null
	./${TST2}
