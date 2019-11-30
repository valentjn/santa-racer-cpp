CC = g++
OBJECTS = santa.o setup.o game.o level.o sleigh.o landscape.o \
          level_object.o cloud.o balloon.o angel.o goblin.o goblin_snowball.o \
          snowman.o finish.o \
          gift.o snowflake.o output.o text.o random.o args.o draw.o mask.o \
          sleigh_star.o snowman_star.o config.o score.o sound.o chimney.o
LIBS = `sdl-config --libs` -lSDL_image -lSDL_mixer -lm
CFLAGS = -c --std=c++03 `sdl-config --cflags` -Wall -Wextra -Wno-sign-compare

all: santa

santa.o: src/args.hpp src/setup.hpp
setup.o: src/config.hpp src/random.hpp src/sound.hpp
game.o: src/draw.hpp src/sound.hpp src/random.hpp
level.o: src/draw.hpp
sleigh.o: src/draw.hpp src/random.hpp
landscape.o: src/draw.hpp
gift.o: src/draw.hpp
snowflake.o: src/random.hpp
star.o: src/draw.hpp src/random.hpp

%.o: src/%.cpp src/%.hpp src/globals.hpp src/game.hpp src/text.hpp \
     src/output.hpp src/landscape.hpp src/snowflake.hpp src/sleigh.hpp \
     src/level.hpp src/level_object.hpp src/cloud.hpp src/balloon.hpp \
     src/angel.hpp src/goblin.hpp src/goblin_snowball.hpp src/snowman.hpp \
     src/gift.hpp src/mask.hpp src/score.hpp src/chimney.hpp \
     src/sleigh_star.hpp src/snowman_star.hpp src/finish.hpp
	$(CC) $(CFLAGS) $< -o $@

santa: $(OBJECTS)
	$(CC) $(LIBS) $(OBJECTS) -o santa

clean:
	rm $(OBJECTS) santa 2> /dev/null
