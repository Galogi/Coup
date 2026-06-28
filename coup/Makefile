TARGET = coup.exe
TEST_LOGIC_TARGET = test_logic.exe
TEST_PLAYERS_TARGET = test_players.exe

CXX = g++
SANITIZE ?=
CPPFLAGS = -I. -I./Players -I./cards -I./Logic -I./Gui
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -g $(SANITIZE) $(shell pkg-config --cflags sfml-all 2>/dev/null)

LIBS = $(shell pkg-config --libs sfml-all 2>/dev/null)
ifeq ($(strip $(LIBS)),)
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
endif

SRCS = main.cpp \
       Gui/GUI.cpp \
       Gui/SelectPlayersGUI.cpp \
       Gui/GameScreenGUI.cpp \
       Gui/gameScreen.cpp \
       Players/Player.cpp \
       Players/PlayerFactory.cpp \
       cards/Card.cpp \
       Logic/GameLogic.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

test_logic:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I./Test \
	Test/GameLogic_Test.cpp Logic/GameLogic.cpp Players/*.cpp cards/Card.cpp \
	-o $(TEST_LOGIC_TARGET) $(LIBS)
	./$(TEST_LOGIC_TARGET)

test_players:
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -I./Test \
	Test/Test_Players.cpp Players/*.cpp cards/*.cpp Logic/GameLogic.cpp \
	-o $(TEST_PLAYERS_TARGET) $(LIBS)
	./$(TEST_PLAYERS_TARGET)

test: test_logic test_players

clean:
	rm -f $(OBJS) $(TARGET) $(TEST_LOGIC_TARGET) $(TEST_PLAYERS_TARGET) test_runner.exe

rebuild: clean all

.PHONY: all clean rebuild test test_logic test_players
