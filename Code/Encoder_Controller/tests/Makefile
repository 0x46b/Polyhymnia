SRC_TESTS = AllTests.cpp ringbuffer_tests.cpp
SRC = ../ringbuffer.c

INCLUDE_DIR = -Iinclude -I../include

CXXBINARIES = AllTests
CC = gcc
CXX = g++
CPPFLAGS = -MMD ${INCLUDE_DIR}
CXXFLAGS = 
CFLAGS = -Wall -Wextra -std=c99 -O2 
LDFLAGS =
LDLIBS =

OBJ_TESTS = ${SRC_TESTS:%.cpp=%.o}
DEP_TESTS = ${SRC_TESTS:%.cpp=%.d}

OBJ = ${SRC:%.c=%.o}
DEP = ${SRC:%.c=%.d}

# CPPUTEST 
CPPFLAGS += -I${CPPUTEST_HOME}/include
CXXFLAGS += -include ${CPPUTEST_HOME}/include/CppUTest/MemoryLeakDetectorNewMacros.h
CFLAGS += -include ${CPPUTEST_HOME}/include/CppUTest/MemoryLeakDetectorMallocMacros.h
LDFLAGS += -L${CPPUTEST_HOME}/lib64 -lCppUTest -lCppUTestExt
#LDLIBS += -lCppuTest -lCppuTestExt

all: AllTests

test: ${CXXBINARIES}
	./AllTests

AllTests: ${OBJ}  ${OBJ_TESTS}

${CXXBINARIES}:
	$(LINK.cc) $^ -o $@ $(LDFLAGS) 

.PHONY: clean test

clean:
	${RM} ${DEP_TESTS}
	${RM} ${OBJ_TESTS}   
	${RM} main
	${RM} ${OBJ}
	${RM} ${DEP}

-include ${DEP}
-include ${DEP_TESTS}
