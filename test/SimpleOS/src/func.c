#include "func.h"
#include "calculator.h"

static char hello_str[] = "Hello world!\n";
static char enter_num[] = "Enter a positive number:";
static char ans_str[] = "Ans = ";
static char enter_infix[] = "Enter an infix expression without space:\n";

static int atoi(char *str)
{
    int result = 0;
    int sign = 0;
    // proc whitespace characters
    while (*str == ' ' || *str == '\t' || *str == '\n')
        ++str;

    // proc sign character
    if (*str == '-')
    {
        sign = 1;
        ++str;
    }
    else if (*str == '+')
    {
        ++str;
    }

    // proc numbers
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + *str - '0';
        ++str;
    }

    // return result
    if (sign == 1)
        return -result;
    else
        return result;
}

void hello()
{
    putstr(hello_str, 0xff);
}

void fib()
{
    putstr(enter_num, 0xfff);

    char tmp_str[16], ch;
    int lenth = 0;
    while (1)
    {
        char ch = getch(tmp_str + lenth);
        if (ch == 8 && lenth > 0)
        {
            lenth--;
            continue;
        }
        if (ch == '\n')
        {
            tmp_str[lenth] = '\0';
            break;
        }
        lenth++;
    }

    int n = atoi(tmp_str);

    if (n == 1 || n == 2)
        putch('1');

    n = n - 2;
    int x = 1, y = 1, tmp;
    while (n--)
    {
        tmp = x;
        x = y;
        y = tmp + y;
    }
    putstr(ans_str, 0xfff);
    putnum(y);
    putch('\n');
}

static char hour[] = "hour(s) ";
static char minute[] = "minute(s) ";
static char second[] = "second(s) ";

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
    putstr(hour, 0xfff);
    putch(' ');
    putnum(min);
    putch(' ');
    putstr(minute, 0xfff);
    putch(' ');
    putnum(sec);
    putch(' ');
    putstr(second, 0xfff);

    putch('\n');
    return;
}

void clear()
{
    vga_clear();
}

void cal()
{
    putstr(enter_infix, 0xfff);

    char tmp_str[1024], ch;
    int lenth = 0;
    while (1)
    {
        char ch = getch(tmp_str + lenth);
        if (ch == 8)
        {
            if (lenth > 0)
            {
                lenth--;
            }
            continue;
        }
        if (ch == '\n')
        {
            tmp_str[lenth] = '\0';
            break;
        }
        lenth++;
    }

    cal_main(tmp_str);
}

int arr[64];
void sort()
{
    char tembuf[128];
    int length = 0;
    while (1)
    {
        char ch = getch(tembuf + length);
        if (ch == 8)
        {
            if (length > 0)
            {
                length--;
                continue;
            }
        }
        if (ch == '\n')
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
    realsort(arr, num);
    for (int i = 0; i < num; i++)
    {
        putnum(arr[i]);
        putch(' ');
    }
    putch('\n');
}

void realsort(int *a, int num)
{
    for (int i = 0; i < num; i++)
    {
        for (int j = i + 1; j < num; j++)
        {
            if (a[j] < a[i])
            {
                int temp = a[j];
                a[j] = a[i];
                a[i] = temp;
            }
        }
    }
}

void help()
{
    putstr("===================COMMAND HELP=======================\n", 0x00f);
    putstr("help     : print COMMAND HELP\n", 0x00f);
    putstr("hello    : print hello\n", 0x00f);
    putstr("time     : print time\n", 0x00f);
    putstr("fib n    : calculate fib(n)\n", 0x00f);
    putstr("cal expr : calculate expression\n", 0x00f);
    putstr("clear    : clear the screen\n", 0x00f);
    putstr("g2048    : play the game 2048\n", 0x00f);
    putstr("snake    : play the game snake\n", 0x00f);
    putstr("======================================================\n", 0x00f);
}

int score = 0;
int k = 0;
int seed = 0;

void srand()
{
    seed = 41;
}

int rand()
{
    seed = ((seed * 214013 + 2531011) >> 16) & 0x7fff;
    if (seed == 41)
        seed = 40;
    return seed;
}

void order(int end, int i, int v, int map[])
{
    for (int begin = end == 16 ? 0 : 15; begin - end; begin += i)
        move(begin, v, map);
}

void move(int i, int v, int map[])
{
    if (i + v < 0 || 15 < i + v || !map[i])
        return;
    if ((v == 1 || v == -1) && i / 4 - (i + v) / 4)
        return;
    if (map[i + v] == map[i])
    {
        map[i + v] *= -2;
        score += map[i];
        map[i] = k = 0;
    }
    if (!map[i + v])
    {
        map[i + v] = map[i];
        map[i] = k = 0;
        move(i + v, v, map);
    }
}

void g2048()
{
    int map[16];
    score = 0;
    k = 0;
    seed = 0;
    for (int i = 0; i <= 15; i++)
        map[i] = 0;
    int game = 1, i, j;
    char c;
    const char *wall[4] = {"\n----- ----- ----- -----\n", "|", "|", "|"};
    for (srand(),
         c = '0', j = 0;
         game; j = k = 1, c = getche())
    {
        if (c == 'a' || c == 'w')
            order(16, 1, c == 'a' ? -1 : -4, map);
        else if (c == 'd' || c == 's')
            order(-1, -1, c == 'd' ? 1 : 4, map);
        else if (c == 'q')
        {
            vga_init();
            return;
        }
        for (i = 0; i < 16; i++)
        {
            if (map[i] < 0)
                map[i] = -map[i];
            // map[i] || (j = 0);
            if (map[i] == 0)
                j = 0;
        }
        do
            if (i = rand() % 16, j || k)
                break;
        while (map[i] || (map[i] = rand() % 5 ? 2 : 4, 0));
        vga_init();
        for (i = 0; j && (i < 15 || (game = 0)); i++)
            if ((i < 12 && map[i] == map[i + 4]) ||
                (((i + 1) & 3) && map[i] == map[i + 1]))
                break;
        if (!game)
        {
            char x[] = "Game over!";
            putstr(x, 0xfff);
        }
        else
        {
            // cout << "score:" << score;
            char x[] = "score: ";
            putstr(x, 0xfff);
            putnum(score);
        }
        for (i = 0; i < 16; i++)
        {
            //	cout << wall[i & 3] <<"    "<< map[i];
            putstr(wall[i & 3], 0xfff);
            char x[] = "     ";
            char x1[] = "    ";
            char x2[] = "   ";
            char x3[] = "  ";
            char x4[] = " ";
            char x5[] = "";

            if (map[i] > 10000)
                putstr(x5, 0xfff);
            else if (map[i] > 1000)
                putstr(x4, 0xfff);
            else if (map[i] > 100)
                putstr(x3, 0xfff);
            else if (map[i] > 10)
                putstr(x2, 0xff0);
            else if (map[i] > 0)
                putstr(x1, 0x0ff);
            else
                putstr(x, 0x0ff);
            putnum(map[i]);
        }
        if (!game)
        {
            putch('\n');
        }
    }
}

void sleep()
{
    int t = get_time();
    int c = get_time();
    while (t + 100 >= c)
        c = get_time();
    return;
}

void snake()
{
    int W = 20, S = W * W, z[2] = {0}, l = 3, i, *p, f;
    char C;
    char c = 'D';
    int m[1000];
    for (int i = 0; i < S; i++)
        m[i] = 0;
    for (C = m[1] = -1; C - 27; sleep())
    {
        if (!(*(char *)kbd_empty))
        {
            char t = getche();
            C = t & 95;
            C - 65 && C - 68 && C - 83 && C - 87 || (C ^ c) & 20 ^ 4 && (c = C);
            if (t == 'q')
            {
                vga_init();
                return;
            }
        }
        p = z + !!(c & 2);
        *p += c / 3 & 2;
        *p = (--*p + W) % W;
        f = 1;
        vga_init();
        *(p = m + *z + z[1] * W) > 0 && (C = 27);
        for (; *p && (m[i = rand() % S] || (--m[i], ++l, --f));)
            ;
        for (i = 0, *p = l; i < S;)
        {

            if (m[i] > 0)
            {
                m[i] -= f;
                char tmp[] = "()";
                putstr(tmp, 0xfff);
            }
            else if (m[i])
            {
                char tmp[] = "00";
                putstr(tmp, 0xfff);
            }
            else
            {
                char tmp[] = "  ";
                putstr(tmp, 0x0ff);
            }

            if (!(++i % W))
            {
                char tmp[] = "|\n";
                putstr(tmp, 0xfff);
            }
        }
    }
}