elf2vkp.exe ..\%1\exe\ELFLoader.elf ELFLoader.tmp %2
echo %1 >version.tmp
date /T >date.tmp
copy /b name+version.tmp+copyright+date.tmp+swi+ELFLoader.tmp ElfPack_%1.vkp
del *.tmp
del ..\%1\exe\ELFLoader.*