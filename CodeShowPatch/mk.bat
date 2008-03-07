%1\..\tools\elf2vkp.exe %2\CodeShowPatch.elf %2\t.tmp e:\fullflash\lg8\%3.bin
copy /b %2\about.txt+%2\t.tmp+%2\DataBase.vkp %2\CodeShowPatch_%3.vkp
del *.tmp
del *.dep
rd /s /q %1\%3
rd /s /q %1\settings
%1\..\tools\7z.exe a %1\CodeShowPatch_%3.zip %1\CodeShowPatch_%3.vkp