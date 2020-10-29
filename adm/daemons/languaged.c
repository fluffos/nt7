// languaged.c
//
//        GB <-> Big5
//
// Kenny@EC (1998/3/21)
// (Ported from @(#)$Id: ccf.c,v 1.2 1994/04/30 19:49:36 shin Exp shin $)

// #define LANGUAGE_D        "/adm/daemons/languaged.c" at globals.h
// Ported to by ken@chinesemud.net at 1998/05/18

// #pragma optimize
// #pragma save_binary

#include <ansi.h>
//inherit F_CLEAN_UP;

#define B2G_TAB                CONFIG_DIR+"language/BtoG.tab"
#define G2B_TAB                CONFIG_DIR+"language/GtoB.tab"

#define B2G                0
#define G2B                1

#define B2G_bad1        0xa1
#define B2G_bad2        0xf5
#define G2B_bad1        0xa1
#define G2B_bad2        0xbc

#define is_GB1(x)       ((x)>=0xa1 && (x)<=0xf7)
#define is_GB2(x)       ((x)>=0xa1 && (x)<=0xfe)
#define is_B51(x)       ((x)>=0xa1&&(x)<=0xfe)
#define is_B52(x)       (((x)>=0x40 && (x)<=0x7e) || ((x)>=0xa1 && (x)<=0xfe))

private int G2B_cols, B2G_cols;
private mapping B2G_Cache=([]),
                G2B_Cache=([]);



#define is_ZH(x)    ((x)>=0xa1&&(x)<=0xfe)

#define is_B5maj(x) ((x)>=0x40&&(x)<=0x7e) //100%
#define is_B5min(x) ((x)>=0xa1&&(x)<=0xfe) //40%
#define is_GB(x)    ((x)>=0xa1&&(x)<=0xfe) //60%

/*
        推测一字串为Big5码的可能性(百分比机率)
        低于20%的百分比就几乎可确定为GB码
        判断的正确度与字串长度呈正比
 */
int encode_conjecture(string arg)
{
        int i, poss=0, size;
        float gbposs=0.;

        if( !arg || !arg[0] ) return -1;

        size = sizeof(arg);

        for(i=0;i<size;i++)
        {
                if( !is_ZH(arg[i]) ) continue;

                i++;poss++;

                if( i<size&&!is_B5maj(arg[i]) )
                {
                        if( is_GB(arg[i]) )
                        {
                                gbposs+=0.6;
                                continue;
                        }
                        i--; poss--;
                }
                gbposs-=0.4;
        }

        return poss ? to_int(exp(-gbposs/poss)*100)*2-100 : -1;
}

/*
        自动判别编码并传回采用Big5码之字串
        仅适用于长度较长之字串, 判别率较高
string auto_G2B(string arg)
{
        int con = encode_conjecture(arg);

        if( con > 0 && con < 20) return G2B(arg);
        return arg;
}
*/

private int Fetch(int key, int flag)
{
        int    col_limit=flag? G2B_cols: B2G_cols,
               col = key%col_limit;
        string buf, file=flag? G2B_TAB: B2G_TAB;

        if (flag && G2B_Cache[key]) return G2B_Cache[key];
        if (!flag && B2G_Cache[key]) return B2G_Cache[key];

        if (buf = read_file(file, key/col_limit+1, 1))
        {
                string *field = explode(buf, ",");

                if (col < sizeof(field))
                {
                        int value;

                        sscanf(field[col], "%x", value);
                        if (flag) G2B_Cache[key] = value;
                        else B2G_Cache[key] = value;
                        return value;
                } // if
        } // if
        return 0;
} // Fetch()


private int *g2b(int c1, int c2)
{
        int i;

        if ((c2>=0xa1) && (c2<=0xfe))
        {
                if ((c1>=0xa1) && (c1<=0xa9))
                {
                        i = ((c1-0xa1)*94 + (c2-0xa1)) * 2;
                        return ({ Fetch(i++, G2B), Fetch(i, G2B) });
                } // if
                else if ((c2>=0xa1) && (c2<=0xfe))
                {
                        i = ((c1-0xb0+9)*94 + (c2-0xa1)) * 2;
                        return ({ Fetch(i++, G2B), Fetch(i, G2B) });
                } // if
        } // if
        return ({ G2B_bad1, G2B_bad2 });
} // g2b()


private int *b2g(int c1, int c2)
{
        int i;

        if ((c1 >= 0xa1) && (c1 <= 0xf6))
        {
                if ((c2 >= 0x40) && (c2 <= 0x7e))
                {
                        i = ((c1 - 0xa1) * 157 + (c2 - 0x40)) * 2;
                        return ({ Fetch(i++, B2G), Fetch(i, B2G) });
                } // if
                else if ((c2 >= 0xa1) && (c2 <= 0xfe))
                {
                        i = ((c1 - 0xa1) * 157 + (c2 - 0xa1) + 63) * 2;
                        return ({ Fetch(i++, B2G), Fetch(i, B2G) });
                } // if
        } // if
        else if ((c1 == 0xf7) && (c2 >= 0x40) && (c2 <= 0x55))
        {
                i = ((c1 - 0xa1) * 157 + (c2 - 0x40)) * 2;
                return ({ Fetch(i++, B2G), Fetch(i, B2G) });
        } // if
        return ({ B2G_bad1, B2G_bad2 });
} // b2g()


string GB2Big5(string src)
{
        string str=src;                        // duplicate string
        int    len=strlen(str);

        for (int i=0; i<len;)
                if (is_GB1(str[i]) && is_GB2(str[i+1]))
                {
                        int *code=g2b(str[i], str[i+1]);
                        str[i] = code[0];
                        str[i+1] = code[1];
                        i += 2;
                } // if
                else        i++;
        return str+"";                        // assure string
} // GB2Big5()


string Big52GB(string src)
{
        string str=src;                        // duplicate string
        int    len=strlen(str);

        for (int i=0; i<len;)
                if (is_B51(str[i]) && is_B52(str[i+1]))
                {
                        int *code=b2g(str[i], str[i+1]);
                        str[i] = code[0];
                        str[i+1] = code[1];
                        i += 2;
                } // if
                else        i++;
        return str+"";                        // assure string
} // Big52GB()

string *Get_Point(int num,string SHZK1616)
{
        string point_buf1,point_buf2;
        string *the_point=({});
        int *mark=({
                0x80,
                0x40,
                0x20,
                0x10,
                0x08,
                0x04,
                0x02,
                0x01,
        });
        int i,j;
        string line="";

        point_buf1 = read_bytes(SHZK1616,32*num,16);
        point_buf2 = read_bytes(SHZK1616,32*num+16,16);
        for(i=0; i<16; i++)
        {
                for(j=0; j<8; j++)
                        if ((point_buf1[i] & mark[j]) == 0)
                                line += "b";
                        else
                                line += "q";
                for(j=0; j<8; j++)
                        if ((point_buf2[i] & mark[j]) == 0)
                                line += "b";
                        else
                                line += "q";
                the_point+=({line});
                line = "";
        }
        return the_point;                        // assure string
}

string Get_Point_Index(int num,string SHZK1616)
{
        return read_bytes(SHZK1616,100*32+num*2,2);
}

string toBig5(string str)
{
        if (!stringp(str)) return 0;
        return GB2Big5(str);
} // toBig5()

string toGB(string str)
{
        if (!stringp(str)) return 0;
        return Big52GB(str);
} // toGB()

string input(string str, object me)
{
            if (! str || ! me)
                return str;

            if (query_temp("big5", me))
            {
                return toGB(str);
                // toGB()
            }
            return str;
}

string output(string str, object me)
{
            if (! str || ! me)
                return str;
            if (query_temp("big5", me))
            {
                return GB2Big5(str);
                // toBig5()
            }
            return str;
}

void create()
{
        string buf;

        seteuid(getuid());
        if (buf = read_file(B2G_TAB, 1, 1))
                B2G_cols = sizeof(explode(buf, ","))-1;
        if (buf = read_file(G2B_TAB, 1, 1))
                G2B_cols = sizeof(explode(buf, ","))-1;
} // create()

string query_name()
{
        return "语言系统(LANGUAGE_D)";
}
