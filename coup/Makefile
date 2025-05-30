
TARGET = coup


CXX = g++
CXXFLAGS = -std=c++17 -fsanitize=address -g


LIBS = -lsfml-graphics -lsfml-window -lsfml-system


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


test_logic:
	$(CXX) $(CXXFLAGS) -I. -I./Test -I./Players -I./cards -I./Logic \
	Test/GameLogic_Test.cpp Logic/GameLogic.cpp Players/*.cpp cards/Card.cpp \
	-o test_runner $(LIBS)
	./test_runner


test_players:
	$(CXX) $(CXXFLAGS) -I./Test -I./Players -I./cards -I. \
	Test/Test_Players.cpp Players/*.cpp cards/*.cpp Logic/GameLogic.cpp \
	-o test_runner $(LIBS)
	./test_runner

clean:
	rm -f $(OBJS) $(TARGET) test_runner

rebuild: clean all
