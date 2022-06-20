#pragma once

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_TEXT 0x0f
#define RED_TEXT   0xf4

/* I/O registers */
#define SCREEN_CTRL 0x3d4
#define SCREEN_DATA 0x3d5

#include "ports.h"
#include "../libc/mem.h"
#include "../libc/math.h"

/* kernel methods */
void clear_screen();

void kprint(char *msg);

void kprint_at(char *msg, int col, int row);

void kprintln(char* msg);

int kprintc(char c, int col, int row, char attr);

int kdelc();

int get_cursor_pos();

void set_cursor_pos(int col, int row);