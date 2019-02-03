default: examples

examples: examples.cpp pbmimage.cpp pgmimage.cpp
	g++ -O3 $^ -o $@

clean:
	rm -f a.out *~ examples ex*_out.p*m
