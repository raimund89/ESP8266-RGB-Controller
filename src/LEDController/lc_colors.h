#ifndef LC_COLORS
#define LC_COLORS

// r - red
// g - green
// b - blue
// l - lightness/brightness
// w - warm white
typedef struct {
    byte r;
    byte g;
    byte b;
    byte l;
    byte w;
} Color;

// Some default colors
#define COLOR_BLACK {  0,   0,   0, 128,   0}
#define COLOR_RED   {255,   0,   0, 128,   0}
#define COLOR_GREEN {  0, 255,   0, 128,   0}
#define COLOR_BLUE  {  0,   0, 255, 128,   0}
#define COLOR_WHITE {  0,   0,   0, 128, 255}

#endif
