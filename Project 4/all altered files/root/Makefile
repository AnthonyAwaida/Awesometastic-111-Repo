CSRC = metacat.c
CEXE = metacat
COBJ = metacat.o
TSRC = metatag.c
TEXE = metatag
TOBJ = metatag.o


all : ${CEXE} ${TEXE}
	cp ${CEXE} ../../../../../../bin
	cp ${TEXE} ../../../../../../bin
	cd
	cd ../bin
	chmod a+x ${CEXE} ${TEXE}
	cd
	make clean

${TEXE} : ${TOBJ}
	cc -o ${TEXE} ${TOBJ}

${CEXE} : ${COBJ}
	cc -o ${CEXE} ${COBJ}

${TOBJ} : ${TSRC}
	cc -c ${TSRC}

${COBJ} : ${CSRC}
	cc -c ${CSRC}

clean :
	rm ${TEXE} ${CEXE} ${TOBJ} ${COBJ}
