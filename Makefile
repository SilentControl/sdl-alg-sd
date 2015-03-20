build:
	g++ -o zombie.out -std=gnu++11 *.cpp -Wall `sdl2-config --cflags --libs`

run:
	./zombie.out

clean:
	rm -rf zombie.out

