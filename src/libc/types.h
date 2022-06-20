#pragma once

#define low16(addr) (u16)((addr) & 0xffff)
#define high16(addr) (u16)(((addr) >> 16) & 0xffff)

typedef unsigned char   u8;
typedef char            i8;
typedef unsigned short  u16;
typedef short           i16;
typedef unsigned int    u32;
typedef int             i32;
