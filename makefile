#Makefile Template 
#Created By: Chris Manlove 

EXE = encrypto
CXX = @clang++
CXXFLAGS = -Wall -g -std=c++20 -O3
#LINKERFLAGS

$(EXE): $(OBJ) makefile
		@rm -f $(EXE)
#$(CXX) *.cpp $(CXXFLAGS) $(LINKERFLAGS) -o $(EXE)
		$(CXX) *.cpp $(CXXFLAGS) -o $(EXE)
clean:
		@rm -f $(EXE)
		@rm -f encrypted.txt
		@rm -f plaintext.*
run: $(EXE)
		@./$(EXE)
test: $(EXE)
		@./$(EXE) key.txt text.txt 1
		@./$(EXE) key.txt encrypted.txt 0
