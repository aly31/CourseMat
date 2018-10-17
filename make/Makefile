GC= g++ -g --std=c++0x

result: main.o chunkedArray.h chunkedArray.o 
	$(GC) main.o chunkedArray.o -o result

main.o: main.cpp
	$(GC) -c main.cpp

chunkedArray.o: chunkedArray.cpp
	$(GC) -c chunkedArray.cpp 
clean:
	rm *.o result
