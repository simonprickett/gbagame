rem GameBoy Advance Game make file

path=c:\gbadev\tools\devkitadv\bin

gcc -c -O3 -mthumb -mthumb-interwork main.c
gcc -mthumb -mthumb-interwork -o gbagame.elf main.o

objcopy -O binary gbagame.elf gbagame.gba

pause

