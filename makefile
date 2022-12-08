CC := gcc
CCFLAGS := -g

BUILD_PATH := build
OBJ_PATH := ${BUILD_PATH}/temp
BIN_PATH := ${BUILD_PATH}/bin
TEST_BIN_PATH := ${BUILD_PATH}/test
TEST_OBJ_PATH := ${OBJ_PATH}/test
TARGET_OBJ_PATH := ${OBJ_PATH}/target
TEST_SRC_PATH := test
SRC_PATH := src
HEAD_PATH := include


SRC := $(foreach dir, ${SRC_PATH}, ${wildcard ${dir}/*.c})
SRC_WITHOUT_DIR := ${notdir ${SRC}}

OBJS := ${patsubst %.c,%.o,${SRC_WITHOUT_DIR}}
OBJS_WITH_DIR := ${addprefix ${OBJ_PATH}/, ${OBJS}}

TEST_TARGET:= ${basename ${notdir ${wildcard ${TEST_SRC_PATH}/*.c}}}
TEST_OBJS := ${addsuffix ${TEST_TARGAT}, .o} 
TEST_OBJS_WITH_DIR := ${addprefix ${TEST_OBJ_PATH}/, ${TEST_OBJS}}
TEST_TARGET_WITH_DIR := ${addprefix ${TEST_BIN_PATH}/, ${TEST_TARGET}}

TARGET := ${patsubst %.c,%,${notdir ${wildcard ${CURDIR}/*.c}}}
TARGET_OBJS := ${addsuffix ${TARGET}, .o}
TARGET_OBJS_WITH_DIR := ${addprefix ${TARGET_OBJ_PATH}/, ${TARGET_OBJS}}
TARGET_WITH_DIR := ${addprefix ${BIN_PATH}/, ${TARGET}}

CCFLAGS += ${addprefix -I,${SRC_PATH}}
CCFLAGS += ${addprefix -I,${HEAD_PATH}}

all: make_dir ${TARGET} ${TEST_TARGET}

${TEST_TARGET}:%: ${TEST_OBJ_PATH}/%.o ${OBJS_WITH_DIR}
	${CC} -o ${TEST_BIN_PATH}/$@ $^

${TARGET}:%: ${TARGET_OBJ_PATH}/%.o ${OBJS_WITH_DIR}
	${CC} -o ${BIN_PATH}/$@ $^

${TEST_OBJ_PATH}/%.o: ${TEST_SRC_PATH}/%.c
	${CC} -c ${CCFLAGS} -o $@ $<

${TARGET_OBJ_PATH}/%.o: ${CURDIR}/%.c
	${CC} -c ${CCFLAGS} -o $@ $<

${OBJ_PATH}/%.o: ${SRC_PATH}/%.c
	${CC} -c ${CCFLAGS} -o $@ $<

fresh: clean all

make_dir:
	@if [ ! -d ${BUILD_PATH} ]; then \
	# mkdir -p ${OBJ_PATH}; \
	mkdir -p ${BIN_PATH}; \
	mkdir -p ${TEST_BIN_PATH}; \
	mkdir -p ${TARGET_OBJ_PATH}; \
	mkdir -p ${TEST_OBJ_PATH}; \
	fi

.PHONY: clean debug
clean: 
	-rm -rf ${BIN_PATH}/${TARGET} ${OBJS_WITH_DIR} ${TEST_TARGET_WITH_DIR} ${TARGET_OBJS_WITH_DIR}
debug: 
	@echo "${SRC}"
	@echo "${basename ${notdir ${wildcard ${TEST_SRC_PATH}/*.c}}}"
	@echo "${TARGET_WITH_DIR}"