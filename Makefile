CXX = g++

CXXFLAGS = -Isrc -mno-cygwin -mwindows
CXXFLAGS += -DUNICODE -D_UNICODE
CXXFLAGS += -W -Wall -Wpointer-arith -fno-exceptions
CXXFLAGS += -DWINVER=\(0x0500\) -D_WIN32_WINNT=\(0x0500\) -D_WIN32_IE=\(0x600\)
CXXFLAGS_TEST    = -D__TEST $(shell gtest-config --cppflags --cxxflags) -mconsole
CXXFLAGS_DEBUG   = -D__DEBUG -fno-rtti
CXXFLAGS_RELEASE = -D__RELEASE -DNDEBUG -fno-rtti -finline-functions -O3

LDFLAGS = -W -Wall -fno-exceptions
LDFLAGS = -mno-cygwin -mwindows -lcomctl32
LDFLAGS_TEST    = $(shell gtest-config --ldflags --libs) -mconsole
LDFLAGS_DEBUG   = -fno-rtti
LDFLAGS_RELEASE = -fno-rtti -finline-functions -O3

PROGRAM_NAME = Shrimp

PROGRAM_TEST    = build/test/$(PROGRAM_NAME)Test.exe
PROGRAM_DEBUG   = build/debug/$(PROGRAM_NAME).exe
PROGRAM_RELEASE = build/release/$(PROGRAM_NAME).exe

SRC_NAMES = $(shell find src -name "*.cpp" | sed -e 's/^src\///')

OBJS_TEST    = $(SRC_NAMES:%.cpp=build/test/obj/%.o)
OBJS_DEBUG   = $(SRC_NAMES:%.cpp=build/debug/obj/%.o)
OBJS_RELEASE = $(SRC_NAMES:%.cpp=build/release/obj/%.o)

.PHONY: test debug release depend clean

first: test

test: $(PROGRAM_TEST)
	./$(PROGRAM_TEST)

debug: $(PROGRAM_DEBUG)
	./$(PROGRAM_DEBUG)

release: $(PROGRAM_RELEASE)

depend:
	$(CXX) -Isrc -MM -MG $(shell find src -name "*.cpp") | \
	sed -e 's/^.*\.o: src\/\(.*\)\.cpp/build\/test\/obj\/\1.o build\/debug\/obj\/\1.o build\/release\/obj\/\1.o: src\/\1.cpp/' > makefile.depend

$(PROGRAM_TEST): $(OBJS_TEST)
	$(CXX) $(OBJS_TEST) $(LDFLAGS) $(LDFLAGS_TEST) -o $@

$(PROGRAM_DEBUG): $(OBJS_DEBUG)
	$(CXX) $(OBJS_DEBUG) $(LDFLAGS) $(LDFLAGS_DEBUG) -o $@

$(PROGRAM_RELEASE): $(OBJS_RELEASE)
	$(CXX) $(OBJS_RELEASE) $(LDFLAGS) $(LDFLAGS_RELEASE) -o $@

$(OBJS_TEST): build/test/obj/%.o: src/%.cpp
	@mkdir -p `obj=$@; echo $${obj%/*}`
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_TEST) -o $@ -c $<

$(OBJS_DEBUG): build/debug/obj/%.o: src/%.cpp
	@mkdir -p `obj=$@; echo $${obj%/*}`
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_DEBUG) -o $@ -c $<

$(OBJS_RELEASE): build/release/obj/%.o: src/%.cpp
	@mkdir -p `obj=$@; echo $${obj%/*}`
	$(CXX) $(CXXFLAGS) $(CXXFLAGS_RELEASE) -o $@ -c $<

clean:
	rm -rf build
	rm -f makefile.depend
	find . -name "*~" | xargs rm -f

-include makefile.depend
