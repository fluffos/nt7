
string chinese_number(int i)
{
    return CHINESE_D->chinese_number(i);
}

string to_chinese(string str)
{
    return CHINESE_D->chinese(str);
}

int is_chinese(string str)
{
    /*        int i;

        if( strlen(str) < 2 ) return 0;

        for( i = 0; i < strlen(str); i++ ) {
                if( str[i] < 161 || str[i] == 255 ) return 0;
                if( !(i % 2) && (str[i] < 176 || str[i] >= 248) ) return 0;
        }

        return 1;*/
    if (!str)
        return 0;
    str = remove_ansi(str);
    return pcre_match(str, "^\\p{Han}+$");
}

int is_chinese2(string str)
{
    if (strlen(str) < 2)
        return 0;
    if (str[0] < 176 || str[0] > 247)
        return 0;
    if (str[1] < 161 || str[1] > 254)
        return 0;
    if (str[0] == 215 && str[1] > 249)
        return 0;
    return 1;
}

int is_english(string str)
{
    if (!str || !str[0])
        return 0;

    foreach (int a in remove_ansi(str))
        if (a != ' ' && (a < 'a' || a > 'z') && (a < 'A' || a > 'Z'))
            return 0;

    return 1;
}
string time_period(int time)
{
    int t, d, h, m, s;
    string str;

    t = time;
    s = t % 60;
    t /= 60;
    m = t % 60;
    t /= 60;
    h = t % 24;
    t /= 24;
    d = t;

    if (d)
        str = chinese_number(d) + "天";
    else
        str = "";

    if (h)
        str += chinese_number(h) + "小时";
    if (m)
        str += chinese_number(m) + "分";
    str += chinese_number(s) + "秒";

    return str;
}
