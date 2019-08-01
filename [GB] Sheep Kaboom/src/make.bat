REM graphics
lcc -Wf-bo1 -c dev/data/tiles/story_tileset.c -o story_tileset.o
lcc -Wf-bo1 -c dev/data/tiles/sprite_tileset.c -o sprite_tileset.o
lcc -Wf-bo1 -c dev/data/tiles/sprite_bkg_tileset.c -o sprite_bkg_tileset.o
lcc -Wf-bo1 -c dev/data/tiles/bkg_tileset.c -o bkg_tileset.o
lcc -Wf-bo1 -c dev/data/tiles/title_tileset.c -o title_tileset.o
REM maps
lcc -Wf-bo2 -c dev/data/maps/title_map.c -o title_map.o
lcc -Wf-bo2 -c dev/data/maps/story_map.c -o story_map.o
lcc -Wf-bo2 -c dev/data/maps/game_map.c -o game_map.o
lcc -Wf-bo2 -c dev/data/maps/gui_map.c -o gui_map.o
REM logic
lcc -c dev/main.c -o main.o
REM build
lcc -Wl-yt1 -Wl-yo4 -Wl-ya0 main.o story_tileset.o sprite_tileset.o sprite_bkg_tileset.o bkg_tileset.o title_tileset.o title_map.o story_map.o game_map.o gui_map.o dev/utils/math.s -o rom/Sheep_Kaboom.gb
REM clean
del *.o *.lst