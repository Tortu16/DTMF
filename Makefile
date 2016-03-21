jack: Sine.cpp
	g++ -O3 -o jack Sine.cpp `pkg-config --cflags --libs jack` -lm


clean: 
	rm -f *.o

clean-all: clean
	rm -f *~ jack


