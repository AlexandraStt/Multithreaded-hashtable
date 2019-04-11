CXX       = g++
CXXFLAGS  = --std=c++17 
LIBS      = -lgtest -lpthread 
SRCS      = $(wildcard *.cpp) 
OBJS      = $(filter %.o,$(SRCS:.cpp=.o) $(SRCS:.cc=.o))

hashtable: $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LIBS)  

valgrind_hashtable : $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LIBS)  

%.o: %.cc 
	$(CXX) $(CXXFLAGS) -c $< -O0 -o $@

clean:
	@rm -f *.o
	@rm -f hashtable

.PHONY: clean valgrind
