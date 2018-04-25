#Abhishek Chakladar(axc161930)
#axc161930@utddallas.edu
#CS 3377.501

#flags needed to compile
CXX = g++
#CXXFLAGS = no cxx flags needed
CPPFLAGS = -Wall -g -I/people/cs/s/sxp127930/include
LDFLAGS = -L/people/cs/s/sxp127930/lib
LDLIBS = -lcdk -lcurses
EXECFILE = program6
OBJS = program6.o

#make the exec file
all: $(EXECFILE)

#compile the exec file using the flags above
$(EXECFILE): $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LDLIBS)

#clean up the files
clean:
	rm -f $(OBJS) $(EXECFILE) *.P *~ \#*


