CFLAGS =  -m64 -O3 -DNDEBUG -ansi -static-libstdc++ -static-libgcc -std=c++11 - -march=native -I./include 
CC = g++
#Alternative compilers:
#clang++
#x86_64-w64-mingw32-g++
BUILDDIR = build
OBJ = Test-UI

all: $(OBJ) clean

$(OBJ): driver.o test128_WeightDistribution.o \
test128_MinimumDistance.o  \
test128_SearchEqual.o \
test128_SearchLessThan.o  \
test128_CountEqual.o  \
test128_CountLessThan.o \
 LinCodeWeightInv.a $(BUILDDIR)
	$(CC) $(CFLAGS) -lm driver.o -L. LinCodeWeightInv.a -o ./build/$(OBJ)
	
	
	$(CC) $(CFLAGS) -lm test128_WeightDistribution.o -L. LinCodeWeightInv.a -o ./build/test128_WeightDistribution
	
	$(CC) $(CFLAGS) -lm test128_MinimumDistance.o -L. LinCodeWeightInv.a -o ./build/test128_MinimumDistance
	
	$(CC) $(CFLAGS) -lm test128_SearchEqual.o -L. LinCodeWeightInv.a -o ./build/test128_SearchEqual
	
	$(CC) $(CFLAGS) -lm test128_SearchLessThan.o -L. LinCodeWeightInv.a -o ./build/test128_SearchLessThan
	
	$(CC) $(CFLAGS) -lm test128_CountEqual.o -L. LinCodeWeightInv.a -o ./build/test128_CountEqual
	
	$(CC) $(CFLAGS) -lm test128_CountLessThan.o -L. LinCodeWeightInv.a -o ./build/test128_CountLessThan
	

lib128.o: ./src/lib128.cpp ./include/lib128.h ./include/ReadWrite.h ./include/Data.h ./include/Polynomials.h
	$(CC) $(CFLAGS) -c ./src/lib128.cpp -o lib128.o
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
	
	
test128_WeightDistribution.o: ./testProgram/Test128.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Test128.cpp -o test128_WeightDistribution.o
	
	
test128_MinimumDistance.o: ./testProgram/Test128_MinimumDistance.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Test128_MinimumDistance.cpp -o test128_MinimumDistance.o
	
test128_SearchEqual.o: ./testProgram/Test128_SearchEqual.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Test128_SearchEqual.cpp -o test128_SearchEqual.o
	
test128_SearchLessThan.o: ./testProgram/Test128_SearchLessThan.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Test128_SearchLessThan.cpp -o test128_SearchLessThan.o
		
test128_CountEqual.o: ./testProgram/Test128_CountEqual.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Test128_CountEqual.cpp -o test128_CountEqual.o
	
test128_CountLessThan.o: ./testProgram/Test128_CountLessThan.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Test128_CountLessThan.cpp -o test128_CountLessThan.o
	
LinCodeWeightInv.a: lib128.o   ReadWrite.o Data.o LinCodeWeightInv.o testDriver.o Polynomials.o
	ar rcs LinCodeWeightInv.a lib128.o  ReadWrite.o Data.o LinCodeWeightInv.o testDriver.o Polynomials.o

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

