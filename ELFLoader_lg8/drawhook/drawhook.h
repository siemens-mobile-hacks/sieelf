//DRAW_HOOK_v1.9 (C)Dimadze 2010 (Only SGold, Hee, hee, hee :D)

// 1.0 - First public release
// 1.1 - A small optimization
// 1.2 - Added support avtopererisovki
// 1.3 - Added support for rendering 32-bit image in the textbox
// 1.4 - Patch rewritten in a different style
// 1.5 - Added support for rendering 32-bit images in the text box, Java, accounting for borders render
// 1.6 - Added support for rendering 32-bit images in Java, the bug fixed version 1.5
// 1.7 - Added support for 32-bit rendering of a packed bitmap 0x8A
// 1.8 - Pofiksina and expanded support for 32-bit rendering of a packed bitmap 0x8A
// 1.9 - Major changes to the code selector semi-transparent images and the option for X75

// If a company (not the word "Linking") or does not start postbuild.cmd helps Project -> Clean
// Path to the project must not contain Cyrillic characters, otherwise there will be converting elf-> vkp


#ifdef SL65sw53
#endif



#ifdef S65sw58
#endif



#ifdef CX70sw56
#endif



#ifdef SK65sw50
#endif



#ifdef CX75sw25
#define X75
//Exceptions toÿ Draw Hook
#define EXC_CSM_MP 0xA04B8A60 //CSM Media Player
#define EXC_CSM_ZP 0xA04D9C7C //CSM Zoom
#endif

#ifdef C75sw22
#define X75
//Exceptions toÿ Draw Hook
#define EXC_CSM_MP 0xA04A9510 //CSM Media Player
#define EXC_CSM_ZP 0xA04B2DF0 //CSM Zoom
#endif
