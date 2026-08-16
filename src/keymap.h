// Source - https://stackoverflow.com/a/61192565
// Posted by jonathan
// Retrieved 2026-07-26, License - CC BY-SA 4.0
// Changes were applied to certain keys

unsigned char kbd_US [128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',   
  '\t', /* <-- Tab */
  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',     
    0xC0, /* <-- control key                                    left shift                                                  right shift */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',  0xC1, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',   0xC2,
  '*',
    0xC3,  /* Alt */
  ' ',  /* Space bar */
    0xC4,  /* Caps lock */
    0xF1,  /* 59 - F1 key ... > */
    0xF2,   0xF3,   0xF4,   0xF5,   0xF6,   0xF7,   0xF8,   0xF9,
    0xF0,  /* < ... F10 */
    0xC5,  /* 69 - Num lock*/
    0xC6,  /* Scroll Lock */
    0xC5,  /* Home key */
    0xFC,  /* Up Arrow */
    0xC7,  /* Page Up */
  '-',
    0xFD,  /* Left Arrow */
    0,
    0xFE,  /* Right Arrow */
  '+',
    0xC8,  /* 79 - End key*/
    0xFF,  /* Down Arrow */
    0xC9,  /* Page Down */
    0xCA,  /* Insert Key */
    0xCB,  /* Delete Key */
    0,   0,   0,
    0xFA,  /* F11 Key */
    0xFB,  /* F12 Key */
    0,  /* All other keys are undefined */
};
