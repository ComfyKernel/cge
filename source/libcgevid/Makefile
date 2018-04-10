FILES=$(shell find -name "*.cpp" -type f)
OBJS =$(patsubst %.cpp, %.o, $(FILES))
LIB  =libcgevid.so

all: $(OUT)/$(LIB)

$(OUT)/$(LIB): $(OBJS)
	$(CXX) $(CXXFLAGS) -fPIC -shared -lSDL2 $(FILES) -o $(OUT)/$(LIB)
	@echo -e "["$(LIB)"]" "\e[32mSUCCESS\e[0m"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
