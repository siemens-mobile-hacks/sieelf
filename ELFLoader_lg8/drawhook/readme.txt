DRAW_HOOK / Capture of function DrawObject
(c)Dimadze
(!)To complete all work needed ELFPAck 2.3 24bit+alpha!
V1.9

Available for:
-------------------------------------------
CX75v25
C75v22

SL65v53
CX70v56
S65v58
SK65v50
-------------------------------------------

ELFPack'i 2.3 24bit + alpha to SGold X65 can take away \elfpacks\

You can put a full VKP\MODELvFIRMWARE\FF.bin for automatic calculation of old data for a patch

For example:
MODELvFIRMWARE - SL65v53

Description.
The patch, which monitors the function of DrawObject (), through which almost all drawn by Siemens,
ie when the parameter is a pointer to the fifth object rendering (`IMGHDR + RECT), the patch checks
on the alpha channel if it is not (bpnum! = 0x0A), then all is drawn in a standard way, or
in the case enters samopisnaya p-Ia rendering, it is made to optimize.
At the heart of her work is writing bitmap image directly into an intermediate buffer rendering
I called him RamScreenPhoneCache (there is similar to Java) c computation of color with alpha - channel.
As a result, may otrisovyvtsya SGold X65 32 bit (24bit + alpha) images of elves, as well as change
schedule using all 32 bits instead of 8 and 16.
Even on the CX75 is the difference, according to the standard seen "divorce", with the patch image is drawn very clearly.
Rendering speed and without the patch on my observations do not menyaetsya.


Why on X65 needed Specials ELFPack.
The fact that support for loading 32-bit bitmap from png to X65 spetsalno cut in ELFPack 2.3,
as the phone anyway can not draw it, why take up space, right?
But now the phone is learned, and correspondingly he wants ELFPack 24 bit + alpha.
 
How to port.
The project is set up, and ready to be compiled.
I've already done three configurations, SL65v53, CX70v56, S65v58

When porting should pay attention to these two faila in the folder \config\:
 
 - MODELswFIRMWARE.xcl     (SL65v53.xcl)
 - drawhook.h

//MODELswFIRMWARE.xcl


PATCH_BODY, CODE ... - It's an empty place in the body patch
PATCH_DRAWOBJECT_OBJ05 - address ip-uu routines DrawObject ()
PATCH_DRAWOBJECT_OBJ17 - address ip-uu routines DrawObject ()

In addition to X75 must:


PATCH_REPAIRJUMP145 - Seat 8 byte transfer to GBS_GetCurCepid
PATCH_REPAIRJUMP100 - Seat 8 byte transfer to GBS_SendMessage 

PATCH_DRAWOBJECT_OBJ05_J32 - PATCH_REPAIRJUMP100 + 0x04 (additional space for 32bit Branch'a)
PATCH_DRAWOBJECT_OBJ17_J32 -  PATCH_REPAIRJUMP145 + 0x04 (additional space for 32bit Branch'a)

PATCH_LOCALJUMP145 - Address GBS_GetCurCepid (0x145)
PATCH_LOCALJUMP100 - Address GBS_SendMessage (0x100)

//drawhook.h

For X75:
#define EXC_CSM_MP - CSM Media Players
#define EXC_CSM_ZP - CSM functions Zoom


Now, where to look for anything you do not want this information but I'll leave ...

How to search RamScreenPhoneCache.
To find it open in full IDA, go to the address ip-uu DrawObject
(Taken from swilib.vkp, perhaps they will be there a few, take any).
Dizassemblim (THUMB), the first available command videm BL, go for it, look around,
find command LDR c loading into RAM-address register is found?
Turn ArmDebugger, go to this address, see Index, a debugger it is highlighted in yellow,
move (just click on it), now take the address (on CX75v25: 0xA84AE7B8)
and add to it 0xAC (Well, it's on CX75v25, and what have you got there, I xs), we 0xA84AE7B8 +0 xAC = 0xA84AE864.
This is the address of the buffer itself. If you turn on the Monitor (M) in ArmDebugger,
on the phone and put a white background, white headband, anything, will see an array of bytes 0xFF,
from where it started there and the starting address of the buffer.
True to SL65v53 I added no 0xAC, and 0x1C5B4, so here is ...

Well, or you can suggest the following method:
Disable the overlay view (if it was pererzagruzhaem and phone number).
Turn ArmDebugger go to RamScreenBuffer (0x0E0, take a swilib.vkp),
and from the beginning of the buffer copy byte 60. We now turn to 0xA8400000,
And from start to search for these 60 bytes, and the phone dozhen work in a same window,
type, if it was at IDLE, and then remain at IDLE dozhen before the end of your search.
RamScreenPhoneCache always to RamScreenBuffer (but before RamScreenJavaCache, it is also an intermediate buffer. But for Java)

Well, if you are not tired to read, then a third way:
Search for pattern Smelter'om or manually

Retrieved on SL65/53, CX70/56, S65/58:
ADDR: char * RamScreenPhoneCache ()=&(??, 48?, 22,?, 21,00,90,?, 48,02,92,04,22,01,91,00,23, A4, 38) 
// SGold X65
Retrieved on S75/22, CF75/23, CX75/25:
ADDR: char * RamScreenPhoneCache ()=&(??, 49?, 22,??, 48,02,92,04,22,00,23,0 C, 39,00,90) 
// SGold X75


Version History:
1.0 - First public release
1.1 - Do some optimization
1.2 - Added support for screen avtopererisovki

It turns out, DrawObject after placing the object in the buffer immediately redraws the screen, and my spec - p-Ia,
of course, do not know how, but if along the way with a translucent image was drawn, such as line,
the screen is redrawn to safely along with a picture, but if there is nothing but the alpha images?
That's right, pictured to the emptiness that we have seen in the elf Turnoff'a, so decided to rendering
32-bit image to insert ma-and-a-Lyonka one bit IMGHDR (1x1) and the bug disappeared.

1.3 - Redrawing translucent image in the textbox

In the text box, as we know, have to be characters, but there is also a possibility to add there
pictures, that is, special characters, encoded as pictures, well, so come DrawObject characters
rather than pictures, and the interception was not working, as a result of a void. But finally found a place where they (pictures, symbols)
come in a "pure" and there is also set to intercept, well, you guessed it - pictures are visible on the screen.

1.4 - Patch rewritten in another way, reduce the size of the patch, an additional avtopererisovka screen is no longer needed.

1.5 - Yet another permutation

Unloaded the frame, leaving one team in each, ie reduced once the recovery code,
Added support for translucent images in the text box, Java, now the patch is easy porting,
ie need to find a tie and everything, no additional ROM / RAM address.
It also keeps track of global boundaries rendering, ie, picture does not come out to where it is impossible.
but tie deystvitelny within + / - 4 MB, so the X75 does not reach to the body of the patch.
And incidentally, to get into the firmware with the "surgical" interventions - this is not good
of the advantages: a small advantage as a draw, but from the minuses - bugs, lag, razderbanennaya
p-Ia DrawObject.

1.6 - Drawing translucent images in Java and some bugs ipravleny

1.7 - Added support for 32-bit rendering of a packed bitmap 0x8A

The fact that the decryption algorithm RLE, based on what packing the bitmap is not fully working
but for me there is no evidence that it is not sufficient for a full rendering.
In any case, I will look for a more versatile and the best way to solve this problem.

1.8 - Fixed rendering 32-bit bitmap packaged 0x8A

Now it works 100%, the mechanism of RLE bitmap to a packed 0x8A podderzhivaetsya completely.
And the piano is equipped with anti-Ia hangs, if she was given incorrectly drawn bitmap.
The fact that the performance of the bitmap nepravelnom, the entire sequence of pixels goes awry,
this may cause a false reading of multiple repetitions and then drawing goes far beyond
bitmap in RAM'e. And so like a snowball, telephone and will be engaged in this rendering - eventually hang.

1.9 - A little orderly mechanism for the selection of pictures, as well as retracting glitch in media player for X75

More carefully studied piano Theological DrawObject, but rather its distribution mechanism otrisovok objects, I do not know
it will help to speed, but this kashy in the source code is no more. Since nothing else is invented, to remove a bug
a media player for X75 had ogorozhdeniem Draw Hook from it, ie from his CSM.










