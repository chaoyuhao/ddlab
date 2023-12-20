#include "sys.h"

char*vga_start=(char*)VGA_START;
int vga_line=0;
int vga_ch=0;
char head=0;
char command[64];
char *key_tail = (char *)KEY_TAIL;
char *key_buf = (char *)KEY_START;
char hellofun[]="Hello World!\n";
char comhello[]="hello";
char comclear[]="clear";
char comfib[]="fib";

//programs:
inline void swap(int *a, int *b);
void bubble_sort(int arr[], int len);

void vga_init(){
    vga_line=0;
    vga_ch=0;
    for(int t=0;t<VGA_MAXCOL*VGA_MAXLINE;t++)
    {
        vga_start[t]=0;
    }
    vga_start[0]='n';vga_start[1]='t';vga_start[2]='e';vga_start[3]='r';vga_start[4]='m';vga_start[5]='>';vga_ch=6;
}
void vga_line_add(){
    vga_line=vga_line+1<VGA_MAXLINE?vga_line+1:0;vga_ch=6;
    vga_start[vga_line*VGA_MAXCOL+0]='n';vga_start[vga_line*VGA_MAXCOL+1]='t';vga_start[vga_line*VGA_MAXCOL+2]='e';vga_start[vga_line*VGA_MAXCOL+3]='r';
    vga_start[vga_line*VGA_MAXCOL+4]='m';vga_start[vga_line*VGA_MAXCOL+5]='>';
}
void putch(char ch){
    if(ch==8)
    {
        
        if(vga_ch>6){vga_ch--;
            vga_start[vga_line*VGA_MAXCOL+vga_ch]=0;
        }
        return;
        
    }
    else if(ch==10)
    {
        vga_line=vga_line+1<VGA_MAXLINE?vga_line+1:0;vga_ch=6;
        vga_start[vga_line*VGA_MAXCOL+0]='n';vga_start[vga_line*VGA_MAXCOL+1]='t';vga_start[vga_line*VGA_MAXCOL+2]='e';vga_start[vga_line*VGA_MAXCOL+3]='r';
        vga_start[vga_line*VGA_MAXCOL+4]='m';vga_start[vga_line*VGA_MAXCOL+5]='>';
    }
    else{
        vga_start[vga_line*VGA_MAXCOL+vga_ch]=ch;
        if(vga_ch+1==VGA_MAXCOL){vga_ch=0;vga_line=vga_line+1<VGA_MAXLINE?vga_line+1:0;}
        else{
            vga_ch++;
        }
    }
}
void putstr(char* str){
    for(char*p=str;*p!=0;p++)
    {
        putch(*p);
    }
}

int cnt=0;
char getch()//转换ascii
{
    
    char tmp;
  while (head == *key_tail)//0x0030020
    ;
    tmp = key_buf[(int)head];
  /*if(tmp == ' ' && c != 0x29 ) tmp ='\0';

  if(tmp!='\0' && tmp != 8)
  {
    command[cnt]=tmp;
    cnt++;
  }*/
    if(tmp==0x08){
        cnt--;
    }
    else if (tmp==0x0a){
        command[cnt]='\0';
    }
    else{
        command[cnt]=tmp;
        cnt++;
    }
  if (head == 0x1f || *key_tail == 0)
    head = 0;
  else
    ++head;


  return tmp;
}


void putcom(char ch)//按键
{
    if(ch==8) //backspace
  {
    putch(ch);
    
  }
  else if(ch==10) //enter
  {
  
    command[cnt] = '\0';
    vga_ch=0;

    deal_com(command);
    vga_line_add();
    cnt=0;
    command[cnt]='\0';

    return;
  }
  else{
    putch(ch);
  }
  return;
}


int strcmp(const char *s1, const char *s2) {
    while(*s1!='\0'&&*s2!='\0')
    {
        if(*s1==*s2){s1++;s2++;}
        else{
          return (*s1<*s2)?-1:1;
        }
    }
    if(*s1=='\0')
    {
        if(*s2=='\0')
        {
          return 0;
        }
        else{return -1;}
    } 
    else{
      return 1;
    }
}




void deal_com(char * com )
{
    // putstr(com);
    // char c= cnt + '0';
    // putch(c);
    // putstr(endl);
    // putch(com[cnt]);
    // putstr(endl);
//
    if(strcmp(comhello,com)==0)
    {
        putstr(hellofun); return;
    }
    if(strcmp(comclear,com)==0)
    {
        vga_init();return;
    }
    /*int flag[14]={0};  //0： hello 1：time 2:fib  3:wrong 4:color 5:cal 6:help 7:clear 8:led 9:g2048 10:snake 11:chess 12:russia 13:mazz

    if(cnt<=4)
    {
      flag[13]=1;
    }
    else
    {
      char ma[]="mazz";
      for(int i=0;i<cnt-1;i++)
      {
        if(com[i] != ma[i])
        flag[13] =1 ;
      }
    }

    if(cnt<=6)
    {
      flag[12]=1;
    }
    else
    {
      char te[]="russia";
      for(int i=0;i<cnt-1;i++)
      {
        if(com[i] != te[i])
        flag[12] =1 ;
      }
    }

    if(cnt<=5)
    {
      flag[11]=1;
    }
    else
    {
      char ch[]="chess";
      for(int i=0;i<cnt-1;i++)
      {
        if(com[i] != ch[i])
        flag[11] =1 ;
      }
    }

    if(cnt<=5)
    {
      flag[10]=1;
    }
    else
    {
      char sn[]="snake";
      for(int i=0;i<cnt-1;i++)
      {
        if(com[i] != sn[i])
        flag[10] =1 ;
      }
    }
     
    if(cnt<=5)
    {
      flag[9]=1;
    }
    else
    {
      char g2[]="g2048";
      for(int i=0;i<cnt-1;i++)
      {
        if(com[i] != g2[i])
        flag[9] =1 ;
      }
    }



    if(cnt!=6)
    {
      flag[8]=1;
    }
    else
    {
      
      char le[]="led";
      for(int i=0;i<3;i++)
      {
        if(com[i]!=le[i])
        {flag[8]=1;break;}
      }
      
      if(flag[8]==0)
      {
        if(com[3]!=' ') flag[3]=1;
        else
        {
          if(com[4]>='0' && com[4]<='9')
          {
            int x= com[4]-'0';
            *(led+x) = (char)1;
          }
          else flag[3]=1;
        }
      }
      
    }


    //输入hello cnt=6 : hello
    if(cnt<=5)
    {
      flag[0]=1;
    }
    else
    {
      char hello[]="hello";
      for(int i=0;i<cnt-1;i++)
      {
        if(com[i] != hello[i])
        flag[0] =1 ;//hello不行
      }
    }
   //time  5
    if(cnt<=4)
    {
      flag[1]=1;
    }
    else
    {
      char time[]="time";
      //输入time cnt=5
      for(int i=0;i<cnt-1;i++)
      {
        if(com[i] != time[i])
        {flag[1]=1 ;break;}
      }
    }
//   
    //输入fib 
    char fibnum2[32];
   // long long int fibnum=0;
    if(cnt<=5)
    {
      flag[2]=1;
    }
    else
    {
      

      char fi[]="fib";
      for(int i=0;i<3;i++)
      {
        if(com[i]!=fi[i])
        {flag[2]=1;break;}
      }
      if(flag[2]==0)
      {
        if(com[3]!=' ') {flag[3]=1;flag[2]=1;}
        int number=0;//10
        for(int i=4;i<cnt-1;i++)
        {
          if( com[i]>='0' && com[i]<='9' )
          {
            number = (number<<3) + (number<<1) + com[i] - '0';
          }
          else
          {
            flag[2]=1; 
            flag[3]=1;//输入有误
          }
        }
        if(flag[2]==0 && number!=0
          && number<=92
          )
        {
          //fibnum= fib(number);
          int j;
          for(j=0;fib2[number][j]!='\0';j++)
          {
          fibnum2[j]=fib2[number][j];
          }
          fibnum2[j]='\0';

        }
        else
        {
          flag[2]=1;
          flag[3]=1;
        }
      }
      
    }
    //输入 color
    if(cnt<=7)
    {
      flag[4]=1;      
    }
    else
    {
      char col[]="color";
      for(int i=0;i<=4;i++)
      {
        if(col[i]!=com[i])
        {
          flag[4]=1 ; break;
        }
      }
      if(flag [ 4] == 0)
      {
        // char red[]="red";
        // for(int i=0;i<=2;i++)
        // {
        //   if(red[i]!=com[i+6])
        //   {
        //     flag[3]=1;break;
        //   }
        // }
        // if(flag [3] ==0)
        // {
        //    *color_addr=(char)1;
        // }
        if(com[6]>='0' && com[6]<='7')
        {
          *color_addr=com[6];
        }
        else
        {
          flag[3]=1;
        }
      }
    }
    //输入 cal

    int cal_number;
    if(cnt<=5)
    {
      flag[5]=1;
    }
    else
    {
      char cal[]="cal";
      for(int i=0;i<=2;i++)
      {
          if(command[i]!=cal[i])
          flag[5]=1;
      }
      if(flag[5]==0)
      {
          char exp[100];
          for(int i=4;i<cnt-1;i++)
          {
            exp[i-4] =command [i];
          }
          exp[cnt-1-4]='\0';
          int f[1]={1};
          cal_number=expr(exp,f);
          //f=0 flag[3] = 1 flag [5] =1 
          flag[3]=1-f[0];
          flag[5]=1-f[0];
      }
    }

    //输入help
    if(cnt<=4)
    {
      flag[6]=1;
    }
    else
    {
       char help[]="help";
       for(int i=0;i<=3;i++)
       {
         if(com[i]!=help[i])
         {flag[6]=1;break;}
       }
    }

    //输入clear
    if(cnt<=5)
    {
      flag[7]=1;
    }
    else
    {
       char cle[]="clear";
       for(int i=0;i<=4;i++)
       {
         if(com[i]!=cle[i])
         {flag[7]=1;break;}
       }
    }

    // //debug
    // for(int i=0;i<=8;i++)
    // {
    //   if(flag[i])
    //   {
    //     char a[]="1";
    //     putstr(a);
    //   }
    //   else
    //   {
    //     char b[]="0";
    //     putstr(b);
    //   }
              
    // }
    // putstr(endl);
    
    if(flag[0]==0)
    {
      char temp[]="Hello World!\n";
      putstr (temp);
    }   
    else if(flag[1]==0)
    {
      char buf[100];

      int c=*time;
      c=c/1000;

      putstr(itoa_10( buf,  htob(itoa(c,buf))  ));

      putstr(endl);
    }
    else if(flag[2]==0)
    {//fib
    
        //char buf[100];
        //putstr(itoa_long_10(buf,fibnum));
        //putstr(endl);
        putstr(fibnum2);
        putstr(endl);
    }
    else if(flag[3]==1)
    {
      char wrong[]="Wrong or invalid input!\n";
      putstr(wrong);
    }
    else if(flag[4]==0)
    {     

    }
    else if(flag[5]==0)
    {
      char buf[100];
       if(cal_number<0)
       {
         putch('-');
         cal_number=-cal_number;
       }
       else if(cal_number==0)
       {
         putch('0');
       }
       putstr(itoa_10(buf,cal_number));
       putstr(endl);
    }
    else if(flag[6]==0)
    {
      //0： hello 1：time 2:fib  3:wrong 4:color 5:cal 6:help 7:clear 8:led 9:segn m
       

        putstr("===================COMMAND HELP=======================\n");
        putstr("help     : print COMMAND HELP\n");
        putstr("hello    : print hello\n");
        putstr("time     : print time\n");
        putstr("fib n    : calculate fib(n)\n");
        putstr("cal expr : calculate expression\n");
        putstr("clear    : clear the screen\n");
        putstr("led n    : turn on/off the led\n");
        putstr("g2048    : play the game 2048\n");
        putstr("snake    : play the game snake\n");
        putstr("chess    : play the game chess\n");
        putstr("russia   : play the game russia\n");
        putstr("mazz     : play the game mazz\n");
        putstr("======================================================\n");
    }
    else if(flag[7]==0)
    {
        vga_init();
    }
    else if(flag[8]==0)
    {

    }
    else if(flag[9]==0)
    {
        g2048();
    }
    else if(flag[10]==0)
    {
       snake();
    }
    else if(flag[11]==0)
    {
       chess();
    }
    else if(flag[12]==0)
    {
       russia();
    }
    else if(flag[13]==0)
    {
       mazz();
    }
    else
    {
      if(cnt!=1)
      {
        char un[]="Unknown command!\n";
        putstr(un);
      }
    }
//0： hello 1：time 2:fib  3:wrong 4:color 5:cal 6:help 7:clear 8:led 9:segn m

    // if(com == "hello")
    // {
    //   char temp[]="Hello World!\n";
    //   putstr (temp);
    // } 
    // if(com[0] == 'h')
    // {
    //   char temp[]="H\n";
    //   putstr (temp);
    // }
    // if(com[0]=='h' && com[1]== 'e')
    // {
    //   char temp[]="He\n";
    //   putstr (temp);
    // }
    // if(com[0]=='h' && com[1]=='e' && com[4]=='o')
    // {
    //   char temp[]="Hello\n";
    //   putstr (temp);
    // }
    // if(com[5]=='\0')
    // {
    //   char temp[]="Hello H\n";
    //   putstr (temp);
    // }

    // else 
    // {
    //   char un[]="Unknown command!\n";
    //   putstr(un);
    // }*/
    return;
}




















unsigned int __mulsi3(unsigned int a, unsigned int b) {
    unsigned int res = 0;
    while (a) {
        if (a & 1) res += b;
        a >>= 1;
        b <<= 1;
    }
    return res;
}

int __modsi3(int a,int b) {
    int bit = 1;
    int res = 0;

    while (b < a && bit && !((unsigned int)b & (1UL << 31))) {
        b <<= 1;
        bit <<= 1;
    }
    while (bit) {
        if (a >= b) {
            a -= b;
            res |= bit;
        }
        bit >>= 1;
        b >>= 1;
    }
    return a;
}

int __divsi3(int a, int b) {
    int bit = 1;
   int res = 0;

    while (b < a && bit && !((unsigned int)b & (1UL << 31))) {
        b <<= 1;
        bit <<= 1;
    }
    while (bit) {
        if (a >= b) {
            a -= b;
            res |= bit;
        }
        bit >>= 1;
        b >>= 1;
    }
    return res;
}

unsigned int __umodsi3(unsigned int a, unsigned int b) {
    unsigned int bit = 1;
    unsigned int res = 0;

    while (b < a && bit && !(b & (1UL << 31))) {
        b <<= 1;
        bit <<= 1;
    }
    while (bit) {
        if (a >= b) {
            a -= b;
            res |= bit;
        }
        bit >>= 1;
        b >>= 1;
    }
    return a;
}

unsigned int __udivsi3(unsigned int a, unsigned int b) {
    unsigned int bit = 1;
    unsigned int res = 0;

    while (b < a && bit && !(b & (1UL << 31))) {
        b <<= 1;
        bit <<= 1;
    }
    while (bit) {
        if (a >= b) {
            a -= b;
            res |= bit;
        }
        bit >>= 1;
        b >>= 1;
    }
    return res;
}

long long int _long_divsi3(long long int a, int b) 
{
   long long int bit = 1;
   long long int res = 0;

    while (b < a && bit && !((unsigned int)b & (1UL << 31))) {
        b <<= 1;
        bit <<= 1;
    }
    while (bit) {
        if (a >= b) {
            a -= b;
            res |= bit;
        }
        bit >>= 1;
        b >>= 1;
    }
    return res;
}
long long int _long_modsi3(long long int a,int b) 
{
   long long int bit = 1;
   long long int res = 0;

    while (b < a && bit && !((unsigned int)b & (1UL << 31))) {
        b <<= 1;
        bit <<= 1;
    }
    while (bit) {
        if (a >= b) {
            a -= b;
            res |= bit;
        }
        bit >>= 1;
        b >>= 1;
    }
    return a;
}

inline void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int arr[], int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            // 如果当前元素大于下一个元素，则交换它们
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}