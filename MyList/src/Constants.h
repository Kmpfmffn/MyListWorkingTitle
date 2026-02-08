#pragma once

// Background colours
#define mfnPRIMARY_BACKGROUND_COLOUR 0x0e0e0e // light black
#define mfnSECONDARY_BACKGROUND_COLOUR 0x11171e // brown
#define mfnTERTIARY_BACKGROUND_COLOUR 0x1d232a // light brown

// Text colours
#define mfnPRIMARY_TEXT_COLOUR 0xf2f2f3 // white
#define mfnSECONDARY_TEXT_COLOUR 0xa3a3a7 // light grey slightly brownish

// Sizes
#define mfnWINDOW_WIDTH 1100
#define mfnWINDOW_HEIGHT 600
#define mfnWINDOW_SIZE wxSize(mfnWINDOW_WIDTH, mfnWINDOW_HEIGHT)

// Unicode characters
#define UNICODE_CHECKBOX_UNCHECKED wxString::FromUTF8("\xE2\x98\x90")
#define UNICODE_CHECKBOX_CHECKED wxString::FromUTF8("\xE2\x98\x91")

// Default paths
#define mfnDEFAULT_SAVE_PATH "C:\\dev\\MyListWorkingTitle\\save.txt"