.PHONY = all clean

CORE_CPP := ${shell find ../../src -name "*.cpp"}
CORE_HEADERS := ${shell find ../../src -name "*.h"}
CORE_OBJS := ${CORE_CPP:%.cpp=%.o}

MAIN = firstPattern.out

all: ${MAIN} clean

${MAIN}: ${CORE_OBJS} firstPattern.o
	g++ -o ${MAIN} ${CORE_OBJS} firstPattern.o -I/home/william/CPP/Projects/RayTracer2/

${CORE_OBJS}: ${CORE_CPP} ${CORE_HEADERS}
	g++ -o $@ -c $(subst .o,.cpp,$@) -I/home/william/CPP/Projects/RayTracer2/

firstPattern.o: firstPattern.cpp ${CORE_HEADERS}
	g++ -c firstPattern.cpp -I/home/william/CPP/Projects/RayTracer2/

clean:
	rm ${CORE_OBJS} ${TEST_OBJS} firstPattern.o

