SRC = slug_mem.c memtest.c
TST1 = memtest
TST2 = memtest2
TST3 = memtest3
OBJ = memtest.o slug_mem.o

all : ${TST1} ${TST2} ${TST3}

${TST1} : ${SRC}
	gcc -o memtest memtest.c  slug_mem.c -lm

${TST2} : ${SRC}
	gcc -o memtest2 memtest2.c slug_mem.c -lm

${TST3} : ${SRC}
	gcc -o memtest3 memtest3.c slug_mem.c -lm
	
clean :
	- rm ${TST1} ${TST2} ${TST3} ${OBJ} 2>/dev/null

run_1 :
	- rm ${OBJ} 2>/dev/null
	./${TST1}

run_2 :
	- rm ${OBJ} 2>/dev/null
	./${TST2}

run_3 :
	- rm ${OBJ} 2>/dev/null
	./${TST3}
