CFLAGS =  -m64 -O3 -DNDEBUG -ansi -static-libstdc++ -static-libgcc -std=c++11 - -march=native -I./include 
CC = g++
#Alternative compilers:
#clang++
#x86_64-w64-mingw32-g++
BUILDDIR = build
OBJ = Test-UI

all: $(OBJ) clean

$(OBJ): driver.o test256_WeightDistribution.o \
test256_MinimumDistance.o  \
test256_SearchEqual.o \
test256_SearchLessThan.o  \
test256_CountEqual.o  \
test256_CountLessThan.o \
 LinCodeWeightInv.a $(BUILDDIR)
	$(CC) $(CFLAGS) -lm driver.o -L. LinCodeWeightInv.a -o ./build/$(OBJ)
	
	
	$(CC) $(CFLAGS) -lm test256_WeightDistribution.o -L. LinCodeWeightInv.a -o ./build/test256_WeightDistribution
	
	$(CC) $(CFLAGS) -lm test256_MinimumDistance.o -L. LinCodeWeightInv.a -o ./build/test256_MinimumDistance
	
	$(CC) $(CFLAGS) -lm test256_SearchEqual.o -L. LinCodeWeightInv.a -o ./build/test256_SearchEqual
	
	$(CC) $(CFLAGS) -lm test256_SearchLessThan.o -L. LinCodeWeightInv.a -o ./build/test256_SearchLessThan
	
	$(CC) $(CFLAGS) -lm test256_CountEqual.o -L. LinCodeWeightInv.a -o ./build/test256_CountEqual
	
	$(CC) $(CFLAGS) -lm test256_CountLessThan.o -L. LinCodeWeightInv.a -o ./build/test256_CountLessThan
	

lib256.o: ./src/lib256.cpp ./include/lib256.h ./include/ReadWrite.h ./include/Data.h ./include/Polynomials.h
	$(CC) $(CFLAGS) -c ./src/lib256.cpp -o lib256.o
Data.o: ./src/Data.cpp ./include/Data.h
	$(CC) $(CFLAGS) -c ./src/Data.cpp -o Data.o
Polynomials.o: ./src/Polynomials.cpp ./include/Polynomials.h
	$(CC) $(CFLAGS) -c ./src/Polynomials.cpp -o Polynomials.o
ReadWrite.o: ./src/ReadWrite.cpp ./include/ReadWrite.h ./include/Polynomials.h
	$(CC) $(CFLAGS) -c ./src/ReadWrite.cpp -o ReadWrite.o
LinCodeWeightInv.o: ./src/LinCodeWeightInv.cpp ./include/LinCodeWeightInv.h ./include/ReadWrite.h ./include/Polynomials.h ./include/Data.h ./include/lib256.h ./include/lib256.h ./include/lib512.h
	$(CC) $(CFLAGS) -c ./src/LinCodeWeightInv.cpp -o LinCodeWeightInv.o
testDriver.o: ./src/testDriver.cpp ./include/testDriver.h ./include/LinCodeWeightInv.h ./include/Data.h
	$(CC) $(CFLAGS) -c ./src/testDriver.cpp -o testDriver.o
driver.o: ./testProgram/Source.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Source.cpp -o driver.o
	
	
test256_WeightDistribution.o: ./testProgram/Test256.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Test256.cpp -o test256_WeightDistribution.o
	
	
test256_MinimumDistance.o: ./testProgram/Test256_MinimumDistance.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Test256_MinimumDistance.cpp -o test256_MinimumDistance.o
	
test256_SearchEqual.o: ./testProgram/Test256_SearchEqual.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Test256_SearchEqual.cpp -o test256_SearchEqual.o
	
test256_SearchLessThan.o: ./testProgram/Test256_SearchLessThan.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Test256_SearchLessThan.cpp -o test256_SearchLessThan.o
		
test256_CountEqual.o: ./testProgram/Test256_CountEqual.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Test256_CountEqual.cpp -o test256_CountEqual.o
	
test256_CountLessThan.o: ./testProgram/Test256_CountLessThan.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Test256_CountLessThan.cpp -o test256_CountLessThan.o
	
LinCodeWeightInv.a: lib256.o   ReadWrite.o Data.o LinCodeWeightInv.o testDriver.o Polynomials.o
	ar rcs LinCodeWeightInv.a lib256.o  ReadWrite.o Data.o LinCodeWeightInv.o testDriver.o Polynomials.o

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

