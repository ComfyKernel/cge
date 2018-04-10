FILES=$(shell find -name "*.cpp" -type f)
OBJS =$(patsubst %.cpp, %.o, $(FILES))
LIB  =libcge.so

all: $(OUT)/$(LIB)

$(OUT)/$(LIB): $(OBJS)
	$(CXX) $(CXXFLAGS) -fPIC -shared $(OBJS) -o $(OUT)/$(LIB)
	@echo -e "["$(LIB)"]" "\e[32mSUCCESS\e[0m"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -fPIC -c $< -o $@
