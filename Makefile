jack: DTMF.cpp tonedetection.cpp
	g++ -O3 -o jack DTMF.cpp `pkg-config --cflags --libs jack` -lm -fpermissive


clean: 
	rm -f *.o

clean-all: clean
	rm -f *~ jack


