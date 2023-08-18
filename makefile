CXX = g++
CXXFLAGS = -Wall

minesweeper:  Grid.h Task_Handler.h minesweeper.cpp
	$(CXX) $(CXXFLAGS) Grid.h Task_Handler.h minesweeper.cpp -o minesweeper

Task_Handler.o: Task_Handler.h
	$(CXX) $(CXXFLAGS) -c Task_Handler.h

clean:
	rm *.o*
	rm *~ 

run:
	./minesweeper