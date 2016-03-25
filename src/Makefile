compile: short_path.o
	g++ short_path.o -o short_path

short_path.o: short_path.cpp short_path.h
	g++ short_path.cpp -c

.PHONY: clean

clean:
	rm short_path.o short_path