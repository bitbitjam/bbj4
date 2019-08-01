..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o sheepitup.o sheepitup.c
..\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -o sheepitup.gb sheepitup.o
del *.o
del *.map
del *.lst
del *.sym
..\bgb\bgb.exe -rom bitbitjam4.gb