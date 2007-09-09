elf2vkp.exe ELFLoader.elf aaa.vkp J:\mobilephone\fullflash\ELC1v41.bin
copy /b swi.vkp+aaa.vkp ElfPack2.31.vkp
del ELFLoader.elf
del ELFLoader.hex
del aaa.vkp