#include "sys.h"

char*vga_start= (char *)VGA_START;
int vga_line=0;
int vga_ch=0;

void putch(char ch){
    vga_start[vga_line*VGA_MAXCOL+vga_ch]=ch;
    return;
}

void putstr(char *str){
    for(char *p=str;*p!=0;p++){
        putch(*p);
    }
}