compile: short_path.o
	g++ short_path.o -o short_path

debug: short_path.cpp short_path.h
	g++ -g short_path.cpp -o tst -std=c++11

short_path.o: short_path.cpp short_path.h
	g++ short_path.cpp -c -std=c++11

.PHONY: clean

clean:
	rm short_path.o short_path tst
