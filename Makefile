# Directory for gtest

GTEST_DIR=~/2019-2020/Embedded_Project/googletest/googletest

#Unit test case
test: unit_test_case.o ringbuffer.o Gtest_main.o libgtest.a
	g++  unit_test_case.o ringbuffer.o Gtest_main.o libgtest.a -pthread -o my_test
	rm -f *.o

ringbuffer.o: ringbuffer.c
		g++ -c ringbuffer.c

Gtest_main.o: Gtest_main.c
	g++ -c -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) Gtest_main.c

unit_test_case.o: unit_test_case.c
	g++ -c -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) unit_test_case.c

libgtest.a:
	g++ -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -c $(GTEST_DIR)/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o

clean:
	rm -f *.o

########Normal run
release: ringbuffer.o main.o
	g++ ringbuffer.o main.o -o my_test
	
main.o: main.c
	g++ -c main.c