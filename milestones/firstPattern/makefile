.PHONY = all clean

PROJ_DIR := ${shell pwd}
PROJ_DIR := ${shell dirname ${PROJ_DIR}}
PROJ_DIR := ${shell dirname ${PROJ_DIR}}

CORE_CPP := ${shell find ../../src -name "*.cpp"}
CORE_HEADERS := ${shell find ../../src -name "*.h"}
CORE_OBJS := ${CORE_CPP:%.cpp=%.o}

MAIN = firstPattern.out

all: ${MAIN} clean

${MAIN}: ${CORE_OBJS} firstPattern.o
	g++ -o ${MAIN} ${CORE_OBJS} firstPattern.o -I${PROJ_DIR}

${CORE_OBJS}: ${CORE_CPP} ${CORE_HEADERS}
	g++ -o $@ -c $(subst .o,.cpp,$@) -I${PROJ_DIR}

firstPattern.o: firstPattern.cpp ${CORE_HEADERS}
	g++ -c firstPattern.cpp -I${PROJ_DIR}

clean:
	rm ${CORE_OBJS} ${TEST_OBJS} firstPattern.o

