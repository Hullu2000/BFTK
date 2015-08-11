/*Copyright (c) 2015 Hullu2000

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.*/

#if !defined(__cplusplus)
#include <stdbool.h>
#endif
#include <stddef.h>
#include <stdint.h>

#include "io.h"
#include "keys.h"

#include "vga.h"

uint16_t make_vgaentry(char c, uint8_t color)
{
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

size_t strlen(const char* str)
{
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize()
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = FG | BG << 4;
	terminal_buffer = (uint16_t*) 0xB8000;
	for ( size_t y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}

 void update_cursor(int row, int col)
 {
    unsigned short position=(row*80) + col;

    // cursor LOW port to vga INDEX register
    write_port(0x3D4, 0x0F);
    write_port(0x3D5, (unsigned char)(position&0xFF));
    // cursor HIGH port to vga INDEX register
    write_port(0x3D4, 0x0E);
    write_port(0x3D5, (unsigned char)((position>>8)&0xFF));
 }

void terminal_putchar(char c)
{
    bool rc = false;
    switch(c)
    {
        case '\n':
            terminal_column = 0;
            rc = true;
            break;
        case '\b':
            terminal_column--;
            if(terminal_column < 0)
            {
                terminal_column = 0;
                terminal_row--;
            }
            terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
        break;

        default:
        	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
            if ( ++terminal_column == VGA_WIDTH )
            {
                terminal_column = 0;
                rc = true;
            }
        break;
    }
    if(rc)
    {
        if (++terminal_row == VGA_HEIGHT)
        {
            for(int i = 0; i < VGA_HEIGHT - 1; i++)
            {
                for(int j = 0; j < VGA_WIDTH; j++)
                {
                    terminal_buffer[i * VGA_WIDTH + j] = terminal_buffer[(i + 1) * VGA_WIDTH + j];
                }
            }
            for(int j = 0; j < VGA_WIDTH; j++)
            {
                terminal_putentryat(' ', terminal_color, j, 24);
            }
            terminal_row = VGA_HEIGHT - 1;
        }
    }
    update_cursor(terminal_row, terminal_column);
}

void terminal_writestring(const char* data)
{
	size_t datalen = strlen(data);
	for ( size_t i = 0; i < datalen; i++ )
		terminal_putchar(data[i]);
}

