#define VGA_START 0x00200000
#define VGA_MAXLINE 30
#define VGA_MAXCOL 80
#define KEY_TAIL     0x00300020
#define KEY_START    0x00300000
#define TIME_ADDR    0x00400000
void putstr(char* str);
void putch(char ch);
void vga_init(void);
void vga_line_add();//vga


char getch();
void putcom(char ch);//kbd


void deal_com(char * com );//deal command

int strcmp(const char*s1,const char* s2);



unsigned int __udivsi3(unsigned int a, unsigned int b);
unsigned int __umodsi3(unsigned int a, unsigned int b);
int __divsi3(int a, int b) ;
int __modsi3(int a,int b) ;
long long int _long_divsi3(long long int a, int b) ;
long long int _long_modsi3(long long int a,int b) ;
unsigned int __mulsi3(unsigned int a, unsigned int b) ;//calculation

