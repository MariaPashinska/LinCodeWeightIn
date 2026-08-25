CFLAGS =  -m64 -O3 -DNDEBUG -ansi -static-libstdc++ -static-libgcc -std=c++11  -march=native -I./include 
#If the target architecture has AVX512 VPOPCNTDQ instructions add the following flag to CFLAGS

CC = g++
#Alternative compilers:
#clang++
#x86_64-w64-mingw32-g++
BUILDDIR = build
OBJ = Test-UI

all: $(OBJ) clean

$(OBJ): driver.o  testScalar_WeightDistribution.o \
 testScalar_MinimumDistance.o \
 testScalar_SearchEqual.o \
 testScalar_SearchLessThan.o \
 testScalar_CountEqual.o \
 testScalar_CountLessThan.o \
 LinCodeWeightInv.a $(BUILDDIR)
	$(CC) $(CFLAGS) -lm driver.o -L. LinCodeWeightInv.a -o ./build/$(OBJ)
	

	$(CC) $(CFLAGS) -lm testScalar_WeightDistribution.o -L. LinCodeWeightInv.a -o ./build/testScalar_WeightDistribution
	
	$(CC) $(CFLAGS) -lm testScalar_MinimumDistance.o -L. LinCodeWeightInv.a -o ./build/testScalar_MinimumDistance

	$(CC) $(CFLAGS) -lm testScalar_SearchEqual.o -L. LinCodeWeightInv.a -o ./build/testScalar_SearchEqual

	$(CC) $(CFLAGS) -lm testScalar_SearchLessThan.o -L. LinCodeWeightInv.a -o ./build/testScalar_SearchLessThan
	

	$(CC) $(CFLAGS) -lm testScalar_CountEqual.o -L. LinCodeWeightInv.a -o ./build/testScalar_CountEqual

	$(CC) $(CFLAGS) -lm testScalar_CountLessThan.o -L. LinCodeWeightInv.a -o ./build/testScalar_CountLessThan
	
	

Data.o: ./src/Data.cpp ./include/Data.h
	$(CC) $(CFLAGS) -c ./src/Data.cpp -o Data.o
Polynomials.o: ./src/Polynomials.cpp ./include/Polynomials.h
	$(CC) $(CFLAGS) -c ./src/Polynomials.cpp -o Polynomials.o
ReadWrite.o: ./src/ReadWrite.cpp ./include/ReadWrite.h ./include/Polynomials.h
	$(CC) $(CFLAGS) -c ./src/ReadWrite.cpp -o ReadWrite.o
LinCodeWeightInv.o: ./src/LinCodeWeightInv.cpp ./include/LinCodeWeightInv.h ./include/ReadWrite.h ./include/Polynomials.h ./include/Data.h ./include/lib128.h ./include/lib256.h ./include/lib512.h
	$(CC) $(CFLAGS) -c ./src/LinCodeWeightInv.cpp -o LinCodeWeightInv.o
testDriver.o: ./src/testDriver.cpp ./include/testDriver.h ./include/LinCodeWeightInv.h ./include/Data.h
	$(CC) $(CFLAGS) -c ./src/testDriver.cpp -o testDriver.o
driver.o: ./testProgram/Source.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Source.cpp -o driver.o
	

testScalar_WeightDistribution.o: ./testProgram/TestScalar.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/TestScalar.cpp -o testScalar_WeightDistribution.o
	
	

testScalar_MinimumDistance.o: ./testProgram/TestScalar_MinimumDistance.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/TestScalar_MinimumDistance.cpp -o testScalar_MinimumDistance.o
	

testScalar_SearchEqual.o: ./testProgram/TestScalar_SearchEqual.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/TestScalar_SearchEqual.cpp -o testScalar_SearchEqual.o
	

testScalar_SearchLessThan.o: ./testProgram/TestScalar_SearchLessThan.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/TestScalar_SearchLessThan.cpp -o testScalar_SearchLessThan.o
		
	

testScalar_CountEqual.o: ./testProgram/TestScalar_CountEqual.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/TestScalar_CountEqual.cpp -o testScalar_CountEqual.o
	

testScalar_CountLessThan.o: ./testProgram/TestScalar_CountLessThan.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/TestScalar_CountLessThan.cpp -o testScalar_CountLessThan.o
	
LinCodeWeightInv.a:   ReadWrite.o Data.o LinCodeWeightInv.o testDriver.o Polynomials.o
	ar rcs LinCodeWeightInv.a  ReadWrite.o Data.o LinCodeWeightInv.o testDriver.o Polynomials.o

libs: LinCodeWeightInv.a
$(BUILDDIR): ./testFiles/TestDataBig ./testFiles/TestDataSmall ./testFiles/ArticleData 
	mkdir -p build
	cp ./testFiles/TestDataBig ./build/TestDataBig
	cp ./testFiles/TestDataSmall ./build/TestDataSmall
	cp ./testFiles/ArticleData ./build/ArticleData
install: LinCodeWeightInv.a
	mkdir -p lib
	cp LinCodeWeightInv.a ./lib/LinCodeWeightInv.a
	-rm *.o
clean:
	-rm *.o

