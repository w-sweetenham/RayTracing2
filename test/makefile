#/home/william/CPP/Projects/RayTracer2/src /home/william/CPP/Projects/RayTracer2/test 
#/home/william/CPP/Projects/RayTracer2/test/TestAll.cpp
#/home/william/CPP/Projects/RayTracer2/
#/usr/local/lib/
#cppunit
HEADERS := /home/william/CPP/Projects/RayTracer2/src/utils/Utils.h /home/william/CPP/Projects/RayTracer2/test/utils/TestUtils.h  /home/william/CPP/Projects/RayTracer2/src/geometry/Tuple.h /home/william/CPP/Projects/RayTracer2/test/geometry/TestTuple.h  /home/william/CPP/Projects/RayTracer2/src/geometry/Matrix.h /home/william/CPP/Projects/RayTracer2/test/geometry/TestMatrix.h 
OBJS := /home/william/CPP/Projects/RayTracer2/test/build/Utils.o /home/william/CPP/Projects/RayTracer2/test/build/TestUtils.o /home/william/CPP/Projects/RayTracer2/test/build/Tuple.o /home/william/CPP/Projects/RayTracer2/test/build/TestTuple.o /home/william/CPP/Projects/RayTracer2/test/build/Matrix.o /home/william/CPP/Projects/RayTracer2/test/build/TestMatrix.o  


/home/william/CPP/Projects/RayTracer2/test/TestAll: $(OBJS) $(HEADERS) /home/william/CPP/Projects/RayTracer2/test/TestAll.cpp
	g++ /home/william/CPP/Projects/RayTracer2/test/TestAll.cpp $(OBJS) -o /home/william/CPP/Projects/RayTracer2/test/TestAll.out -I/home/william/CPP/Projects/RayTracer2/ -L/usr/local/lib/ -lcppunit

/home/william/CPP/Projects/RayTracer2/test/build/Utils.o: /home/william/CPP/Projects/RayTracer2/src/utils/Utils.cpp $(HEADERS)
	g++ -c /home/william/CPP/Projects/RayTracer2/src/utils/Utils.cpp -o /home/william/CPP/Projects/RayTracer2/test/build/Utils.o -I/home/william/CPP/Projects/RayTracer2/ -L/usr/local/lib/ -lcppunit

/home/william/CPP/Projects/RayTracer2/test/build/TestUtils.o: /home/william/CPP/Projects/RayTracer2/test/utils/TestUtils.cpp $(HEADERS)
	g++ -c /home/william/CPP/Projects/RayTracer2/test/utils/TestUtils.cpp -o /home/william/CPP/Projects/RayTracer2/test/build/TestUtils.o -I/home/william/CPP/Projects/RayTracer2/ -L/usr/local/lib/ -lcppunit

/home/william/CPP/Projects/RayTracer2/test/build/Tuple.o : /home/william/CPP/Projects/RayTracer2/src/geometry/Tuple.cpp $(HEADERS)
	g++ -c /home/william/CPP/Projects/RayTracer2/src/geometry/Tuple.cpp -o /home/william/CPP/Projects/RayTracer2/test/build/Tuple.o  -I/home/william/CPP/Projects/RayTracer2/ -L/usr/local/lib/ -lcppunit


/home/william/CPP/Projects/RayTracer2/test/build/TestTuple.o : /home/william/CPP/Projects/RayTracer2/test/geometry/TestTuple.cpp $(HEADERS)
	g++ -c /home/william/CPP/Projects/RayTracer2/test/geometry/TestTuple.cpp -o /home/william/CPP/Projects/RayTracer2/test/build/TestTuple.o  -I/home/william/CPP/Projects/RayTracer2/ -L/usr/local/lib/ -lcppunit

/home/william/CPP/Projects/RayTracer2/test/build/Matrix.o : /home/william/CPP/Projects/RayTracer2/src/geometry/Matrix.cpp $(HEADERS)
	g++ -c /home/william/CPP/Projects/RayTracer2/src/geometry/Matrix.cpp -o /home/william/CPP/Projects/RayTracer2/test/build/Matrix.o  -I/home/william/CPP/Projects/RayTracer2/ -L/usr/local/lib/ -lcppunit

/home/william/CPP/Projects/RayTracer2/test/build/TestMatrix.o : /home/william/CPP/Projects/RayTracer2/test/geometry/TestMatrix.cpp $(HEADERS)
	g++ -c /home/william/CPP/Projects/RayTracer2/test/geometry/TestMatrix.cpp -o /home/william/CPP/Projects/RayTracer2/test/build/TestMatrix.o  -I/home/william/CPP/Projects/RayTracer2/ -L/usr/local/lib/ -lcppunit
