all: \
	roguespace.out \
	tests.out

clean:
	rm -f *.out
	rm -f lib/*.a
	rm -f obj/*.o

c++warnings= \
	-pedantic \
	-pedantic-errors \
	-Wall \
	-Wcast-align \
	-Wcast-qual \
	-Wchar-subscripts \
	-Wcomment\
	-Wconversion  \
	-Wdisabled-optimization \
	-Weffc++ \
	-Werror \
	-Wextra \
	-Wfloat-equal \
	-Wformat \
	-Wformat=2 \
	-Wformat-nonliteral \
	-Wformat-security \
	-Wformat-y2k \
	-Wimport \
	-Winline \
	-Winit-self \
	-Winvalid-pch \
	-Wlong-long \
	-Wmissing-field-initializers \
	-Wmissing-format-attribute \
	-Wmissing-include-dirs \
	-Wmissing-noreturn \
	-Wno-long-long \
	-Wpacked \
	-Wparentheses \
	-Wpointer-arith \
	-Wredundant-decls \
	-Wreturn-type \
	-Wsequence-point \
	-Wshadow \
	-Wsign-compare \
	-Wstack-protector \
	-Wstrict-aliasing \
	-Wstrict-aliasing=2 \
	-Wswitch \
	-Wswitch-default \
	-Wswitch-enum \
	-Wtrigraphs \
	-Wuninitialized \
	-Wunknown-pragmas \
	-Wunreachable-code \
	-Wunused-function \
	-Wunused-label \
	-Wunused-parameter \
	-Wunused-value \
	-Wunused-variable \
	-Wunused \
	-Wvariadic-macros \
	-Wvolatile-register-var \
	-Wwrite-strings
# not including these warnings
#	-Waggregate-return	because I like treating Locations as a value type
#	-Wmissing			braces misidentifies 2 sets of missing braces
#	-Wpadded			no need to pad out my structures
#	-ansi				replacement for -std=c++11, messes up enum::value formatting
#	-Wunsafe-loop-optimizations	(won't build on osx)

c++compile=g++
c++standard=-std=c++11
c++debug=-ggdb3 -O0
#c++debug=-O3 for production
c++profiling=-g -pg -fprofile-arcs -ftest-coverage
c++command=$(c++compile) $(c++standard) $(c++debug) $(c++warnings)

# directories (for compiling and linking)
common_include_dirs=\
	-I$(CURDIR)/interfaces
ui_include_dirs=\
	-I$(CURDIR)/interfaces \
	-I$(CURDIR)/ui \
	-I$(CURDIR)/ui/io
world_include_dirs=\
	-I$(CURDIR)/interfaces \
	-I$(CURDIR)/world \
	-I$(CURDIR)/world/visibility
all_include_dirs=\
	-I$(CURDIR)/interfaces \
	-I$(CURDIR)/ui \
	-I$(CURDIR)/ui/io \
	-I$(CURDIR)/world \
	-I$(CURDIR)/world/visibility

# header file lists (for setting dependencies)
common_includes= \
	Makefile \
	interfaces/content_size.h \
	interfaces/direction.h \
	interfaces/iactor.h \
	interfaces/ifloor.h \
	interfaces/io_constants.h \
	interfaces/iscreen.h \
	interfaces/ithing.h \
	interfaces/iupdate.h \
	interfaces/iwindow.h \
	interfaces/location.h \
	interfaces/uitoken.h
game_includes =\
	game/game_type.h \
	game/game.h \
	game/generator.h \
	game/time_entry.h \
	game/timeline.h
world_includes= \
	world/actor_base.h \
	world/bee.h \
	world/dog.h \
	world/floor.h \
	world/hero.h \
	world/iwall_map.h \
	world/rat.h \
	world/thing_base.h \
	world/tile.h \
	world/wall.h \
	world/visibility/los.h \
	world/visibility/fov.h \
	world/visibility/pathfinder.h \
	world/visibility/dijkstra.h
ui_includes=\
	ui/blank_pane.h \
	ui/icon.h \
	ui/ipane.h \
	ui/mosaic.h \
	ui/rect.h \
	ui/viewport.h \
	ui/statuspane.h \
	ui/io/rawcurses.h \
	ui/io/screen.h \
	ui/io/window.h

# library lists
library_files = \
	lib/libgame.a \
	lib/libworld.a \
	lib/libui.a \
	lib/libinterfaces.a
library_dir=-L$(CURDIR)/lib
library_specs = \
	-lgame \
	-lworld \
	-lui \
	-linterfaces

# test lists
tests= \
	game/timeline_test.cpp \
	game/time_entry_test.cpp \
	interfaces/content_size_test.cpp \
	interfaces/location_test.cpp \
	interfaces/uitoken_test.cpp \
	ui/icon_test.cpp \
	ui/screen_test.cpp \
	world/floor_test.cpp \
	world/hero_test.cpp \
	world/tile_test.cpp \
	world/wall_test.cpp \
	world/visibility/dijkstra_test.cpp \
	world/visibility/los_test.cpp \
	world/visibility/fov_test.cpp \
	world/visibility/pathfinder_test.cpp
test_mocks = \
	interfaces/iactor_mock.h \
	interfaces/icurses_mock.h \
	interfaces/ithing_mock.h \
	world/iwall_map_mock.h

# executables
roguespace.out: \
		$(library_files) \
		obj/main.o
	$(c++command) \
		$(all_include_dirs) \
		$(library_dir) \
		obj/main.o \
		$(library_specs) \
		-lcurses \
		-o roguespace.out

tests.out : \
		$(library_files) \
		$(tests) \
		$(test_mocks) \
		interfaces/catch.hpp \
		interfaces/test_main.cpp
	$(c++command) \
		$(all_include_dirs) \
		$(library_dir) \
		-DPROTECTED_ACCESS=public \
		interfaces/test_main.cpp \
		$(tests) \
		$(library_specs) \
		-o tests.out

# Libraries
lib/libinterfaces.a : \
		obj/location.o \
		obj/uitoken.o
	ar crf lib/libinterfaces.a \
		obj/location.o \
		obj/uitoken.o

lib/libgame.a : \
		obj/game.o \
		obj/generator.o \
		obj/timeline.o
	ar crf lib/libgame.a \
		obj/game.o \
		obj/generator.o \
		obj/timeline.o

lib/libui.a : \
		obj/blank_pane.o \
		obj/icon.o \
		obj/mosaic.o \
		obj/rawcurses.o \
		obj/rect.o \
		obj/screen.o \
		obj/statuspane.o \
		obj/viewport.o \
		obj/window.o
	ar crf lib/libui.a \
		obj/blank_pane.o \
		obj/icon.o \
		obj/mosaic.o \
		obj/rawcurses.o \
		obj/rect.o \
		obj/screen.o \
		obj/statuspane.o \
		obj/viewport.o \
		obj/window.o

lib/libworld.a : \
		obj/actor_base.o \
		obj/dijkstra.o \
		obj/floor.o \
		obj/location.o \
		obj/los.o \
		obj/hero.o \
		obj/fov.o \
		obj/pathfinder.o \
		obj/thing_base.o \
		obj/tile.o
	ar crf lib/libworld.a \
		obj/actor_base.o \
		obj/dijkstra.o \
		obj/floor.o \
		obj/location.o \
		obj/los.o \
		obj/hero.o \
		obj/fov.o \
		obj/pathfinder.o \
		obj/thing_base.o \
		obj/tile.o

# interfaces objects
obj/location.o : \
		$(common_includes) \
		interfaces/location.cpp
	$(c++command) $(common_include_dirs) \
		-c interfaces/location.cpp \
		-o obj/location.o

obj/uitoken.o : \
		$(common_includes) \
		interfaces/uitoken.cpp
	$(c++command) $(common_include_dirs) \
		-c interfaces/uitoken.cpp \
		-o obj/uitoken.o

# game objects
obj/game.o : \
		$(common_includes) \
		$(game_includes) \
		$(ui_includes) \
		$(world_includes) \
		game/game.cpp
	$(c++command) $(all_include_dirs) \
		-c game/game.cpp \
		-o obj/game.o

obj/generator.o : \
		$(common_includes) \
		$(game_includes) \
		$(world_includes) \
		game/generator.cpp
	$(c++command) $(all_include_dirs) \
		-c game/generator.cpp \
		-o obj/generator.o

obj/main.o : \
		$(common_includes) \
		$(game_includes) \
		game/main.cpp
	$(c++command) $(all_include_dirs) \
		-c game/main.cpp \
		-o obj/main.o

obj/timeline.o : \
		$(common_includes) \
		$(game_includes) \
		game/timeline.cpp
	$(c++command) $(all_include_dirs) \
		-c game/timeline.cpp \
		-o obj/timeline.o

# world objects
obj/actor_base.o : \
		$(common_includes) \
		$(world_includes) \
		world/actor_base.cpp
	$(c++command) $(world_include_dirs) \
		-c world/actor_base.cpp \
		-o obj/actor_base.o

obj/floor.o : \
		$(common_includes) \
		$(world_includes) \
		world/floor.cpp
	$(c++command) $(world_include_dirs) \
		-c world/floor.cpp \
		-o obj/floor.o

obj/hero.o : \
		$(common_includes) \
		$(world_includes) \
		world/hero.cpp
	$(c++command) $(world_include_dirs) \
		-c world/hero.cpp \
		-o obj/hero.o

obj/thing_base.o : \
		$(common_includes) \
		$(world_includes) \
		world/thing_base.cpp
	$(c++command) $(world_include_dirs) \
		-c world/thing_base.cpp \
		-o obj/thing_base.o

obj/tile.o : \
		$(common_includes) \
		$(world_includes) \
		world/tile.cpp
	$(c++command) $(world_include_dirs) \
		-c world/tile.cpp \
		-o obj/tile.o

# UI objects
obj/blank_pane.o : \
		$(common_includes) \
		$(ui_includes) \
		ui/blank_pane.cpp
	$(c++command) $(ui_include_dirs) \
		-c ui/blank_pane.cpp \
		-o obj/blank_pane.o

obj/icon.o : \
		$(common_includes) \
		$(ui_includes) \
		ui/icon.cpp
	$(c++command) $(ui_include_dirs) \
		-c ui/icon.cpp \
		-o obj/icon.o

obj/mosaic.o : \
		$(common_includes) \
		$(ui_includes) \
		ui/mosaic.cpp
	$(c++command) $(ui_include_dirs) \
		-c ui/mosaic.cpp \
		-o obj/mosaic.o

obj/rect.o : \
		$(common_includes) \
		$(ui_includes) \
		ui/rect.cpp
	$(c++command) $(ui_include_dirs) \
		-c ui/rect.cpp \
		-o obj/rect.o

obj/statuspane.o : \
		$(common_includes) \
		$(ui_includes) \
		ui/statuspane.cpp
	$(c++command) $(ui_include_dirs) \
		-c ui/statuspane.cpp \
		-o obj/statuspane.o

obj/viewport.o : \
		$(common_includes) \
		$(ui_includes) \
		ui/viewport.cpp
	$(c++command) $(ui_include_dirs) \
		-c ui/viewport.cpp \
		-o obj/viewport.o

# io objects
obj/rawcurses.o : \
		$(common_includes) \
		$(io_includes) \
		ui/io/rawcurses.cpp
	$(c++command) $(common_include_dirs) \
		-c ui/io/rawcurses.cpp \
		-o obj/rawcurses.o

obj/screen.o : \
		$(common_includes) \
		$(io_includes) \
		ui/io/screen.cpp
	$(c++command) $(common_include_dirs) \
		-c ui/io/screen.cpp \
		-o obj/screen.o
	
obj/window.o : \
		$(common_includes) \
		$(io_includes) \
		ui/io/window.cpp
	$(c++command) $(common_include_dirs) \
		-c ui/io/window.cpp \
		-o obj/window.o

# visibility objects
obj/dijkstra.o : \
		$(common_includes) \
		$(vis_includes) \
		world/visibility/dijkstra.cpp
	$(c++command) $(common_include_dirs) \
		-c world/visibility/dijkstra.cpp \
		-o obj/dijkstra.o

obj/los.o : \
		$(common_includes) \
		$(world_includes) \
		world/visibility/los.cpp
	$(c++command) $(world_include_dirs) \
		-c world/visibility/los.cpp \
		-o obj/los.o

obj/fov.o : \
		$(common_includes) \
		$(vis_includes) \
		world/visibility/fov.cpp
	$(c++command) $(common_include_dirs) \
		-c world/visibility/fov.cpp \
		-o obj/fov.o

obj/pathfinder.o : \
		$(common_includes) \
		$(vis_includes) \
		world/visibility/pathfinder.cpp
	$(c++command) $(common_include_dirs) \
		-c world/visibility/pathfinder.cpp \
		-o obj/pathfinder.o
