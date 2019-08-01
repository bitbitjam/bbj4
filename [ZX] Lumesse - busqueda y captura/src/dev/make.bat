@echo off
rem Cambia "lumesse" por el nombre de tu güego.
echo ### COMPILANDO SCRIPT ###
cd ..\script
msc lumesse.spt msc.h 24
copy *.h ..\dev
cd ..\dev
echo -------------------------------------------------------------------------------
echo ### REGENERANDO MAPA ###
cd ..\map
rem cambia ALTO y ANCHO por los valores de tu mapa:
..\utils\mapcnv mapa.map 8 3 15 10 15 packed
copy mapa.h ..\dev
cd ..\dev
echo -------------------------------------------------------------------------------
echo ### COMPILANDO GUEGO ###
zcc +zx -vn lumesse.c -o lumesse.bin -lndos -lsplib2 -zorg=24200
echo -------------------------------------------------------------------------------
echo ### CONSTRUYENDO CINTA ###
rem cambia LOADER por el nombre que quieres que salga en Program:
..\utils\bas2tap -a10 -sLUMESSE loader.bas loader.tap
..\utils\bin2tap -o screen.tap -a 16384 loading.bin
..\utils\bin2tap -o main.tap -a 24200 lumesse.bin
copy /b loader.tap + screen.tap + main.tap lumesse.tap
echo -------------------------------------------------------------------------------
echo ### LIMPIANDO ###
del loader.tap
del screen.tap
del main.tap
del lumesse.bin
echo -------------------------------------------------------------------------------
echo ### DONE ###
pause
