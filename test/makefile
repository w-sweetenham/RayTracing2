.PHONY = all clean

CORE_CPP := ${shell find ../src -name "*.cpp"}
CORE_HEADERS := ${shell find ../src -name "*.h"}
CORE_OBJS := ${CORE_CPP:%.cpp=%.o}

TEST_CPP := ${shell find ./ -name "*.cpp"}
TEST_HEADERS := ${shell find ./ -name "*.h"}
TEST_OBJS := ${TEST_CPP:%.cpp=%.o}

MAIN = TestAll.out

all: ${MAIN} clean

${MAIN}: ${CORE_OBJS} ${TEST_OBJS}
	g++ -o ${MAIN} ${CORE_OBJS} ${TEST_OBJS} -I/home/william/CPP/Projects/RayTracer2/ -L/usr/local/lib/ -lcppunit

${TEST_OBJS}: ${TEST_CPP} ${TEST_HEADERS} ${CORE_HEADERS}
	g++ -o $@ -c $(subst .o,.cpp,$@) -I/home/william/CPP/Projects/RayTracer2/

${CORE_OBJS}: ${CORE_CPP} ${CORE_HEADERS}
	g++ -o $@ -c $(subst .o,.cpp,$@) -I/home/william/CPP/Projects/RayTracer2/

clean:
	rm ${CORE_OBJS} ${TEST_OBJS}
