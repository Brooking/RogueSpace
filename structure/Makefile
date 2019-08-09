cc=g++
cflags=-ggdb3 -Wall -std=c++17 -fno-rtti

common_include_dirs=-I$(CURDIR)/inc -I$(CURDIR)/io
all_include_dirs=$(common_include_dirs) -I$(CURDIR)/ui -I$(CURDIR)/world
lib_dir=-L$(CURDIR)/lib

common_includes=inc/direction.h inc/location.h inc/uitokens.h inc/ifloor.h
io_includes= io/rawcurses.h io/io_constants.h io/screen.h io/window.h
world_includes=world/floor.h world/hero.h world/ithing.h world/rat.h world/tile.h world/wall.h world/monster_base.h
ui_includes=ui/icon.h ui/viewport.h

all: \
		game.out \
		worldtests.out

game.out: \
		lib/libworld.a \
		lib/libui.a \
		lib/libio.a \
		obj/main.o
	$(cc) $(cflags) \
		$(all_include_dirs) \
		$(lib_dir) \
		obj/main.o \
		-lworld \
		-lui \
		-lio \
		-lcurses \
		-o game.out

worldtests.out : \
		lib/libworld.a \
		test/catch.hpp \
		test/main.cpp \
		test/floor_test.cpp \
		test/hero_test.cpp \
		test/ithing_mock.h \
		test/location_test.cpp \
		test/template_test.cpp \
		test/tile_test.cpp \
		test/wall_test.cpp
	$(cc) $(cflags) \
		$(all_include_dirs) \
		$(lib_dir) \
		test/main.cpp \
		test/floor_test.cpp \
		test/hero_test.cpp \
		test/location_test.cpp \
		test/template_test.cpp \
		test/tile_test.cpp \
		test/wall_test.cpp \
		-lworld \
		-o worldtests.out

lib/libworld.a : \
		obj/floor.o \
		obj/hero.o \
		obj/tile.o
	ar crf lib/libworld.a \
		obj/floor.o \
		obj/hero.o \
		obj/tile.o

lib/libui.a : \
		obj/icon.o \
		obj/viewport.o
	ar crf lib/libui.a \
		obj/icon.o \
		obj/viewport.o

lib/libio.a : \
		obj/rawcurses.o \
		obj/screen.o \
		obj/window.o
	ar crf lib/libio.a \
		obj/rawcurses.o \
		obj/screen.o \
		obj/window.o

obj/floor.o : \
		$(common_includes) \
		$(world_includes) \
		world/floor.cpp
	$(cc) $(cflags) $(common_include_dirs) \
		-c world/floor.cpp \
		-o obj/floor.o

obj/hero.o : \
		$(common_includes) \
		$(world_includes) \
		world/hero.cpp
	$(cc) $(cflags) $(common_include_dirs) \
		-c world/hero.cpp \
		-o obj/hero.o

obj/tile.o : \
		$(common_includes) \
		$(world_includes) \
		world/tile.cpp
	$(cc) $(cflags) $(common_include_dirs) \
		-c world/tile.cpp \
		-o obj/tile.o

obj/icon.o : \
		$(common_includes) \
		$(ui_includes) \
		ui/icon.cpp
	$(cc) $(cflags) $(common_include_dirs) \
		-c ui/icon.cpp \
		-o obj/icon.o

obj/viewport.o : \
		$(common_includes) \
		$(ui_includes) \
		ui/viewport.cpp
	$(cc) $(cflags) $(common_include_dirs) \
		-c ui/viewport.cpp \
		-o obj/viewport.o

obj/main.o : \
		$(common_includes) \
		$(ui_includes) \
		$(world_includes) \
		game/main.cpp
	$(cc) $(cflags) $(all_include_dirs) \
		-c game/main.cpp \
		-o obj/main.o

obj/rawcurses.o : \
		$(io_includes) \
		io/rawcurses.cpp
	$(cc) $(cflags) $(all_include_dirs) \
		-c io/rawcurses.cpp \
		-o obj/rawcurses.o

obj/screen.o : \
		$(io_includes) \
		io/screen.cpp
	$(cc) $(cflags) $(common_include_dirs) \
		-c io/screen.cpp \
		-o obj/screen.o
	
obj/window.o : \
		$(io_includes) \
		io/window.cpp
	$(cc) $(cflags) $(common_include_dirs) \
		-c io/window.cpp \
		-o obj/window.o

clean:
	rm -f *.out
	rm -f lib/*.a
	rm -f obj/*.o
