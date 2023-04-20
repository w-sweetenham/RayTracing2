.PHONY = all clean

PROJ_DIR := ${shell pwd}
PROJ_DIR := ${shell dirname ${PROJ_DIR}}

CORE_CPP := ${shell find ../src -name "*.cpp"}
CORE_HEADERS := ${shell find ../src -name "*.h"}
CORE_OBJS := ${CORE_CPP:%.cpp=%.o}

all: example1.ppm example2.ppm example3.ppm clean

example1.ppm: example1.out
	@echo "running example1" 
	./example1.out

example2.ppm: example2.out
	@echo "running example2" 
	./example2.out

example3.ppm: example3.out
	@echo "running example3" 
	./example3.out

example1.out: ${CORE_OBJS} example1.o
	g++ -o example1.out ${CORE_OBJS} example1.o -I${PROJ_DIR}

example2.out: ${CORE_OBJS} example2.o
	g++ -o example2.out ${CORE_OBJS} example2.o -I${PROJ_DIR}

example3.out: ${CORE_OBJS} example3.o
	g++ -o example3.out ${CORE_OBJS} example3.o -I${PROJ_DIR}

${CORE_OBJS}: ${CORE_CPP} ${CORE_HEADERS}
	g++ -o $@ -c $(subst .o,.cpp,$@) -I${PROJ_DIR}

example1.o: example1.cpp ${CORE_HEADERS}
	g++ -c example1.cpp -I${PROJ_DIR}

example2.o: example2.cpp ${CORE_HEADERS}
	g++ -c example2.cpp -I${PROJ_DIR}

example3.o: example3.cpp ${CORE_HEADERS}
	g++ -c example3.cpp -I${PROJ_DIR}

clean:
	rm example1.o example2.o example3.o ${CORE_OBJS} ${TEST_OBJS}

