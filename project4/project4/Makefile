LD=g++
LDFLAGS=-std=c++11 -g -Wall
CXX=g++
CXXFLAGS=-std=c++11 -g -Wall
EXE=Project4.out
OBJS=Project4.o SecondHash.o MainHash.o HashMap.o Node.o
DEPS=$(addprefix .,$(OBJS:.o=.d))

.PHONY: clean finish run val

$(EXE): $(DEPS) $(OBJS)
				$(LD) $(LDFLAGS) $(LDLIBS) $(OBJS) -o $@

.%.d: %.cpp
			@$(RM) $@; \
			$(CXX) -MM -MF $@ -MT "$(<:.cpp=.o) $@" -c $(CPPFLAGS) $<

$(OBJS): %.o: %.cpp
			$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(DEPS) $(EXE)

run: $(EXE)
		./$(EXE) $(FILE)

val:
	valgrind ./$(EXE) $(FILE)

finish: clean
	rm -rf project4.zip			#This command will remove an existing zip
	zip project4.zip ./*			#Command to Zip all the .cpp, .h and Makefile
