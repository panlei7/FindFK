# FindFK

FindFK is a tool to obtain points along dispersion curve. 

The idea comes from [union-find algorithm](http://algs4.cs.princeton.edu/15uf/) when I'm learning Priceton's Algorithm Course in Coursera. It's based on weighted-quick-union-path-compression algorithm.

## Preparing

- Install [Cmake](www.cmake.org)
- Install [yaml-cpp](https://github.com/jbeder/yaml-cpp) (This is needed by examples)
- Install Python 3 (Plotting scipts are written in Python 3)

FindFK is only tested with Clang++-3.8

## How to use

1. Navigate into the source directory, and type:

		> mkdir build
		> cd build
		
2. Check **CMakeLists.txt** in the source directory and ensure the compiler is OK.
3. Build and test
	
		> cmake ..
		> make
		> ../bin/unit_test
		
4. Run examples

		> cd ../examples
		> ../bin/findfk fk.yaml
		
	It will create an output file "output.txt". You can adjust the paremeters in yaml file.
	
5. Plotting

		> ../python/plot_input.py input_fk.txt
		> ../python/plot_output.py input_fk.txt output_fk.txt
		
**Note**: the input file should contain an array.

## Results

[dispersion curve in f-k coordinates](doc/example_fk.md)
[dispersion curve in f-c coordinates](doc/example_fc.md)
		