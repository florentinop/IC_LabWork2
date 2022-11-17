all:
	@(if [ ! -d build ]; then mkdir build; fi; cd build;\
	  if [ ! -d part2-bin ]; then mkdir part2-bin; fi; cmake ..; make)

clean:
	rm -rf build part2-bin
