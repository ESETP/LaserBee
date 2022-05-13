/////////////////////////////////////////////////////////////////////////////
// waveform_tables.h
/////////////////////////////////////////////////////////////////////////////

#ifndef WAVEFORM_TABLES_H_
#define WAVEFORM_TABLES_H_

// A full cycle, 12-bit, unsigned sine wave lookup table
SI_SEGMENT_VARIABLE(sineTable[256], uint16_t, const SI_SEG_CODE) = 
{
    0x22D,0x23A,0x248,0x256,0x263,0x271,0x27F,0x28C,0x29A,
    0x2A7,0x2B4,0x2C2,0x2CF,0x2DC,0x2E9,0x2F6,0x302,0x30F,
    0x31C,0x328,0x334,0x340,0x34C,0x358,0x363,0x36E,0x379,
    0x384,0x38F,0x399,0x3A4,0x3AE,0x3B8,0x3C1,0x3CA,0x3D3,
    0x3DC,0x3E5,0x3ED,0x3F5,0x3FD,0x404,0x40B,0x412,0x419,
    0x41F,0x425,0x42B,0x430,0x435,0x43A,0x43E,0x442,0x446,
    0x44A,0x44D,0x44F,0x452,0x454,0x456,0x457,0x458,0x459,
    0x459,0x45A,0x459,0x459,0x458,0x456,0x455,0x453,0x451,
    0x44E,0x44B,0x448,0x444,0x440,0x43C,0x438,0x433,0x42D,
    0x428,0x422,0x41C,0x416,0x40F,0x408,0x401,0x3F9,0x3F1,
    0x3E9,0x3E1,0x3D8,0x3CF,0x3C6,0x3BC,0x3B3,0x3A9,0x39F,
    0x394,0x38A,0x37F,0x374,0x369,0x35D,0x352,0x346,0x33A,
    0x32E,0x322,0x315,0x309,0x2FC,0x2EF,0x2E2,0x2D5,0x2C8,
    0x2BB,0x2AE,0x2A0,0x293,0x285,0x278,0x26A,0x25C,0x24F,
    0x241,0x233,0x226,0x218,0x20A,0x1FD,0x1EF,0x1E1,0x1D4,
    0x1C6,0x1B9,0x1AB,0x19E,0x191,0x184,0x177,0x16A,0x15D,
    0x150,0x144,0x137,0x12B,0x11F,0x113,0x107,0xFC,0xF0,
    0xE5,0xDA,0xCF,0xC5,0xBA,0xB0,0xA6,0x9D,0x93,0x8A,0x81,
    0x78,0x70,0x68,0x60,0x58,0x51,0x4A,0x43,0x3D,0x37,0x31,
    0x2C,0x26,0x21,0x1D,0x19,0x15,0x11,0xE,0xB,0x8,0x6,0x4,
    0x3,0x1,0x0,0x0,0x0,0x0,0x0,0x1,0x2,0x3,0x5,0x7,0xA,0xC,
    0xF,0x13,0x17,0x1B,0x1F,0x24,0x29,0x2E,0x34,0x3A,0x40,
    0x47,0x4E,0x55,0x5C,0x64,0x6C,0x74,0x7D,0x86,0x8F,0x98,
    0xA1,0xAB,0xB5,0xC0,0xCA,0xD5,0xE0,0xEB,0xF6,0x101,0x10D,
    0x119,0x125,0x131,0x13D,0x14A,0x157,0x163,0x170,0x17D,
    0x18A,0x197,0x1A5,0x1B2,0x1BF,0x1CD,0x1DA,0x1E8,0x1F6,
    0x203,0x211,0x21F,0x22C,

};

// A full cycle, 12-bit, unsigned square wave lookup table
SI_SEGMENT_VARIABLE(squareTable[256], uint16_t, const SI_SEG_CODE) = 
{
   0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314,
   0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314,
   0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314,
   0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314,
   0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314,
   0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314,
   0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314,
   0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314,
   0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314,
   0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314,
   0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314,
   0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314,
   0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314,
   0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314,
   0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314,
   0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314, 0x314,
   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
   0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000, 0x000,
};

// A full cycle, 12-bit, unsigned sawtooth wave lookup table
SI_SEGMENT_VARIABLE(sawtoothTable[256], uint16_t, const SI_SEG_CODE) = 
{
    0x0,0x5,0xA,0x10,0x15,0x1A,0x20,0x25,0x2A,0x30,0x35,
    0x3A,0x40,0x45,0x4A,0x50,0x55,0x5B,0x60,0x65,0x6B,
    0x70,0x75,0x7B,0x80,0x85,0x8B,0x90,0x95,0x9B,0xA0,
    0xA5,0xAB,0xB0,0xB6,0xBB,0xC0,0xC6,0xCB,0xD0,0xD6,
    0xDB,0xE0,0xE6,0xEB,0xF0,0xF6,0xFB,0x100,0x106,0x10B,
    0x111,0x116,0x11B,0x121,0x126,0x12B,0x131,0x136,0x13B,
    0x141,0x146,0x14B,0x151,0x156,0x15B,0x161,0x166,0x16C,
    0x171,0x176,0x17C,0x181,0x186,0x18C,0x191,0x196,0x19C,
    0x1A1,0x1A6,0x1AC,0x1B1,0x1B6,0x1BC,0x1C1,0x1C6,0x1CC,
    0x1D1,0x1D7,0x1DC,0x1E1,0x1E7,0x1EC,0x1F1,0x1F7,0x1FC,
    0x201,0x207,0x20C,0x211,0x217,0x21C,0x222,0x227,0x22C,
    0x232,0x237,0x23C,0x242,0x247,0x24C,0x252,0x257,0x25C,
    0x262,0x267,0x26C,0x272,0x277,0x27D,0x282,0x287,0x28D,
    0x292,0x297,0x29D,0x2A2,0x2A7,0x2AD,0x2B2,0x2B7,0x2BD,
    0x2C2,0x2C7,0x2CD,0x2D2,0x2D8,0x2DD,0x2E2,0x2E8,0x2ED,
    0x2F2,0x2F8,0x2FD,0x302,0x308,0x30D,0x312,0x318,0x31D,
    0x322,0x328,0x32D,0x333,0x338,0x33D,0x343,0x348,0x34D,
    0x353,0x358,0x35D,0x363,0x368,0x36D,0x373,0x378,0x37D,
    0x383,0x388,0x38D,0x393,0x398,0x39E,0x3A3,0x3A8,0x3AE,
    0x3B3,0x3B8,0x3BE,0x3C3,0x3C8,0x3CE,0x3D3,0x3D8,0x3DE,
    0x3E3,0x3E8,0x3EE,0x3F3,0x3F9,0x3FE,0x403,0x409,0x40E,
    0x413,0x419,0x41E,0x423,0x429,0x42E,0x433,0x439,0x43E,
    0x444,0x449,0x44E,0x454,0x459,0x45E,0x464,0x469,0x46E,
    0x474,0x479,0x47E,0x484,0x489,0x48E,0x494,0x499,0x49F,
    0x4A4,0x4A9,0x4AF,0x4B4,0x4B9,0x4BF,0x4C4,0x4C9,0x4CF,
    0x4D4,0x4D9,0x4DF,0x4E4,0x4E9,0x4EF,0x4F4,0x4FA,0x4FF,
    0x504,0x50A,0x50F,0x514,0x51A,0x51F,0x524,0x52A,0x52F,
    0x534,0x53A,0x53F,0x544,0x54A,0x54F,0x555,

};


#endif /* WAVEFORM_TABLES_H_ */
