Memory Control / The control layout of RAM at startup
(c)Dimadze
(r)feanor (for code search blocks in EEPROM)
(!) Conflict with all patches on memory:
(!) Cancel the previous version of the patch
A possible list:

browser killer
memory resizer 
change nonperm/perm
cutheap

v1.1

Available for:
------------------
SL65v53
------------------

Description
That on the basis of all knowledge, and patches of RAM on X65, decided to make one "mega" patch.
When you start the phone is counting RAM, ie, Share on
NonPermMemory, PermMemory, JavaHeap, the rest of us are not interested.
Thus, the patch loads the configuration and layout if you want to stop
downloading a browser or Java-machine (or both).
Configuration (1 byte) are contained in the 5304 block EEFULL, so to change them
require a special elf configurator.
Functions for working with PS / Fail during the patch does not work,
therefore attributable to use EEPROM.

By the way, this patch does and Theological Faculty patch CutHeap.

Ect 8 fixed regimes, as opportunity
free, and most importantly, change the values ??of mismanagement
Memory can lead to poor results,
and in particular pikoffu at startup or not to include all, just like that!

  1 - Normal
  2 - Killed browser
  3 - Increase NonPermMmem
  4 - Increase Killed browser NonPermMmem (NonPermSize: 4 Mb)
  5 - Optimal NonPerm / JavaHeap # 1 (NonPermSize: 3.5 Mb, JavaHeap: 2 Mb)
  6 - Optimum NonPerm / JavaHeap # 2 (NonPermSize: 2.5 Mb, JavaHeap: 3 Mb)
  7 - Maximum NonPermMem (NonPermSize: 5,64 Mb) (Java does not work!)
  8 - Maximum JavaHeap (NonPermSize: 1 Mb, JavaHeap: 4.2 Mb)

Startup parameter set special elf-configurator
Can run without restarting the browser.
* This total memory size (but not free!)