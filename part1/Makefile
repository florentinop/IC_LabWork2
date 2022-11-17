all:
	@(if [ ! -d build ]; then mkdir build; fi; cd build;\
	  if [ ! -d part1-bin ]; then mkdir part1-bin; fi; cmake ..; make)

clean:
	rm -rf build part1-bin
