#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../kernel/kernel.h"

#define BACKSPACE 0x0e
#define ENTER 0x1c

static char key_buffer[256];

#define SC_MAX 57
const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};

const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void keyboard_callback(registers_t regs) {
  u8 scancode = port_byte_in(0x60);

  if (scancode > SC_MAX) return;
  if (scancode == BACKSPACE) {
    backspace(key_buffer);
    kprint_backspace();
  } else if (scancode == ENTER) {
    kprint("\n");
    user_input(key_buffer);
    key_buffer[0] = '\0';
  } else {
    char letter = sc_ascii[(int)scancode];
    char str[2] = {letter, '\0'};
    append(key_buffer, letter);
    kprint(str);
  }

  UNUSED(regs);
}

void init_keyboard() {
  register_interrupt_handler(IRQ1, keyboard_callback);
}

void print_letter(u8 scancode) {
  switch(scancode) {
    case 0x0:
    kprint("error");
    break;
    case 0x1:
      kprint("esc");
      break;
    case 0x2:
      kprint("1");
      break;
    case 0x3:
      kprint("2");
      break;
    case 0x4:
      kprint("3");
      break;
    case 0x5:
      kprint("4");
      break;
    case 0x6:
      kprint("5");
      break;
    case 0x7:
      kprint("6");
      break;
    case 0x8:
      kprint("7");
      break;
    case 0x9:
      kprint("8");
      break;
    case 0x0a:
      kprint("9");
      break;
    case 0x0b:
      kprint("0");
      break;
    case 0x0c:
      kprint("-");
      break;
    case 0x0d:
      kprint("+");
      break;
    case 0x0e:
      kprint("backspace");
      break;
    case 0x0f:
      kprint("tab");
      break;
    case 0x10:
      kprint("q");
      break;
    case 0x11:
      kprint("w");
      break;
    case 0x12:
      kprint("e");
      break;
    case 0x13:
      kprint("r");
      break;
    case 0x14:
      kprint("t");
      break;
    case 0x15:
      kprint("y");
      break;
    case 0x16:
      kprint("u");
      break;
    case 0x17:
      kprint("i");
      break;
    case 0x18:
      kprint("o");
      break;
    case 0x19:
      kprint("p");
      break;
    case 0x1a:
      kprint("[");
      break;
    case 0x1b:
      kprint("]");
      break;
    case 0x1c:
      kprint("enter");
      break;
    case 0x1d:
      kprint("lctrl");
      break;
    case 0x1e:
      kprint("a");
      break;
    case 0x1f:
      kprint("s");
      break;
    case 0x20:
      kprint("d");
      break;
    case 0x21:
      kprint("f");
      break;
    case 0x22:
      kprint("g");
      break;
    case 0x23:
      kprint("h");
      break;
    case 0x24:
      kprint("j");
      break;
    case 0x25:
      kprint("k");
      break;
    case 0x26:
      kprint("l");
      break;
    case 0x27:
      kprint(";");
      break;
    case 0x28:
      kprint("'");
      break;
    case 0x29:
      kprint("`");
      break;
    case 0x2a:
      kprint("lshift");
      break;
    case 0x2b:
      kprint("\\");
      break;
    case 0x2c:
      kprint("z");
      break;
    case 0x2d:
      kprint("x");
      break;
    case 0x2e:
      kprint("c");
      break;
    case 0x2f:
      kprint("v");
      break;
    case 0x30:
      kprint("b");
      break;
    case 0x31:
      kprint("n");
      break;
    case 0x32:
      kprint("m");
      break;
    case 0x33:
      kprint(",");
      break;
    case 0x34:
      kprint(".");
      break;
    case 0x35:
      kprint("/");
      break;
    case 0x36:
      kprint("rshift");
      break;
    case 0x37:
      kprint("keypad *");
      break;
    case 0x38:
      kprint("lalt");
      break;
    case 0x39:
      kprint("spc");
      break;
    default:
      if (scancode <= 0x7f) {
        kprint("unknow key down");
      } else if (scancode <= 0x39 + 0x80) {
        kprint("key up ");
        print_letter(scancode - 0x80);
      } else {
        kprint("unknown key up");
      }
      break;
    
  }
}