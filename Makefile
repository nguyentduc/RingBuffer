# Directory for gtest
GTEST_DIR=/u/f/e1601145/2019-2020/Embedded_Project/googletest/googletest
COPTS=-fprofile-arcs -ftest-coverage

PROJ = ringbuffer


#Unit test case
test: unit_test_case.o ringbuffer.o Gtest_main.o libgtest.a
	g++  unit_test_case.o ringbuffer.o Gtest_main.o libgtest.a $(COPTS) -pthread -o my_test
	rm -f *.o

ringbuffer.o: ringbuffer.c
	g++ -c $(COPTS) ringbuffer.c

Gtest_main.o: Gtest_main.c
	g++ -c -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) Gtest_main.c

unit_test_case.o: unit_test_case.c
	g++ -c -isystem $(GTEST_DIR)/include $(COPTS) -I$(GTEST_DIR) unit_test_case.c

libgtest.a:
	g++ -isystem $(GTEST_DIR)/include -I$(GTEST_DIR) -pthread -c $(GTEST_DIR)/src/gtest-all.cc
	ar -rv libgtest.a gtest-all.o

clean:
	rm -f *.o

########Normal run
release: ringbuffer.o main.o
	g++ ringbuffer.o main.o $(COPTS) -o my_test
	
main.o: main.c
	g++ -c main.c
	
report:
	export COV_OUTPUT=./cov_output
	lcov -rc lcov_branch_coverage=1 -c -i -d . -o .coverage.base
	lcov -rc lcov_branch_coverage=1 -c -d . -o .coverage.run
	lcov -rc lcov_branch_coverage=1 -d . -a .coverage.base -a .coverage.run -o .coverage.total
	genhtml --branch-coverage -o $(COV_OUTPUT) .coverage.total
	rm -f .coverage.base .coverage.run .coverage.total