/* C source file created by SevenuP v1.20                                */
/* SevenuP (C) Copyright 2002-2006 by Jaime Tejedor Gomez, aka Metalbrain*/

/*
GRAPHIC DATA:
Pixel Size:      (256,  64)
Char Size:       ( 32,   8)
Sort Priorities: Char line, X char, Y char
Data Outputted:  Gfx+Attr
Interleave:      Sprite
Mask:            No
*/

unsigned char tileset[2304] = {
  0,  0,  0,  0,  0,  0,  0,  0,
  0, 16, 16, 16, 16,  0, 16,  0,
  0, 36, 36,  0,  0,  0,  0,  0,
  0, 36,126, 36, 36,126, 36,  0,
  0,  8, 62, 40, 62, 10, 62,  8,
  0, 98,100,  8, 16, 38, 70,  0,
  0, 16, 40, 16, 42, 68, 58,  0,
  0,  8, 16,  0,  0,  0,  0,  0,
  0,  4,  8,  8,  8,  8,  4,  0,
  0, 32, 16, 16, 16, 16, 32,  0,
  0,  0, 20,  8, 62,  8, 20,  0,
  0,  0,  8,  8, 62,  8,  8,  0,
  0,  0,  0,  0,  0,  8,  8, 16,
  0,  0,  0,  0, 62,  0,  0,  0,
  0,  0,  0,  0,  0, 24, 24,  0,
  0,  0,  2,  4,  8, 16, 32,  0,
  0, 60, 70, 74, 82, 98, 60,  0,
  0, 24, 40,  8,  8,  8, 62,  0,
  0, 60, 66,  2, 60, 64,126,  0,
  0, 60, 66, 12,  2, 66, 60,  0,
  0,  8, 24, 40, 72,126,  8,  0,
  0,126, 64,124,  2, 66, 60,  0,
  0, 60, 64,124, 66, 66, 60,  0,
  0,126,  2,  4,  8, 16, 16,  0,
  0, 60, 66, 60, 66, 66, 60,  0,
  0, 60, 66, 66, 62,  2, 60,  0,
  0,  0,  0, 16,  0,  0, 16,  0,
  0,  0, 16,  0,  0, 16, 16, 32,
  0,  0,  4,  8, 16,  8,  4,  0,
  0,  0,  0, 62,  0, 62,  0,  0,
  0,  0, 16,  8,  4,  8, 16,  0,
  0, 60, 66,  4,  8,  0,  8,  0,
  0, 60, 74, 86, 94, 64, 60,  0,
  0, 60, 66, 66,126, 66, 66,  0,
  0,124, 66,124, 66, 66,124,  0,
  0, 60, 66, 64, 64, 66, 60,  0,
  0,120, 68, 66, 66, 68,120,  0,
  0,126, 64,124, 64, 64,126,  0,
  0,126, 64,124, 64, 64, 64,  0,
  0, 60, 66, 64, 78, 66, 60,  0,
  0, 66, 66,126, 66, 66, 66,  0,
  0, 62,  8,  8,  8,  8, 62,  0,
  0,  2,  2,  2, 66, 66, 60,  0,
  0, 68, 72,112, 72, 68, 66,  0,
  0, 64, 64, 64, 64, 64,126,  0,
  0, 66,102, 90, 66, 66, 66,  0,
  0, 66, 98, 82, 74, 70, 66,  0,
  0, 60, 66, 66, 66, 66, 60,  0,
  0,124, 66, 66,124, 64, 64,  0,
  0, 60, 66, 66, 82, 74, 60,  0,
  0,124, 66, 66,124, 68, 66,  0,
  0, 60, 64, 60,  2, 66, 60,  0,
  0,254, 16, 16, 16, 16, 16,  0,
  0, 66, 66, 66, 66, 66, 60,  0,
  0, 66, 66, 66, 66, 36, 24,  0,
  0, 66, 66, 66, 66, 90, 36,  0,
  0, 66, 36, 24, 24, 36, 66,  0,
  0,130, 68, 40, 16, 16, 16,  0,
  0,126,  4,  8, 16, 32,126,  0,
  0, 14,  8,  8,  8,  8, 14,  0,
  0,  0, 64, 32, 16,  8,  4,  0,
  0,112, 16, 16, 16, 16,112,  0,
  0, 16, 56, 84, 16, 16, 16,  0,
  0,  0,  0,  0,  0,  0,  0,255,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,193,255,
  0,  0,  0,  0,  0,  7,223,255,
255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,
255,255,255,255,127, 39, 34,  0,
255,255,255,255,254,188, 16,  0,
  8, 24, 60, 14,  7,  3,  1,  1,
  0,  0,  0,  0,  0,192,128,  0,
  0,  0,  3,  7, 15, 15,  7,  3,
  0,  0,224,240,248,248,240,224,
  0,  0,  0, 16, 24, 12,  6,  1,
128,128,128,128,136,152,176,192,
  0,  0,  0,  1,  0,  4,  0,  8,
  0,  0,  0,  0, 64,  8,  0, 64,
  0,  3,  7, 15, 15, 15, 15,  3,
  0,  0,192,224,240,240,240,192,
255,255,255,255,255,222,221,221,
255,255,255,255,255,227,107, 99,
220,219,195,255,255,255,255,255,
107,171,163,255,255,255,255,255,
255,255,255,255,255,255,192,192,
255,255,255,255,191,159, 15,  7,
192,192,255,255,255,255,255,255,
  7, 15,159,191,255,255,255,255,
255,255,255,255,127, 39,  3,  0,
255,255,255,255,254,188, 24,  0,
255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,
  7,  7,  7, 15, 15, 15, 31, 63,
224,224,224,240,240,240,248,252,
 31, 15, 15, 31, 15,  7,  7,  7,
248,240,240,248,240,224,224,224,
  7,  7,  7,  7,  7,  7,  7,  7,
224,224,224,224,224,224,224,224,
  7,  7,  7,  7,  7,  7,  7,  7,
224,224,224,224,224,224,224,224,
  0,  0,  0,  0,128,224,242,255,
  0,  0,  0,  0,  1, 11, 31, 63,
255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,
250,208,242, 80,175, 13, 47,  5,
 14,  5, 11,  5,224, 80,160, 80,
250,208,242, 80,175, 13, 47,  5,
 14,  5, 11,  5,224, 80,160, 80,
255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,
255,255,255,255,255,255,255,255,
  0,  0,  0,  0,  0,  8,  8,  8,
  0,128,128,136,136,136,136,136,
 12, 12, 31, 31, 63,127,127,127,
152,152,184,248,252,254,254,254,
  0,  0,  0,128,193,227,178,158,
  0,  0,  0,  1,  3,133,201,113,
140,156,180,163,225,128,  0,  0,
 49,113,217,143,  3,  1,  0,  0,
  0,  1,  3,  6, 12, 24, 16, 24,
  0,128,192, 96, 48, 24,  8, 24,
 28, 28, 24,  8,  7,  3,  1,  0,
 56, 56, 24, 16,224,192,128,  0,
  0, 28, 62,127,127,127,127,127,
  0, 56,124,254,254,254,254,254,
127,127, 63, 31, 15,  7,  3,  1,
254,254,252,248,240,224,192,128,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  7, 15, 15, 31,
  0,  0,  0,  0,128,192,192,224,
  0,  0,  1,  3,  6,  6,  6,  3,
  0,  0,128,192, 96, 96, 96,192,
  1,  1,  1,  1,  7,  1,  7,  0,
128,128,128,128,128,128,128,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  9,  0,  2, 63, 32, 63,  8,
  0, 64, 16,128,252,  4,252, 16,
248,128,128,128,128,128,128,255,
 31,  1,  1,  1,  1,  1,  1,255,
  0,  0, 30, 12, 63, 33, 33, 63,
  0,  0,127, 20, 20, 20, 20,  8,
255,255,224,224,224,224,224,224,
255,255,  0,  0,  0,  0,  0,  0,
  0,  0,  3,  1,  2,  4,  2,  1,
  0,  0,192,128, 64, 32, 64,128,
255,255,  3,  3,  3,  3,  3,  3,
255,255,192,192,192,192,192,192,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
255,255,  0,  0,  0,  0,  0,  0,
255,255,  7,  7,  7,  7,  7,  7,
255,224,240,184,156,142,135,130,
255,  7, 15, 29, 57,113,225, 65,
130,135,142,156,184,240,224,255,
 65,225,113, 57, 29, 15,  7,255,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0, 71, 71, 71, 71, 71, 71, 71,
 71, 71, 71, 71, 71, 71, 71, 71,
 71, 71, 71, 71, 71, 71, 71, 71,
 71, 71, 71, 71, 71, 71, 71, 71,
 71, 71, 71, 71, 71, 71, 71, 71,
 71, 71, 71, 71, 71, 71, 71, 71,
 71, 71, 71, 71, 71, 71, 71, 71,
 71, 71, 71, 71, 71, 71, 71, 71,
  7,  7,  7,  7, 38, 38,  6,  6,
 46, 46, 47, 47, 66, 66,  4,  4,
  7,  7,  2,  2, 71, 71, 71, 71,
 87, 87, 87, 87, 46, 46,  5,  5,
  7,  7,  7,  7,  7,  7,  7,  7,
 15, 15,  7,  7, 15, 15, 15, 15,
  5,  5,  5,  5,  7,  7,  7,  7,
  1, 66,  1, 66, 68, 68, 68, 68,
  2,  2,  2,  2,  0,  0,  7,  7,
 70, 70, 70, 70,  0,  0,  0,  0,
  7,  7,103,103,  7,  7,  6,  6,
  7,  7,  6,  6,  0,  0,  6,  6,
 70, 70, 70, 70,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0,
  0,  0,  0,  0,  0,  0,  0,  0};
