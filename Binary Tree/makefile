proj4.x: bet.cpp proj4_driver.o
	g++ -std=c++11 -Wall -pedantic -o proj4.x bet.cpp proj4_driver.o

proj4_driver.o: proj4_driver.cpp bet.cpp
	g++ -c -std=c++11 -Wall -pedantic proj4_driver.cpp


clean:
	rm -f *.o *.x core.*