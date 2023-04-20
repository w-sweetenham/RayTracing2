.PHONY = all clean

PROJ_DIR := ${shell pwd}
PROJ_DIR := ${shell dirname ${PROJ_DIR}}
PROJ_DIR := ${shell dirname ${PROJ_DIR}}

CORE_CPP := ${shell find ../../src -name "*.cpp"}
CORE_HEADERS := ${shell find ../../src -name "*.h"}
CORE_OBJS := ${CORE_CPP:%.cpp=%.o}

MAIN = firstVoxelWorld.out

all: ${MAIN} clean

${MAIN}: ${CORE_OBJS} firstVoxelWorld.o
	g++ -o ${MAIN} ${CORE_OBJS} firstVoxelWorld.o -I${PROJ_DIR}

${CORE_OBJS}: ${CORE_CPP} ${CORE_HEADERS}
	g++ -o $@ -c $(subst .o,.cpp,$@) -I${PROJ_DIR}

firstVoxelWorld.o: firstVoxelWorld.cpp ${CORE_HEADERS}
	g++ -c firstVoxelWorld.cpp -I${PROJ_DIR}

clean:
	rm ${CORE_OBJS} ${TEST_OBJS} firstVoxelWorld.o

