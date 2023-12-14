all: main

main: main.cpp file_processor.cpp
	g++ -o main main.cpp file_processor.cpp -I.

clean:
	rm -f main debug

debug:
	g++ -g -o debug main.cpp file_processor.cpp -I. -fstandalone-debug