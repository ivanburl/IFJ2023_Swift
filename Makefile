all:
	mkdir -p build
	cd build && cmake ..
	cd build && cmake --build . -j 10
	mv ./build/*IFJ* ./
clean:
	rm ./build/*