#   Makefile
#   Version 
#   Author: WildfootW
#   GitHub: github.com/WildfootW
#   Copyright (C) 2019-2020 WildfootW All rights reserved.

.PHONY: all
all: grading

.PHONY: configure
configure:
	cd ./src && \
	cmake -D CMAKE_CXX_COMPILER=clang++ .

.PHONY: clean
clean:
	cd ./src && \
	make clean
	rm -f *.out *.o

.PHONY: grading
grading:
	cd ./src && \
	make grading.out
	ln -sf ./src/grading.out grading.out

.PHONY: grading_test
grading_test:
	cd ./src && \
	make grading_with_output.out
	ln -sf ./src/grading_with_output.out grading_test.out

.PHONY: snake_test
snake_test:
	cd ./src && \
	make snake_test.out
	ln -sf ./src/snake_test.out snake_test.out

.PHONY: print_test
print_test:
	cd ./src && \
	make print_test.out
	ln -sf ./src/print_test.out print_test.out

