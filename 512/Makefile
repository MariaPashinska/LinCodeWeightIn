CFLAGS =  -m64 -O3 -DNDEBUG -ansi -static-libstdc++ -static-libgcc -std=c++11 - -march=native -mavx512vpopcntdq -I./include 
#If the target architecture has AVX512 VPOPCNTDQ instructions add the following flag to CFLAGS
#-mavx512vpopcntdq
CC = g++
#Alternative compilers:
#clang++
#x86_64-w64-mingw32-g++
BUILDDIR = build
OBJ = Test-UI

all: $(OBJ) clean

$(OBJ): driver.o test512_WeightDistribution.o \
test512_MinimumDistance.o  \
test512_SearchEqual.o \
test512_SearchLessThan.o  \
test512_CountEqual.o  \
test512_CountLessThan.o \
 LinCodeWeightInv.a $(BUILDDIR)
	$(CC) $(CFLAGS) -lm driver.o -L. LinCodeWeightInv.a -o ./build/$(OBJ)
	
	
	$(CC) $(CFLAGS) -lm test512_WeightDistribution.o -L. LinCodeWeightInv.a -o ./build/test512_WeightDistribution
	
	$(CC) $(CFLAGS) -lm test512_MinimumDistance.o -L. LinCodeWeightInv.a -o ./build/test512_MinimumDistance
	
	$(CC) $(CFLAGS) -lm test512_SearchEqual.o -L. LinCodeWeightInv.a -o ./build/test512_SearchEqual
	
	$(CC) $(CFLAGS) -lm test512_SearchLessThan.o -L. LinCodeWeightInv.a -o ./build/test512_SearchLessThan
	
	$(CC) $(CFLAGS) -lm test512_CountEqual.o -L. LinCodeWeightInv.a -o ./build/test512_CountEqual
	
	$(CC) $(CFLAGS) -lm test512_CountLessThan.o -L. LinCodeWeightInv.a -o ./build/test512_CountLessThan
	

lib512.o: ./src/lib512.cpp ./include/lib512.h ./include/ReadWrite.h ./include/Data.h ./include/Polynomials.h
	$(CC) $(CFLAGS) -c ./src/lib512.cpp -o lib512.o
Data.o: ./src/Data.cpp ./include/Data.h
	$(CC) $(CFLAGS) -c ./src/Data.cpp -o Data.o
Polynomials.o: ./src/Polynomials.cpp ./include/Polynomials.h
	$(CC) $(CFLAGS) -c ./src/Polynomials.cpp -o Polynomials.o
ReadWrite.o: ./src/ReadWrite.cpp ./include/ReadWrite.h ./include/Polynomials.h
	$(CC) $(CFLAGS) -c ./src/ReadWrite.cpp -o ReadWrite.o
LinCodeWeightInv.o: ./src/LinCodeWeightInv.cpp ./include/LinCodeWeightInv.h ./include/ReadWrite.h ./include/Polynomials.h ./include/Data.h ./include/lib512.h ./include/lib256.h ./include/lib512.h
	$(CC) $(CFLAGS) -c ./src/LinCodeWeightInv.cpp -o LinCodeWeightInv.o
testDriver.o: ./src/testDriver.cpp ./include/testDriver.h ./include/LinCodeWeightInv.h ./include/Data.h
	$(CC) $(CFLAGS) -c ./src/testDriver.cpp -o testDriver.o
driver.o: ./testProgram/Source.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Source.cpp -o driver.o
	
	
test512_WeightDistribution.o: ./testProgram/Test512.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Test512.cpp -o test512_WeightDistribution.o
	
	
test512_MinimumDistance.o: ./testProgram/Test512_MinimumDistance.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Test512_MinimumDistance.cpp -o test512_MinimumDistance.o
	
test512_SearchEqual.o: ./testProgram/Test512_SearchEqual.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Test512_SearchEqual.cpp -o test512_SearchEqual.o
	
test512_SearchLessThan.o: ./testProgram/Test512_SearchLessThan.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Test512_SearchLessThan.cpp -o test512_SearchLessThan.o
		
test512_CountEqual.o: ./testProgram/Test512_CountEqual.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Test512_CountEqual.cpp -o test512_CountEqual.o
	
test512_CountLessThan.o: ./testProgram/Test512_CountLessThan.cpp ./include/LinCodeWeightInv.h ./include/testDriver.h
	$(CC) $(CFLAGS) -c ./testProgram/Test512_CountLessThan.cpp -o test512_CountLessThan.o
	
LinCodeWeightInv.a: lib512.o   ReadWrite.o Data.o LinCodeWeightInv.o testDriver.o Polynomials.o
	ar rcs LinCodeWeightInv.a lib512.o  ReadWrite.o Data.o LinCodeWeightInv.o testDriver.o Polynomials.o

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

