.PHONY = all clean

PROJ_DIR := ${shell pwd}
PROJ_DIR := ${shell dirname ${PROJ_DIR}}
PROJ_DIR := ${shell dirname ${PROJ_DIR}}

CORE_CPP := ${shell find ../../src -name "*.cpp"}
CORE_HEADERS := ${shell find ../../src -name "*.h"}
CORE_OBJS := ${CORE_CPP:%.cpp=%.o}

MAIN = firstImage.out

all: ${MAIN} clean

${MAIN}: ${CORE_OBJS} firstImage.o
	g++ -o ${MAIN} ${CORE_OBJS} firstImage.o -I${PROJ_DIR}

${CORE_OBJS}: ${CORE_CPP} ${CORE_HEADERS}
	g++ -o $@ -c $(subst .o,.cpp,$@) -I${PROJ_DIR}

firstImage.o: firstImage.cpp ${CORE_HEADERS}
	g++ -c firstImage.cpp -I${PROJ_DIR}

clean:
	rm ${CORE_OBJS} ${TEST_OBJS}
