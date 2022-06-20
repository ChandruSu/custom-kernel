#include "keyboard.h"

static void print_key(u8 sc)
{    
    char* sc_key_map[] = {
        "ERR",
        "ESC",
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "0",
        "-",
        "+",
        "BACK",
        "    ",
        "Q",
        "W",
        "E",
        "R",
        "T",
        "Y",
        "U",
        "I",
        "O",
        "P",
        "[",
        "]",
        "ENTER",
        "L-CTRL",
        "A",
        "S",
        "D",
        "F",
        "G",
        "H",
        "J",
        "K",
        "L",
        ";",
        "'",
        "`",
        "L-SHIFT",
        "\\",
        "Z",
        "X",
        "C",
        "V",
        "B",
        "N",
        "M",
        ",",
        ".",
        "/",
        "R-SHIFT",
        "KEYPAD #",
        "L-ALT",
        " "
    };

    if (sc <= 0x39) {
        kprint(sc_key_map[sc]);
    } else {
        if (sc <= 0x7f) {
            kprint("Unknown key pressed!");
        } else if (sc <= 0x39 + 0x80) {
            print_key(sc - 0x80);
            kprint(" [Up]");
        } else {
            kprint("Unknown key released!");
        }
    }
}

static void keyboard_callback(registers_t r)
{
    u8 sc = port_byte_in(0x60);

    if (sc == 28)
        kprint("\n");
    else if (sc == 14)
        kdelc();
    else if (sc <= 0x39)
        print_key(sc);
}

void init_keyboard()
{
    register_interrupt_handler(IRQ1, keyboard_callback);
}
