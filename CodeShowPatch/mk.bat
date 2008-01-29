..\elfloader_lg8\vkp\elf2vkp.exe .\%1\exe\CodeShowPatch.elf t.tmp K:\fullflash\lg8\%1.bin
copy /b about.txt+t.tmp+DataBase.vkp CodeShowPatch_%1.vkp
del *.tmp
RD /S /Q .\%1
RD /S /Q .\settings