#include "sys.h"
char hello[]="Hello World!\n";


int main();
void entry()
{
    asm("lui sp,0x00120");
    asm("addi sp,sp,-4");
    main();
}
int main()
{
    putstr(hello);
    return 0;
}