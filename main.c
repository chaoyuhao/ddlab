#include "sys.h"
const char hello[]="Hello World!\n";


int main();
void entry()
{
    asm("lui sp,0x00120");
    asm("addi sp,sp,-4");
    main();
}
int main()
{
    vga_init();
    // putstr(hello);
    // vga_line_add();
    // while(1)
    // {
    //     char ch=getch();
    //     putcom(ch);
    // };
    return 0;
}