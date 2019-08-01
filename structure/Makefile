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
		ui/realcurses.cpp \
		ui/realcurses.h \
		ui/screen.h \
		ui/screen.cpp \
		world/floor.cpp \
		world/floor.h \
		world/hero.cpp \
		world/hero.h \
		world/ithing.h \
		world/tile.cpp \
		world/tile.h
	g++ -ggdb3 -Wall -std=c++17 -fno-rtti \
		-I$(CURDIR) \
		-I$(CURDIR)/inc \
		test/main.cpp \
		test/floor_test.cpp \
		test/hero_test.cpp \
		test/location_test.cpp \
		test/template_test.cpp \
		test/tile_test.cpp \
		ui/realcurses.cpp \
		ui/screen.cpp \
		world/floor.cpp \
		world/hero.cpp \
		world/tile.cpp \
		-lncurses \
		-o tests.out

app:

clean:
	rm -f tests.out
