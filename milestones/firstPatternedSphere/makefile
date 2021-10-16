.PHONY = all clean

CORE_CPP := ${shell find ../../src -name "*.cpp"}
CORE_HEADERS := ${shell find ../../src -name "*.h"}
CORE_OBJS := ${CORE_CPP:%.cpp=%.o}

MAIN = firstPatternedSphere.out

all: ${MAIN} clean

${MAIN}: ${CORE_OBJS} firstPatternedSphere.o
	g++ -o ${MAIN} ${CORE_OBJS} firstPatternedSphere.o -I/home/william/CPP/Projects/RayTracer2/

${CORE_OBJS}: ${CORE_CPP} ${CORE_HEADERS}
	g++ -o $@ -c $(subst .o,.cpp,$@) -I/home/william/CPP/Projects/RayTracer2/

firstPatternedSphere.o: firstPatternedSphere.cpp ${CORE_HEADERS}
	g++ -c firstPatternedSphere.cpp -I/home/william/CPP/Projects/RayTracer2/

clean:
	rm ${CORE_OBJS} ${TEST_OBJS} firstPatternedSphere.o

