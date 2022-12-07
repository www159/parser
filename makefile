
CC := gcc
OBJ_PATH := temp
CCFLAGS := -I include -g
SRC := $(wildcard *.c)
OBJS := ${patsubst %.c,%.o,${SRC}}
OBJS_WITH_DIR := ${addprefix ${OBJ_PATH}/, ${OBJS}}
TARGET := wwc

.PHONY: clean
clean: 
	-rm -rf ${OBJ_PATH}

all: make_dir ${TARGET}
${TARGET}: ${OBJS_WITH_DIR}
	${CC} -o $@ $^
${OBJ_PATH}/%.o: %.c
	${CC} -c ${CCFLAGS} -o $@ $<

fresh: clean all

make_dir:
	@if [ ! -d ${OBJ_PATH} ]; then \
	mkdir -p ${OBJ_PATH}; \
	fi