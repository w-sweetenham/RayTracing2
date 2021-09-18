.PHONY = all clean

CORE_CPP := ${shell find ../../src -name "*.cpp"}
CORE_HEADERS := ${shell find ../../src -name "*.h"}
CORE_OBJS := ${CORE_CPP:%.cpp=%.o}

MAIN = firstShadow.out

all: ${MAIN} clean

${MAIN}: ${CORE_OBJS} firstShadow.o
	g++ -o ${MAIN} ${CORE_OBJS} firstShadow.o -I/home/william/CPP/Projects/RayTracer2/

${CORE_OBJS}: ${CORE_CPP} ${CORE_HEADERS}
	g++ -o $@ -c $(subst .o,.cpp,$@) -I/home/william/CPP/Projects/RayTracer2/

firstShadow.o: firstShadow.cpp ${CORE_HEADERS}
	g++ -c firstShadow.cpp -I/home/william/CPP/Projects/RayTracer2/

clean:
	rm ${CORE_OBJS} ${TEST_OBJS} firstShadow.o

