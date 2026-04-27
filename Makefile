CXX = g++
CXXFLAGS = -std=c++11 -Wall -g
TARGET = game
SRCDIR = .
OBJDIR = obj

SOURCES = main.cpp game.cpp player.cpp enemy.cpp card.cpp combat.cpp map.cpp event.cpp relic.cpp save.cpp flavor.cpp ascii_art.cpp utils.cpp global_pool.cpp

OBJECTS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	rm -rf $(OBJDIR) $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
