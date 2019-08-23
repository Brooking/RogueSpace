all: \
		game.out \
		mini.out \
		worldtests.out \
		vistests.out

clean:
	rm -f *.out
	rm -f lib/*.a
	rm -f obj/*.o

# definitions	
cc=g++
cflags=-ggdb3 -Wall -std=c++17 
#-fno-rtti <- we are now using dynamic_casts

# directories (for compiling and linking)
common_include_dirs=-I$(CURDIR)/inc -I$(CURDIR)/io
all_include_dirs=$(common_include_dirs) -I$(CURDIR)/ui -I$(CURDIR)/world -I$(CURDIR)/visibility
lib_dir=-L$(CURDIR)/lib

# header file lists (for setting dependencies)
common_includes= \
	inc/content_size.h \
	inc/direction.h \
	inc/ifloor.h \
	inc/iupdate.h \
	inc/uitokens.h
io_includes= \
	io/io_constants.h \
	io/rawcurses.h \
	io/screen.h \
	io/window.h
world_includes= \
	world/bee.h \
	world/dog.h \
	world/floor.h \
	world/hero.h \
	world/ithing.h \
	world/location.h \
	world/map_for_casting.h \
	world/monster_base.h \
	world/rat.h \
	world/thing_base.h \
	world/tile.h \
	world/wall.h
ui_includes=ui/icon.h ui/viewport.h
vis_includes= \
	visibility/imap.h \
	visibility/los.h \
	visibility/original_shadow_cast.h \
	visibility/pathfinder.h

# executables
game.out: \
		lib/libworld.a \
		lib/libui.a \
		lib/libio.a \
		lib/libvisibility.a \
		obj/main.o
	$(cc) $(cflags) \
		$(all_include_dirs) \
		$(lib_dir) \
		obj/main.o \
		-lworld \
		-lui \
		-lio \
		-lvisibility \
		-lcurses \
		-o game.out

mini.out: \
		lib/libworld.a \
		lib/libui.a \
		lib/libio.a \
		lib/libvisibility.a \
		obj/mini.o
	$(cc) $(cflags) \
		$(all_include_dirs) \
		$(lib_dir) \
		obj/mini.o \
		-lworld \
		-lui \
		-lio \
		-lvisibility \
		-lcurses \
		-o mini.out

vistests.out : \
		lib/libvisibility.a \
		test/catch.hpp \
		test/main.cpp \
		test/original_shadow_cast_test.cpp \
		test/los_test.cpp \
		test/pathfinder_test.cpp
	$(cc) $(cflags) \
		$(all_include_dirs) \
		$(lib_dir) \
		-DPROTECTED_ACCESS=public \
		test/main.cpp \
		test/original_shadow_cast_test.cpp \
		test/los_test.cpp \
		test/pathfinder_test.cpp \
		-lvisibility \
		-lworld \
		-o vistests.out

worldtests.out : \
		lib/libworld.a \
		lib/libvisibility.a \
		test/catch.hpp \
		test/main.cpp \
		test/content_size_test.cpp \
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
		-DPROTECTED_ACCESS=public \
		test/main.cpp \
		test/content_size_test.cpp \
		test/floor_test.cpp \
		test/hero_test.cpp \
		test/location_test.cpp \
		test/template_test.cpp \
		test/tile_test.cpp \
		test/wall_test.cpp \
		-lworld \
		-lvisibility \
		-o worldtests.out

# Libraries
lib/libio.a : \
		obj/rawcurses.o \
		obj/screen.o \
		obj/window.o
	ar crf lib/libio.a \
		obj/rawcurses.o \
		obj/screen.o \
		obj/window.o

lib/libui.a : \
		obj/icon.o \
		obj/viewport.o
	ar crf lib/libui.a \
		obj/icon.o \
		obj/viewport.o

lib/libvisibility.a : \
		obj/original_shadow_cast.o \
		obj/los.o \
		obj/pathfinder.o
	ar crf lib/libvisibility.a \
		obj/original_shadow_cast.o \
		obj/los.o \
		obj/pathfinder.o

lib/libworld.a : \
		obj/map_for_casting.o \
		obj/floor.o \
		obj/location.o \
		obj/hero.o \
		obj/tile.o
	ar crf lib/libworld.a \
		obj/map_for_casting.o \
		obj/floor.o \
		obj/location.o \
		obj/hero.o \
		obj/tile.o

# world objects
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

obj/location.o : \
		$(common_includes) \
		$(world_includes) \
		world/location.cpp
	$(cc) $(cflags) $(common_include_dirs) \
		-c world/location.cpp \
		-o obj/location.o

obj/map_for_casting.o : \
		$(common_includes) \
		$(vis_includes) \
		$(world_includes) \
		world/map_for_casting.cpp
	$(cc) $(cflags) $(all_include_dirs) \
		-c world/map_for_casting.cpp \
		-o obj/map_for_casting.o

obj/tile.o : \
		$(common_includes) \
		$(world_includes) \
		world/tile.cpp
	$(cc) $(cflags) $(common_include_dirs) \
		-c world/tile.cpp \
		-o obj/tile.o

# UI objects
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

# game objects
obj/main.o : \
		$(common_includes) \
		$(ui_includes) \
		$(world_includes) \
		game/main.cpp
	$(cc) $(cflags) $(all_include_dirs) \
		-c game/main.cpp \
		-o obj/main.o

obj/mini.o : \
		$(common_includes) \
		$(ui_includes) \
		$(world_includes) \
		game/mini.cpp
	$(cc) $(cflags) $(all_include_dirs) \
		-c game/mini.cpp \
		-o obj/mini.o

# io objects
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

# visibility objects
obj/los.o : \
		$(common_includes) \
		$(vis_includes) \
		visibility/los.cpp
	$(cc) $(cflags) $(all_include_dirs) \
		-c visibility/los.cpp \
		-o obj/los.o

obj/original_shadow_cast.o : \
		$(common_includes) \
		$(vis_includes) \
		visibility/original_shadow_cast.cpp
	$(cc) $(cflags) $(common_include_dirs) \
		-c visibility/original_shadow_cast.cpp \
		-o obj/original_shadow_cast.o

obj/pathfinder.o : \
		$(common_includes) \
		$(vis_includes) \
		visibility/pathfinder.cpp
	$(cc) $(cflags) $(all_include_dirs) \
		-c visibility/pathfinder.cpp \
		-o obj/pathfinder.o
