LD=g++
LDFLAGS=-std=c++11 -g -Wall
CXX=g++
CXXFLAGS=-std=c++11 -g -Wall
EXE=Project3.out
OBJS=main.o Song.o Library.o TitleCompare.o ArtistCompare.o AlbumCompare.o GenreCompare.o YearCompare.o
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
		./$(EXE) $(LIBRARY_FILE)

val:
	valgrind ./$(EXE) $(LIBRARY_FILE)

finish: clean
	rm -rf project3.zip			#This command will remove an existing zip
	zip project3.zip ./*			#Command to Zip all the .cpp, .h and Makefile
