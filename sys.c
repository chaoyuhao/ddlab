#include "sys.h"

char*vga_start= (char *)VGA_START;
int vga_line=0;
int vga_ch=0;
int cnt=0;
char head=0;
char command[64];
char *key_tail = (char *)KEY_TAIL;
char *key_buf = (char *)KEY_START;
char hellofun[]="Hello World! Have Fun!!\n";
char comhello[]="hello";
char comclear[]="clear";
char comfib[]="fib";
char comsort[]="sort";
char comhelp[]="help";
char comtimer[]="timer";
char comguess[]="guess";
char auther_name[]="cyh";
char auther_stuid[]="221240013";

enum operators
{
    Positive, // 值为0
    Negative, // 值为1
    Reverse,  // 值为2
    Multiply,
    Divideby,
    Module,
    Plus,
    Minus,
    Less,
    Greater,
    LeftBracket,
    RightBracket
}; 

//programs:
void swap(int *a, int *b);
void bubble_sort(int arr[], int len);
void foo();
void addline()
{

    //vga_line=vga_line+1<VGA_MAXLINE?vga_line+1:0;vga_ch=0;

    // roll
    if(vga_line == VGA_MAXLINE-1){
        for(int i=1;i<VGA_MAXCOL;i++){
            for(int j=0;j<VGA_MAXLINE;j++){
                vga_start[VGA_MAXCOL*i+j] = vga_start[VGA_MAXCOL*(i-1)+j];
            }
        }
        for(int j=0;j<VGA_MAXLINE;j++){
            vga_start[(VGA_MAXCOL-1)*VGA_MAXLINE + j] = 0;
        }
    }

}

void vga_clear(){
    vga_line=0;
    vga_ch=0;
    for(int t=0;t<VGA_MAXCOL*VGA_MAXLINE;t++)
    {
        vga_start[t]=0;
    }
    return;
}
void vga_init(){
    vga_clear();
    vga_start[0]='n';vga_start[1]='t';vga_start[2]='e';vga_start[3]='r';vga_start[4]='m';vga_start[5]='>';vga_ch=6;
}
void vga_line_add(){
    if(vga_ch!=0){
    vga_line=vga_line+1<VGA_MAXLINE?vga_line+1:0;
    }
    vga_ch=6;
    vga_start[vga_line*VGA_MAXCOL+0]='n';vga_start[vga_line*VGA_MAXCOL+1]='t';vga_start[vga_line*VGA_MAXCOL+2]='e';vga_start[vga_line*VGA_MAXCOL+3]='r';
    vga_start[vga_line*VGA_MAXCOL+4]='m';vga_start[vga_line*VGA_MAXCOL+5]='>';
}
void putch(char ch){
    if(ch==8)
    {
        if(vga_ch>6){
            vga_ch--;
            vga_start[vga_line*VGA_MAXCOL+vga_ch] = '\0';
            if(vga_ch > 6) vga_start[vga_line*VGA_MAXCOL+vga_ch-1]=command[cnt-1];
            else vga_start[vga_line*VGA_MAXCOL+5] = '>';
        }
        return;
    }
    else if(ch==10)
    {
        addline();
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

char getch()//转换ascii
{
    
    char tmp;
    while (head == *key_tail) //0x0030020
        ;
    tmp = key_buf[(int)head];
    head = *key_tail;
    return tmp;
}


void putcom(char ch)//按键
{
  if(ch==8) //backspace
  {
    cnt--;
    command[cnt] = 0;
    putch(8);
  }
  else if(ch=='\r') //enter
  {
    command[cnt] = '\0';
    vga_ch=0;
    putch('\n');
    putstr("receive command: ");
    putstr(command);
    putch('\n');
    deal_com(command);
    vga_line_add();
    cnt=0;
    for(int i=0;i<64;i++) command[i] = 0;
    return;
  }
  else{
    putch(ch);
    command[cnt] = ch;
    cnt++;
  }
  return;
}

int readnum(){
    char c = getch(); 
    putch(c);
    int tmp = 0;
    while(c<'0'|| c>'9'){ 
        c = getch();
        putch(c);
    }
    while(c>'0'-1 && c<'9'+1){
        tmp = (tmp<<1) + (tmp<<3) + c - '0';
        c = getch();
        putch(c);
    }
    return tmp;
}

int strlen(char *str){
    int ret = 0;
    for(char *p = str;*p!='\0';p++){
        ret++;
    }
    return ret;
}

void* memset(void* ptr, int value, unsigned int num) {
    unsigned char* p = ptr;
    while (num--) {
        *p++ = (unsigned char)value;
    }
    return ptr;
}

int strcmp(const char *s1, const char *s2) {
    while(1)
    {
      if(*s1=='\0'||*s2=='\0'){break;}
      if(*s1==*s2){s1++;s2++;}
      else{
        return *s1-*s2;
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

int quit(int x){
    putch('\n');
    if(x == 0) putstr("press any key to quit");
    else {
        putstr("press ");
        putch(x);
        putstr("to quit");
    }
    char ch;
    while(1){
        switch (x)
        {
        case 0:
            ch = getch();
            return 1;
        default:
            ch = getch();
            if(ch == x) return 1;
        }
    }
}

/////////////////////////////////////////////      cal          //////////////////////////

int abs(int num) {
    return num < 0 ? -num : num;
}


int multi(int a, int b) {
    int multiplier = abs(a), multiplicand = abs(b);

    int product = 0;
    while (multiplicand) {
        if (multiplicand & 0x1) {
            product = product + multiplier;
        }
        multiplier = multiplier << 1;
        multiplicand = multiplicand >> 1;
    }

    if ((a ^ b) < 0) {
        product = -product;
    }

    return product;
}

int bitlength(int a)
{
    int length = 0;
    while (a)
    {
        length = length + 1;
        a = a >> 1;
    }
    return length;
}

int lengthdiff(int a, int b)
{
    return bitlength(a) - bitlength(b);
}

int div(int a, int b) {
    int dividend = abs(a), divisor = abs(b);

    int quotient = 0;
    for (int i = lengthdiff(dividend, divisor); i >= 0; i = i - 1) {
        int r = (divisor << i);
        // Left shift divisor until it's smaller than dividend
        if (r <= dividend) {
            quotient |= (1 << i);
            dividend = dividend - r;
        }
    }

    if ((a ^ b) < 0) {
        quotient = -quotient;
    }

    return quotient;
}

int mod(int a, int b) {
    int dividend = abs(a), divisor = abs(b);

    for (int i = lengthdiff(dividend, divisor); i >= 0; i--) {
        int r = (divisor << i);
        // Left shift divisor until it's smaller than dividend
        if (r <= dividend) {
            dividend = dividend - (int) r;
        }
    }

    if (a < 0) {
        dividend = -dividend;
    }

    return dividend;
}

///////////////////////////////////////////////////

int arr[32];

void putnum(int n) {
    if (n == 0) {
        putch('0');
        return;
    }

    if (n < 0)
        putch('-');

    n = (n < 0) ? -n : n;

    int tmp_num[32];
    int i = 0;
    while (n) {
        tmp_num[i++] = mod(n, 10);
        n = div(n, 10);
    }

    i = i - 1;
    for (; i >= 0; i--)
        putch((char)tmp_num[i] + '0');
}

void sort()
{
    char tembuf[128];
    int length = 0;
    while (1)
    {
        char ch = getch(tembuf + length);
        if (ch == 8)
        { 
            putch(ch);
            if (length > 0)
            {
                length--;
                continue;
            }
        }
        if (ch == '\r')
        {
            tembuf[length] = '\0';
            break;
        }
        length++;
    }
    int flag = 0;
    int num = 0;
    for (int i = 0; i <= length; i++)
    {
        if (tembuf[i] >= '0' && tembuf[i] <= '9')
        {
            arr[num] = arr[num] * 10 + (int)(tembuf[i] - '0');
            flag = 1;
        }
        else
        {
            if (flag == 1)
            {
                num++;
            }
            flag = 0;
        }
    }
    addline();
    bubble_sort(arr, num);
    for (int i = 0; i < num; i++)
    {
        putnum(arr[i]);
        putch(' ');
    }
    putch('\n');
}


void help()
{
    putstr("===================COMMAND HELP=======================\n");
    putstr("help     : print COMMAND HELP\n");
    putstr("hello    : print hello\n");
    putstr("timer    : print time\n");
    putstr("fib n    : calculate fib(n)\n");
    putstr("cal expr : calculate expression\n");
    putstr("clear    : clear the screen\n");
    putstr("g2048    : play the game 2048\n");
    putstr("guess    : play the game guess number\n");
    putstr("======================================================\n");
}

static char hour[] = "hour(s) ";
static char minute[] = "minute(s) ";
static char second[] = "second(s) ";

unsigned int get_time() {
    return *(unsigned int*)TIME_ADDR;
}

unsigned int rand(){
    unsigned int time = get_time();
    unsigned int a = 1664525;
    unsigned int c = 1013904223;
    unsigned int m = 0xFFFFFFFF;
    unsigned int ret = mod(multi(a,time) + c, m);
    return ret;
}



void time()
{
    int time = get_time();
    time = div(time, 1000);

    int min, sec, hou;

    sec = mod(time, 60);
    time = div(time, 60);

    min = mod(time, 60);
    time = div(time, 60);

    hou = mod(time, 60);

    putnum(hou);
    putch(' ');
    putstr(hour);
    putch(' ');
    putnum(min);
    putch(' ');
    putstr(minute);
    putch(' ');
    putnum(sec);
    putch(' ');
    putstr(second);

    putch('\n');
    return;
}

int match_fib(char *str){
    int ret = 0;
    for(int i=0;i<80;i++){
        if(comfib[i] == '\0' && (str[i] == ' ')){
            for(int j=i+1;j<80;j++){
                if(str[i] < '0' || str[i] > '9') return ret;
                ret = (ret<<1) + (ret<<3) + str[i] - '0';
            }
        }
        if(str[i] == comfib[i]) continue;
        return 0;
    }
    return 0;
}

void fib(int x){
    while(x>100){
        putstr("too big (>100) \n");
        return;
    } 
    int a[101] = {0,1,1};
    for(int i=3;i<=x;i++){
        a[i] = a[i-1] + a[i-2];
    }
    putstr("it is ----->");
    putnum(a[x]);
    return;
}

///////////////////////  game //////////////////////////////

int generateRandomNumber(int lower, int upper) {
    return mod(rand(), (upper - lower + 1)) + lower;
}

void playGuessNumberGame() {
    int lowerBound = 1;
    int upperBound = 100;
    int targetNumber = generateRandomNumber(lowerBound, upperBound);
    int guess;
    int attempts = 0;
    int result = 0;
    vga_clear();
    putstr("Welcome to guess number game\n");
    putstr("I have generated a number between:");
    putnum(lowerBound); putch('-');
    putnum(upperBound); putch('\n');
    do {
        putstr("please enter your guess: ");
        guess = readnum();
        putch('\n');
        attempts++;
        if(guess == 114514){
            putnum(targetNumber); putch('\n');
            foo();
        } else if (guess == targetNumber) {
            putstr("Congratulate! you guess : "); 
            putnum(attempts);
            if(attempts>1) putstr("times \n");
            else putstr("time \n");
            return;
        } else if (guess < targetNumber) {
            putstr("too small \n");
        } else {
            putstr("too big! \n");
        }
    } while (guess != targetNumber);
    quit(0);
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

char WelcomePage(){
    vga_clear();
    putstr("author:"); putstr(auther_name); 
    putstr("        STUID:"); putstr(auther_stuid); 
    putch('\n');
    putch('\n');
    putch('\n');
    putstr("H   H  eeeee  ll      ll       ooooo    ||   CCCCC    M   M     DDDDD \n");
    putstr("H   H  e      ll      ll      o     o   ||  C        M M M M    D    D\n");
    putstr("HHHHH  eeeee  ll      ll      o     o   ||  C       M   M   M   D    D\n");
    putstr("H   H  e      ll      ll      o     o   ||  C       M       M   D    D\n");
    putstr("H   H  eeeee  llllll  llllll   ooooo    ||   CCCCC  M       M   DDDDD \n");
    putch('\n');
    putch('\n');
    putch('\n');
    putstr("  W       W   eeeee  ll       CCCC    ooooo      M   M    eeeee \n");
    putstr("  W   W   W   e      ll      C       o     o    M M M M   e     \n");
    putstr("  W   W   W   eeeee  ll      C       o     o   M   M   M  eeeee \n");
    putstr("  W   W   W   e      ll      C       o     o   M       M  e     \n");
    putstr("    W   W     eeeee  llllll   CCCC    ooooo    M       M  eeeee \n");
    putch('\n');
    putch('\n');
    putch('\n');
    putstr("press any key to start:\n");
    char ch = getch();
    return ch;
}

void deal_com(char * com)
{
    int flag = 0;
    if(strcmp(comhello,command)==0)
    {
        flag++;
        putstr(hellofun); 
    }
    else if(strcmp(comclear,com)==0)
    {
        flag++;
        vga_init(); 
    }
    else if(strcmp(comsort,com)==0)
    {
        flag++;
        sort();
    }
    else if(strcmp(comhelp,com)==0)
    {
        flag++;
        help();
    }
    else if(strcmp(comtimer,com)==0)
    {
        flag++;
        time();
    }
    else if(match_fib(com)){
        fib(match_fib(com));
        flag++;
    }
    else if(strcmp(comguess, com) == 0){
        flag++;
        playGuessNumberGame();
    }
    else if(cnt == 0) return;
    if(flag == 0) putstr("Invalid command!\n");
    return;
}

/////////////////////////////////// cal_switch     ////////////////// 
/*
static char enter_infix[] = "Enter an infix expression without space:\n";
struct stack_int
{
    int buff[256];
    int top_idx;
}; // 后缀表达式用于计算中间结果的栈

static struct stack_int opera; // 实例化一个栈

static void stack_int()
{
    opera.top_idx = -1;
} // 初始化栈
// 以下是栈的操作
static int empty()
{
    return (opera.top_idx == -1);
}

static int top()
{
    return opera.buff[opera.top_idx];
}

static void pop()
{
    if (opera.top_idx >= 0)
        opera.top_idx--;
}

static void push(int i)
{
    if (opera.top_idx == 255)
        return;
    opera.buff[++opera.top_idx] = i;
    return;
}

static int runtime_error;
// 以下是一些运算符的操作

int bitlength(int a)
{
    int length = 0;
    while (a)
    {
        length = length + 1;
        a = a >> 1;
    }
    return length;
}

int lengthdiff(int a, int b)
{
    return bitlength(a) - bitlength(b);
}

// 以下是在预算时用到的操作
static int positive(int a, int b)
{
    return a;
}

static int negative(int a, int b)
{
    return -a;
}

static int multiply(int a, int b)
{
    return multi(a, b);
}

static int divideby(int a, int b)
{
    if (b == 0)
    {
        runtime_error = 1;
        return 0;
    }
    return div(a, b);
}

static int reverse(int a, int b) // 按位取反
{
    return (~a);
}

static int module(int a, int b)
{
    if (b == 0)
    {
        runtime_error = 1;
        return 0;
    }
    return mod(a, b);
}

static int plus(int a, int b)
{
    return a + b;
}

static int minus(int a, int b)
{
    return a - b;
}

static int less(int a, int b)
{
    return ((a < b) ? 1 : 0);
}

static int greater(int a, int b)
{
    return ((a > b) ? 1 : 0);
}

static int (*opt[])(int, int) = { // 给操作符做标记
    [Positive] = positive,
    [Negative] = negative,
    [Reverse] = reverse,
    [Multiply] = multiply,
    [Divideby] = divideby,
    [Module] = module,
    [Plus] = plus,
    [Minus] = minus,
    [Less] = less,
    [Greater] = greater};

struct Node
{
    int flag;
    int val;
};

static struct Node postfix[20000]; // 后缀表达式
;

static char *infix; // 中缀表达式

static int getid(int position) // 相当于maketokens
{
    switch (infix[position])
    {
    case '+':
        if (position >= 1 && infix[position - 1] <= '9' && infix[position - 1] >= '0' ||
            infix[position - 1] == ')')
        {
            return Plus;
        }
        else
        {
            return Positive;
        }
    case '-':
        if (position >= 1 && infix[position - 1] <= '9' && infix[position - 1] >= '0' ||
            infix[position - 1] == ')')
        {
            return Minus;
        }
        else
        {
            return Negative;
        }
    case '*':
        return Multiply;
    case '/':
        return Divideby;
    case '%':
        return Module;
    case '~':
        return Reverse;
    case '<':
        return Less;
    case '>':
        return Greater;
    case '(':
        return LeftBracket;
    case ')':
        return RightBracket;
    default:
        return infix[position];
    }
}

static int associativity[256]; // 结合性
static int priority[256];      // 优先级
static int single[256];        // 指示单目操作符

enum
{
    LeftAssociative = 0,
    RightAssociative = 1
};

static int pn; // 指示后缀表达式长度

static void infix_to_postfix() // 中缀到后缀的转换
{
    int length = strlen(infix);
    for (int i = 0; i < length; i++)
    {
        int to_be = getid(i);
        if (to_be <= '9' && to_be >= '0')
        {
            i++;
            int temp = to_be - '0';
            while (infix[i] <= '9' && infix[i] >= '0')
            {
                temp = temp * 10 + infix[i] - '0';
                i++;
            }
            postfix[pn].flag = 1;
            postfix[pn].val = temp;
            pn++;
            i--;
        }
        else if (to_be == LeftBracket)
            push(to_be);
        else if (to_be == RightBracket)
        {
            int temp = top();
            while (temp != LeftBracket)
            {
                postfix[pn].val = temp;
                postfix[pn].flag = 0;
                pop();
                temp = top();
                pn++;
            }
            pop();
        }
        else
        {
            while ((!empty()) && (top() != LeftBracket) && (priority[top()] <= priority[to_be]) &&
                   ((priority[to_be] != priority[top()]) || (associativity[top()] != RightAssociative)))
            {
                postfix[pn].val = top();
                postfix[pn].flag = 0;
                pop();
                pn++;
            }
            push(to_be);
        }
    }
    while (!empty())
    {
        postfix[pn].val = top();
        postfix[pn].flag = 0;
        pop();
        pn++;
    }
}

static int calculate() // 计算后缀表达式
{
    for (int i = 0; i < pn; i++)
    {
        if (postfix[i].flag == 1)
        {
            push(postfix[i].val);
            continue;
        }
        else if (!single[postfix[i].val])
        {
            int temp1 = top();
            pop();
            int temp2 = top();
            pop();
            push(opt[postfix[i].val](temp2, temp1));
            continue;
        }
        else if (single[postfix[i].val])
        {
            int temp = opt[postfix[i].val](top(), 0);
            pop();
            push(temp);
            continue;
        }
        if (runtime_error == 1)
            return 0;
    }
    int answer = top();
    pop();
    return answer;
}

static void init() // 初始化，给所有操作符取定优先级
{
    associativity[Negative] = associativity[Positive] = associativity[Reverse] = RightAssociative;
    single[Negative] = single[Positive] = single[Reverse] = 1;
    priority[LeftBracket] = priority[RightBracket] = 1;
    priority[Positive] = priority[Negative] = priority[Reverse] = 2;
    priority[Multiply] = priority[Divideby] = priority[Module] = 3;
    priority[Plus] = priority[Minus] = 4;
    priority[Greater] = priority[Less] = 5;
}

static char re[] = "Runtime Error\n";
static char ans_STR[] = "Ans = ";

static void calclear()
{
    runtime_error = 0;
    pn = 0;
}

void cal_main(char *expr)
{
    calclear();
    stack_int();
    init();
    infix = expr;
    infix_to_postfix();
    int t = calculate();
    if (runtime_error)
    {
        putstr(re);
    }
    else
    {
        putstr(ans_STR);
        putnum(t);
        putch('\n');
    }
}

void cal()
{
    vga_clear();
    putstr(enter_infix);

    char tmp_str[1024], ch;
    int lenth = 0;
    while (1)
    {
        char ch = getch(tmp_str + lenth);
        if (ch == 8 && lenth > 0)
        {
            lenth--;
            continue;
        }
        if (ch == '\r')
        {
            tmp_str[lenth] = '\0';
            break;
        }
        lenth++;
    }

    cal_main(tmp_str);
}
*/

void foo(){
    putstr("░░░░░▓▓▓▓▓▓▓▓▓▓▓░░░░░░░░ \n");
    putstr("░░░▓▓▓▓▓▓▒▒▒▒▒▒▓▓░░░░░░░ \n");
    putstr("░░▓▓▓▓▒░░▒▒▓▓▒▒▓▓▓▓░░░░░ \n");
    putstr("░▓▓▓▓▒░░▓▓▓▒▄▓░▒▄▄▄▓░░░░ \n");
    putstr("▓▓▓▓▓▒░░▒▀▀▀▀▒░▄░▄▒▓▓░░░ \n");
    putstr("▓▓▓▓▓▒░░▒▒▒▒▒▓▒▀▒▀▒▓▒▓░░ \n");
    putstr("▓▓▓▓▓▒▒░░░▒▒▒░░▄▀▀▀▄▓▒▓░ \n");
    putstr("▓▓▓▓▓▓▒▒░░░▒▒▓▀▄▄▄▄▓▒▒▒▓ \n");
    putstr("░▓█▀▄▒▓▒▒░░░▒▒░░▀▀▀▒▒▒▒░ \n");
    putstr("░░▓█▒▒▄▒▒▒▒▒▒▒░░▒▒▒▒▒▒▓░ \n");
    putstr("░░░▓▓▓▓▒▒▒▒▒▒▒▒░░░▒▒▒▓▓░ \n");
    putstr("░░░░░▓▓▒░░▒▒▒▒▒▒▒▒▒▒▒▓▓░ \n");
    putstr("░░░░░░▓▒▒░░░░▒▒▒▒▒▒▒▓▓░░ \n");
    quit(0);
}