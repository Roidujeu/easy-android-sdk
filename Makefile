# See LICENSE file for copyright and license details.

include config.mk

SRC = ${NAME}.c
OBJ = ${SRC:.c=.o}

all: options ${NAME}

options:
	@echo ${NAME} build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS   = ${LDFLAGS}"
	@echo "CC       = ${CC}"

${OBJ}: marvin.h config.mk

.c.o:
	@${CC} ${CFLAGS} -c $<

${NAME}: ${OBJ}
	@${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	@echo cleaning
	@rm -f ${NAME} ${OBJ} ${NAME}-${VERSION}.tar.gz

dist: clean
	@echo creating dist tarball
	@mkdir -p ${NAME}-${VERSION}
	@cp -R Makefile LICENSE config.mk \
		${SRC} ${NAME}-${VERSION}
	@tar -cf ${NAME}-${VERSION}.tar ${NAME}-${VERSION}
	@gzip ${NAME}-${VERSION}.tar
	@rm -rf ${NAME}-${VERSION}

install: all
	@echo installing executable file to ${DESTDIR}${PREFIX}/bin
	@mkdir -p ${DESTDIR}${PREFIX}/bin
	@cp -f ${NAME} ${DESTDIR}${PREFIX}/bin
	@chmod 755 ${DESTDIR}${PREFIX}/bin/${NAME}
	@mkdir -p ${DESTDIR}${PREFIX}/share/marvin
	@mkdir -p ${DESTDIR}${PREFIX}/share/marvin/scripts
	@mkdir -p ${DESTDIR}${PREFIX}/share/marvin/license
	@install ASDKinstaller.sh ${DESTDIR}${PREFIX}/share/marvin/scripts
	@install JDKinstaller.sh ${DESTDIR}${PREFIX}/share/marvin/scripts
	@install editorSetup.sh ${DESTDIR}${PREFIX}/hare/marvin/scripts
	@install LICENSE ${DESTDIR}${PREFIX}/share/marvin/license

uninstall:
	@echo removing executable file from ${DESTDIR}${PREFIX}/bin
	@rm -f ${DESTDIR}${PREFIX}/bin/${NAME}
	@rm -f ${DESTDIR}${PREFIX}/share/marvin

.PHONY: all options clean dist install uninstall
