build: main.cpp
	g++ -std=c++11 -g -Wall *.cpp -o bonus 
clean: 
	$(RM) bonus