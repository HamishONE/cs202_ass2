CXX = g++
CXXFLAGS = -Wall -g

all: traffic_test

traffic_test: test.cpp Traffic/*.cpp
	$(CXX) $(CXXFLAGS) -o traffic_test $^

test: traffic_test
	./traffic_test

clean:
	del /Q traffic_test.exe
