all: \
		game.out \
		commontests.out \
		iotests.out \
		vistests.out \
		worldtests.out

clean:
	rm -f *.out
	rm -f lib/*.a
	rm -f obj/*.o

# not including these warnings
#  -Waggregate return because I like treating Locations as a value type
#  -Wmissing   braces misidentifies 2 sets of missing braces
#  -Wpadded    haven't grocked this stuff yet
#  -ansi       messes up enum::value formatting 
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
	-Wunsafe-loop-optimizations \
	-Wunused-function \
	-Wunused-label \
	-Wunused-parameter \
	-Wunused-value \
	-Wunused-variable \
	-Wunused \
	-Wvariadic-macros \
	-Wvolatile-register-var \
	-Wwrite-strings

c++compile=g++
c++standard=-std=c++11
c++debug=-ggdb3 -O0
#c++debug=-O3 for production
c++profiling=-g -pg -fprofile-arcs -ftest-coverage
c++command=$(c++compile) $(c++standard) $(c++debug) $(c++warnings)

# directories (for compiling and linking)
common_include_dirs=\
	-I$(CURDIR)/inc
ui_include_dirs=\
	-I$(CURDIR)/inc \
	-I$(CURDIR)/ui \
	-I$(CURDIR)/ui/io
world_include_dirs=\
	-I$(CURDIR)/inc \
	-I$(CURDIR)/world \
	-I$(CURDIR)/world/visibility
all_include_dirs=\
	-I$(CURDIR)/inc \
	-I$(CURDIR)/ui \
	-I$(CURDIR)/ui/io \
	-I$(CURDIR)/world \
	-I$(CURDIR)/world/visibility
lib_dir=-L$(CURDIR)/lib

# header file lists (for setting dependencies)
common_includes= \
	Makefile \
	inc/content_size.h \
	inc/direction.h \
	inc/ifloor.h \
	inc/io_constants.h \
	inc/iscreen.h \
	inc/iwindow.h \
	inc/iupdate.h \
	inc/location.h \
	inc/uitokens.h
io_includes= \
	ui/io/rawcurses.h \
	ui/io/screen.h \
	ui/io/window.h
world_includes= \
	world/bee.h \
	world/dog.h \
	world/floor.h \
	world/hero.h \
	world/ithing.h \
	world/map_for_casting.h \
	world/monster_base.h \
	world/rat.h \
	world/thing_base.h \
	world/tile.h \
	world/wall.h
ui_includes=\
	ui/blank_pane.h \
	ui/icon.h \
	ui/ipane.h \
	ui/mosaic.h \
	ui/rect.h \
	ui/viewport.h \
	ui/statuspane.h 
vis_includes= \
	world/visibility/imap.h \
	world/visibility/los.h \
	world/visibility/original_shadow_cast.h \
	world/visibility/pathfinder.h \
	world/visibility/dijkstra.h

# executables
game.out: \
		lib/libworld.a \
		lib/libui.a \
		lib/libio.a \
		lib/libvisibility.a \
		obj/main.o \
		obj/generator.o
	$(c++command) \
		$(all_include_dirs) \
		$(lib_dir) \
		obj/main.o \
		obj/generator.o \
		-lcommon \
		-lworld \
		-lui \
		-lio \
		-lvisibility \
		-lcurses \
		-o game.out

vistests.out : \
		lib/libvisibility.a \
		test/catch.hpp \
		test/main.cpp \
		test/imap_mock.h \
		test/original_shadow_cast_test.cpp \
		test/los_test.cpp \
		test/pathfinder_test.cpp \
		test/dijkstra_test.cpp
	$(c++command) \
		$(all_include_dirs) \
		$(lib_dir) \
		-DPROTECTED_ACCESS=public \
		test/main.cpp \
		test/original_shadow_cast_test.cpp \
		test/los_test.cpp \
		test/pathfinder_test.cpp \
		test/dijkstra_test.cpp \
		-lcommon \
		-lvisibility \
		-o vistests.out

worldtests.out : \
		lib/libworld.a \
		lib/libvisibility.a \
		test/catch.hpp \
		test/ithing_mock.h \
		test/main.cpp \
		test/content_size_test.cpp \
		test/floor_test.cpp \
		test/hero_test.cpp \
		test/ithing_mock.h \
		test/location_test.cpp \
		test/template_test.cpp \
		test/tile_test.cpp \
		test/wall_test.cpp
	$(c++command) \
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
		-lcommon \
		-lworld \
		-lvisibility \
		-o worldtests.out

iotests.out : \
		lib/libio.a \
		test/catch.hpp \
		test/icurses_mock.h \
		test/main.cpp \
		test/screen_test.cpp
	$(c++command) \
		$(all_include_dirs) \
		$(lib_dir) \
		-DPROTECTED_ACCESS=public \
		test/main.cpp \
		test/screen_test.cpp \
		-lcommon \
		-lio \
		-o iotests.out

# Libraries
lib/libcommon.a : \
		obj/location.o
	ar crf lib/libcommon.a \
		obj/location.o

lib/libio.a : \
		obj/rawcurses.o \
		obj/screen.o \
		obj/window.o
	ar crf lib/libio.a \
		obj/rawcurses.o \
		obj/screen.o \
		obj/window.o

lib/libui.a : \
		obj/blank_pane.o \
		obj/icon.o \
		obj/mosaic.o \
		obj/rect.o \
		obj/statuspane.o \
		obj/viewport.o
	ar crf lib/libui.a \
		obj/blank_pane.o \
		obj/icon.o \
		obj/mosaic.o \
		obj/rect.o \
		obj/statuspane.o \
		obj/viewport.o

lib/libvisibility.a : \
		obj/original_shadow_cast.o \
		obj/los.o \
		obj/pathfinder.o \
		obj/dijkstra.o
	ar crf lib/libvisibility.a \
		obj/original_shadow_cast.o \
		obj/los.o \
		obj/pathfinder.o \
		obj/dijkstra.o

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

# common objects
obj/location.o : \
		$(common_includes) \
		common/location.cpp
	$(c++command) $(common_include_dirs) \
		-c common/location.cpp \
		-o obj/location.o

# world objects
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

obj/map_for_casting.o : \
		$(common_includes) \
		$(vis_includes) \
		$(world_includes) \
		world/map_for_casting.cpp
	$(c++command) $(world_include_dirs) \
		-c world/map_for_casting.cpp \
		-o obj/map_for_casting.o

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

# game objects
obj/main.o : \
		$(common_includes) \
		$(ui_includes) \
		$(world_includes) \
		game/generator.h \
		game/main.cpp
	$(c++command) $(all_include_dirs) \
		-c game/main.cpp \
		-o obj/main.o

obj/generator.o : \
		$(common_includes) \
		$(ui_includes) \
		$(world_includes) \
		game/generator.h \
		game/generator.cpp
	$(c++command) $(all_include_dirs) \
		-c game/generator.cpp \
		-o obj/generator.o

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
obj/los.o : \
		$(common_includes) \
		$(world_includes) \
		world/visibility/los.cpp
	$(c++command) $(world_include_dirs) \
		-c world/visibility/los.cpp \
		-o obj/los.o

obj/original_shadow_cast.o : \
		$(common_includes) \
		$(vis_includes) \
		world/visibility/original_shadow_cast.cpp
	$(c++command) $(common_include_dirs) \
		-c world/visibility/original_shadow_cast.cpp \
		-o obj/original_shadow_cast.o

obj/pathfinder.o : \
		$(common_includes) \
		$(vis_includes) \
		world/visibility/pathfinder.cpp
	$(c++command) $(common_include_dirs) \
		-c world/visibility/pathfinder.cpp \
		-o obj/pathfinder.o

obj/dijkstra.o : \
		$(common_includes) \
		$(vis_includes) \
		world/visibility/dijkstra.cpp
	$(c++command) $(common_include_dirs) \
		-c world/visibility/dijkstra.cpp \
		-o obj/dijkstra.o
