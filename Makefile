CXX = g++

CXXFLAGS = $(shell gtest-config --cppflags --cxxflags) -Isrc -W -Wall -mno-cygwin
CXXFLAGS += -DUNICODE -D_UNICODE
CXXFLAGS_TEST    = -D__TEST
CXXFLAGS_DEBUG   = -D__DEBUG -mwindows 
CXXFLAGS_RELEASE = -D__RELEASE -mwindows -O2

LDFLAGS = -W -Wall

PROGRAM_NAME = Shrimp

PROGRAM_TEST    = build/test/$(PROGRAM_NAME)Test.exe
PROGRAM_DEBUG   = build/debug/$(PROGRAM_NAME).exe
PROGRAM_RELEASE = build/release/$(PROGRAM_NAME).exe

SRC_NAMES = $(shell find src -name "*.cpp" | sed -e 's/^src\///')

OBJS_TEST    = $(SRC_NAMES:%.cpp=build/test/obj/%.o)
OBJS_DEBUG   = $(SRC_NAMES:%.cpp=build/debug/obj/%.o)
OBJS_RELEASE = $(SRC_NAMES:%.cpp=build/release/obj/%.o)

.PHONY: clean test debug release

first: debug

test: $(PROGRAM_TEST)
	./$(PROGRAM_TEST)

debug: $(PROGRAM_DEBUG) test

release: $(PROGRAM_RELEASE)

depend:
	$(CXX) -Isrc -MM -MG $(shell find src -name "*.cpp") | \
	sed -e 's/^.*\.o: \(.*\)\.cpp/\1.o: \1.cpp/' > makefile.depend

$(PROGRAM_TEST): $(OBJS_TEST)
	$(CXX) $(OBJS_TEST) $(LDFLAGS) $(shell gtest-config --ldflags --libs) -o $@

$(PROGRAM_DEBUG): $(OBJS_DEBUG)
	$(CXX) $(OBJS_DEBUG) $(LDFLAGS) -o $@

$(PROGRAM_RELEASE): $(OBJS_RELEASE)
	$(CXX) $(OBJS_RELEASE) $(LDFLAGS) -o $@

$(OBJS_TEST): build/test/obj/%.o: src/%.cpp
	@mkdir -p build/test/obj
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_TEST) -o $@ -c $<

$(OBJS_DEBUG): build/debug/obj/%.o: src/%.cpp
	@mkdir -p build/debug/obj
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_DEBUG) -o $@ -c $<

$(OBJS_RELEASE): build/release/obj/%.o: src/%.cpp
	@mkdir -p build/release/obj
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_RELEASE) -o $@ -c $<

clean:
	rm -rf build
	rm -f $(PROGRAM_TEST) $(PROGRAM_DEBUG) $(PROGRAM_RELEASE)
	rm -f makefile.depend
	find . -name "*~" | xargs rm -f

-include makefile.depend
