FILES=$(shell find -name "*.cpp" -type f)
OBJS =$(patsubst %.cpp, %.o, $(FILES))
BIN  =cgetester

all: $(OUT)/$(BIN)

$(OUT)/$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -L$(OUT) -lcge -lcgevid -o $(OUT)/$(BIN)
	@echo -e "["$(BIN)"]" "\e[32mSUCCESS\e[0m"

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@
