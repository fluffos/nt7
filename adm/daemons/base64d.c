/****************************************
 * base64_d.c                           *
 *                                      *
 * BASE64 编码和解码。我是为了 ESMTP 协 *
 * 议的认证信息写的这个玩意，因为我们是 *
 * 要用的。                             *
 *                                      *
 * by Find@TX.                          *
 ****************************************/

#define IN_TEST

protected string base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
protected string four_to_three(string base);
protected string three_to_four(string asc);

void create()
{
        seteuid(getuid());
}

/* 对传入的字符串进行 BASE64 编码 */
string encode(string ascii)
{
        int l,b;
        string out = "";

#ifndef IN_TEST
        if( previous_object()
        && (geteuid(previous_object()) != ROOT_UID))
                return "";
#endif

        if(!stringp(ascii) || ascii == "")
                return "";

        l = strlen(ascii);

        b = l/3;
        if(l%3)
                b++;

        for(int i=0;i<b;i++)
        {
                int start = i*3;

                if( (start+2) > l )
                        out += three_to_four(ascii[start..]);
                else
                        out += three_to_four(ascii[start..(start+2)]);
        }

        return out;
}

/* 对传入的 BASE64 编码字符串进行解码 */
string decode(string b64)
{
        int l,b;
        string out = "";

#ifndef IN_TEST
        if( previous_object()
        && (geteuid(previous_object()) != ROOT_UID))
                return "";
#endif

        if(!stringp(b64) || b64 == "")
                return "";

        l = strlen(b64);

        if( l%4 )        // 错误！
                return "";

        b = l/4;

        for(int i=0;i<b;i++)
        {
                int start = i*4;

                out += four_to_three(b64[start..(start+3)]);
        }

        return out;
}

protected string four_to_three(string base)
{
        string out;
        int a1,a2,a3,a4,end,o1,o2,o3,n;

        if( strlen(base) != 4)
                return "";

        a1 = strsrch(base64,base[0..0]);
        a2 = strsrch(base64,base[1..1]);
        if(base[2] != '=')
        {
                a3 = strsrch(base64,base[2..2]);
                if(base[3] != '=')
                        a4 = strsrch(base64,base[3..3]);
                else
                        n = 2;
        }
        else
                n = 1;

        end = (a1<<6)|a2;
        end = (end<<6)|a3;
        end = (end<<6)|a4;

        o1 = end>>16;
        o2 = (end>>8)&255;
        o3 = end&255;

        if(n == 1)
                out = sprintf("%c",o1);
        else if( n == 2 )
                out = sprintf("%c%c",o1,o2);
        else
                out = sprintf("%c%c%c",o1,o2,o3);

        return out;
}

protected string three_to_four(string asc)
{
        int a1,a2,a3,end,o1,o2,o3,o4,n;
        string out;

        if(!stringp(asc) || asc =="")
                return "";
        n = strlen(asc);

        a1 = asc[0];
        if( n > 1 )
                a2 = asc[1];
        if( n > 2 )
                a3 = asc[2];

        end = (a1<<8)|a2;
        end = (end<<8)|a3;

        o1 = end>>18;
        o2 = (end>>12)&63;
        o3 = (end>>6)&63;
        o4 = end&63;

        if( n == 1 )
                out = sprintf("%c%c==",base64[o1],base64[o2]);
        else if( n == 2 )
                out = sprintf("%c%c%c=",base64[o1],base64[o2],base64[o3]);
        else
                out = sprintf("%c%c%c%c",base64[o1],base64[o2],base64[o3],base64[o4]);

        return out;
}