#include "screen.h"

#define CALC_OFFSET(col, row) 2 * ((row) * MAX_COLS + (col))
#define CALC_ROW(pos) (pos) / (2 * MAX_COLS)
#define CALC_COL(pos) ((pos) % (2 * MAX_COLS)) / 2

int get_cursor_pos() 
{
    int pos;
    port_byte_out(SCREEN_CTRL, 14);
    pos = port_byte_in(SCREEN_DATA) << 8;

    port_byte_out(SCREEN_CTRL, 15);
    pos += port_byte_in(SCREEN_DATA);

    return pos * 2;
}

void set_cursor_pos(int col, int row)
{
    int offset = CALC_OFFSET(col, row) / 2;
    port_byte_out(SCREEN_CTRL, 14);
    port_byte_out(SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(SCREEN_CTRL, 15);
    port_byte_out(SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void clear_screen()
{
    int screen_dim = MAX_COLS * MAX_ROWS;
    int i;
    char* screen = (char*) VIDEO_ADDRESS;

    for (i = 0; i < screen_dim; i++) 
    {
        screen[i*2] = ' ';
        screen[i*2+1] = WHITE_TEXT;
    }

    set_cursor_pos(0, 0);
}

/* ----------------------------------------------------- */

int kprintc(char c, int col, int row, char attr) 
{
    unsigned char* screen = (unsigned char*) VIDEO_ADDRESS;
    if (!attr) 
    {
        attr = WHITE_TEXT;
    }

    // error indicator on bottom right of screen
    if (col >= MAX_COLS || row >= MAX_ROWS) 
    {
        screen[2 * MAX_COLS * MAX_ROWS - 2] = 'E';
        screen[2 * MAX_COLS * MAX_ROWS - 1] = RED_TEXT;
    }

    int offset = col >= 0 && row >= 0 ? CALC_OFFSET(col, row) : get_cursor_pos();

    if (c == '\n')
    {
        row = CALC_ROW(offset);
        offset = CALC_OFFSET(0, row + 1);
    }
    else 
    {
        screen[offset] = c;
        screen[offset + 1] = attr;
        offset += 2;
    }

    // scrolls screen down one row
    if (offset >= MAX_ROWS * MAX_COLS * 2) {
        int i;
        for (i = 1; i < MAX_ROWS; i++)
        {
            memcpy((void*)(CALC_OFFSET(0, i) + VIDEO_ADDRESS), (void*)(CALC_OFFSET(0, i-1) + VIDEO_ADDRESS), MAX_COLS * 2);
        }

        char* last_line = (char*)(CALC_OFFSET(0, MAX_ROWS - 1) + VIDEO_ADDRESS);
        for (i = 0; i < MAX_COLS * 2; i++) {
            last_line[i] = 0;
        }
        offset -= 2 * MAX_COLS;
    }

    set_cursor_pos(CALC_COL(offset), CALC_ROW(offset));
    return offset;
}

int kdelc()
{
    int offset = get_cursor_pos();
 
    int row = CALC_ROW(offset);
    int col = CALC_COL(offset) - 1;
    offset = CALC_OFFSET(col, row);

    if (offset < 0) {
        return offset;
    }

    unsigned char* screen = (unsigned char*) VIDEO_ADDRESS;
    screen[offset] = ' ';
    screen[offset+1] = WHITE_TEXT;

    set_cursor_pos(col, row);
    return offset;
}

void kprint(char* msg)
{
    kprint_at(msg, -1, -1);
}

void kprintln(char* msg)
{
    kprint(msg);
    kprint("\n");
}

void kprint_at(char* msg, int col, int row)
{
    int offset;

    if (col >= 0 && row >= 0) 
    {
        offset = CALC_OFFSET(col, row);
    } 
    else 
    {
        offset = get_cursor_pos();
        row = CALC_ROW(offset);
        col = CALC_COL(offset);
    }

    // loops through message and prints characters
    int i = 0;
    while (msg[i] != '\0') 
    {
        offset = kprintc(msg[i++], col, row, WHITE_TEXT);
        row = CALC_ROW(offset);
        col = CALC_COL(offset);
    }
    set_cursor_pos(col, row);
}
