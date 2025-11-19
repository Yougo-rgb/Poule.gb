c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o ./build/poule.o ./project/main.c
c:\gbdk\bin\lcc -c -o ./build/audio.o ./project/src/audio.c
c:\gbdk\bin\lcc -c -o ./build/player.o ./project/src/player.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -o ./build/poule.gb ./build/poule.o ./build/player.o ./build/audio.o