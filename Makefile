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
	@echo installing executable file to $${PREFIX}/bin
	@mkdir -p ${PREFIX}/bin
	@cp -f ${NAME} ${PREFIX}/bin
	@chmod 755 ${PREFIX}/bin/${NAME}
	@mkdir -p ${PREFIX}/share/marvin
	@mkdir -p ${PREFIX}/share/marvin/scripts
	@mkdir -p ${PREFIX}/share/marvin/license
	@install ASDKinstaller.sh ${PREFIX}/share/marvin/scripts
	@install JDKinstaller.sh ${PREFIX}/share/marvin/scripts
	@install editorSetup.sh ${PREFIX}/hare/marvin/scripts
	@install LICENSE ${PREFIX}/share/marvin/license

uninstall:
	@echo removing executable file from ${PREFIX}/bin
	@rm -f ${PREFIX}/bin/${NAME}
	@rm -f ${PREFIX}/share/${NAME}

.PHONY: all options clean dist install uninstall
