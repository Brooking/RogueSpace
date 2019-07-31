all: tests app

tests: \
		test/catch.hpp \
		test/main.cpp \
		test/floor_test.cpp \
		test/hero_test.cpp \
		test/ithing_mock.h \
		test/location_test.cpp \
		test/template_test.cpp \
		test/tile_test.cpp \
		inc/direction.h \
		inc/location.h \
		inc/uitokens.h \
		world/floor.cpp \
		world/floor.h \
		world/hero.cpp \
		world/hero.h \
		world/ithing.h \
		world/tile.cpp \
		world/tile.h
	g++ -ggdb3 -Wall -std=c++17 -o tests.out \
		-I$(CURDIR) \
		-I$(CURDIR)/inc \
		test/main.cpp \
		test/floor_test.cpp \
		test/hero_test.cpp \
		test/location_test.cpp \
		test/template_test.cpp \
		test/tile_test.cpp \
		world/floor.cpp \
		world/hero.cpp \
		world/tile.cpp

app:

clean:
	rm tests.out
