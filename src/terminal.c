#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include "terminal.h"

/*
 * Terminal that writes to the VGA buffer. Not threadsafe. Must call
 * terminal_initialize before using.
 */

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

static inline uint8_t vga_entry_color(enum vga_color fg,
                                      enum vga_color bg)
{
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color)
{
    return (uint16_t) uc | (uint16_t) color << 8;
}

size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

void terminal_initialize(void)
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*) 0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_setcolor(uint8_t color)
{
    terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color,
                         size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
    terminal_putentryat(c, terminal_color,
                        terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
            terminal_row = 0;
    }
    if(c == 10)
      write_newline();
}

void write_newline() {
  ++terminal_row;
  terminal_column = 0;
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
      if(data[i] == 10) {
        write_newline();
      }
      else {
        terminal_putchar(data[i]);
      }
    }
}

void terminal_writestring(const char* data)
{
    terminal_write(data, strlen(data));
}


void print(char type, ...)
{
  va_list args;
  // assumed to be 1 for now.
  va_start(args, type);

  switch(type){
    case 'l': //fall through.
    case 'd' :
      {
        int val = va_arg(args, int);
        char buf[65];
        buf[64] = '0';
        int temp;
        int i = 0;

        do{
          temp = val;
          val /= 10;

          if(i == 64){
            for(int j = i; j >= 0; j--){
              terminal_putchar(buf[j]);
            }
            i = 0;
          }

          buf[i] =  "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (temp - val * 10)];
          i++;
        } while(val);

        for(int j = i-1; j >= 0; j--){
          terminal_putchar(buf[j]);
        }
      }
      break;
    default:
      break;
  }
  va_end(args);
}

int convert_int(int value, int radix)
{
  int new[64];
  for(int i=0; i < 64; i++){
    new[i] = 0;
  }

  int digit = 0;
  while(value != 0){
    new[digit] = value % radix;
    digit++;
    value = value / radix;
  }

  int new_val = 0;
  for(int i = digit; digit >= 0; digit--){
    new_val += new[i]*radix*digit;
  }

  return new_val;
}
