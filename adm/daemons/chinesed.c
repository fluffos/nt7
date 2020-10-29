// chinesed.c
// by Annihilator@ES
// modified by Xiang@XKX
// updated by Lonely@nitan3

// #pragma optimize
// #pragma save_binary

#include <localtime.h>

#ifndef DATA_DIR
#define DATA_DIR        "/data/"
#endif
#define E2C_DICTIONARY  DATA_DIR + "e2c_dict"

inherit F_SAVE;

// some constatns
nosave string *c_digit = ({ "零","十","百","千","万","亿","兆" });
nosave string *c_num = ({ "零","一","二","三","四","五","六","七","八","九","十" });
nosave string *c_num2 = ({ "零","壹","贰","叁","肆","伍","陆","柒","捌","玖","拾" });
nosave string *sym_tian = ({ "甲","乙","丙","丁","戊","己","庚","辛","壬","癸" });
nosave string *sym_di = ({ "子","丑","寅","卯","辰","巳","午","未","申","酉","戌","亥" });
// 最大数值单位可自由增减
// string *unit = ({ "万","亿","兆","京","垓","杼","穣","沟","涧","正","载","极","恒河沙","阿僧祇","那由它","不可思议","无量","大数" });
nosave string *unit = ({ "万","亿","兆" });

nosave mapping wei = (["十":10,"百":100,"千":1000,"万":10000,"亿":100000000]);
nosave mapping shu = (["一":1,"二":2,"三":3,"四":4,"五":5,"六":6,"七":7,"八":8,"九":9]);
nosave string zero = "零";
nosave string ten  = "十";
nosave string one  = "一";

int is_wei(string a)
{
        if(undefinedp(wei[a]))
                return 0;
        return wei[a];
}

int is_shu(string a)
{
        if(undefinedp(shu[a]))
                return 0;
        return shu[a];
}

nosave mapping cache;
mapping dict =
([
        "north"         :"北边",
        "south"         :"南边",
        "east"          :"东边",
        "west"          :"西边",
        "northwest"     :"西北边",
        "northeast"     :"东北边",
        "southwest"     :"西南边",
        "southeast"     :"东南边",
        "down"          :"楼下",
        "up"            :"楼上",
        "changan"       :"长安",
        "city"          :"扬州",
        "kaifeng"       :"开封",
        "hangzhou"      :"杭州",
        "suzhou"        :"苏州",
        "dali"          :"大理",
        "beijing"       :"北京",
]);

void add_translate(string key, string chn);
void remove_translate(string key);

string initialize(int i)
{
        if( i < 11 ) return c_num[i];
        if( i < 20 ) return "十"+c_num[i%10];
        if( i < 100 ) return c_num[i/10]+"十"+(i%10 ? c_num[i%10] : "" );
        if( i < 1000 ) return c_num[i/100]+"百"+(i%100 ? ((i%100<10?"零":0)||(i%100<20?"一":""))+initialize(i%100) : "");
}

void create()
{
        seteuid(getuid());
        restore();
        cache = allocate_mapping(0);

        /* 建立数值快取 */
        for(int i=0;i<=1000;i++)
                cache[i] = initialize(i);
}

void remove()
{
        save();
}

string chinese_number(mixed i)
{
        // 若输入参数为 integer (会 overflow)
        if( intp(i) )
        {
                if (i < 0)
                        return "负" + chinese_number(-i);
                if (i < 11)
                        return c_num[i];
                if (i < 20)
                        return c_digit[1] + c_num[i - 10];
                if (i < 100)
                {
                        if (i % 10)
                                return c_num[i / 10] + c_digit[1] + c_num[i % 10];
                        else
                                return c_num[i / 10] + c_digit[1];
                }
                if (i < 1000)
                {
                        if (i % 100 == 0)
                                return c_num[i / 100] + c_digit[2];
                        else if (i % 100 < 10)
                                return c_num[i / 100] + c_digit[2] +
                                c_num[0] + chinese_number(i % 100);
                        else if (i % 100 < 10)
                                return c_num[i / 100] + c_digit[2] +
                                c_num[1] + chinese_number(i % 100);
                        else
                                return c_num[i / 100] + c_digit[2] +
                                chinese_number(i % 100);
                }
                if (i < 10000)
                {
                        if (i % 1000 == 0)
                                return c_num[i / 1000] + c_digit[3];
                        else if (i % 1000 < 100)
                                return c_num[i / 1000] + c_digit[3] +
                                c_num[0] + chinese_number(i % 1000);
                        else
                                return c_num[i / 1000] + c_digit[3] +
                                chinese_number(i % 1000);
                }
                if (i < 100000000)
                {
                        if (i % 10000 == 0)
                                return chinese_number(i / 10000) + c_digit[4];
                        else if (i % 10000 < 1000)
                                return chinese_number(i / 10000) + c_digit[4] +
                                c_num[0] + chinese_number(i % 10000);
                        else
                                return chinese_number(i / 10000) + c_digit[4] +
                                chinese_number(i % 10000);
                        }
                if (i < 1000000000000)
                {
                        if (i % 100000000 == 0)
                                return chinese_number(i / 100000000) + c_digit[5];
                        else if (i % 100000000 < 1000000)
                                return chinese_number(i / 100000000) + c_digit[5] +
                                c_num[0] + chinese_number(i % 100000000);
                        else
                                return chinese_number(i / 100000000) + c_digit[5] +
                                chinese_number(i % 100000000);
                }
                if (i % 1000000000000 == 0)
                        return chinese_number(i / 1000000000000) + c_digit[6];
                else
                if (i % 1000000000000 < 100000000)
                        return chinese_number(i / 1000000000000) + c_digit[6] +
                        c_num[0] + chinese_number(i % 1000000000000);
                else
                        return chinese_number(i / 1000000000000) + c_digit[6] +
                        chinese_number(i % 1000000000000);
            }
            // 若输入参数为 string (无限位数处理)
        else if( stringp(i) && i != "")
        {
                   int j, k, *n=({}), usize = sizeof(unit);
                string *u=({""});
                string msg;

                if( i[0] == '-' ) return "负" + chinese_number(i[1..]);

                // 将数字依四位数拆解
                while( (msg = i[<(j+=4)..<(j-3)])!="" )
                {
                        n += ({ to_int(msg) });
                        if( j != 4 ) u += ({ unit[k++%usize] });
                }

                j = k = sizeof(n);

                while(j--)
                        if( n[j] ) msg += (j+1<k ? (n[j+1] && n[j]>999 ? chinese_number(n[j]):"零"+chinese_number(n[j])):chinese_number(n[j])) + u[j];
                        else if( u[j] == unit[usize-1] ) msg += unit[usize-1];

                return msg;
        }
        else return "错误数值";
}

nomask string chinese_period(int t)
{
        int y, n, d, h, m, s;
        string time="";

        s = t %60;
        m = t /60%60;
        h = t /60/60%24;
        d = t /60/60/24%30;
        n = t /60/60/24/30%13;
        y = t /60/60/24/30/13;

        if(y) time = cache[y] + "年又";
        if(n) time += cache[n] + "个月"                + (y?"":"又");
        if(d) time += cache[d] + "天"                + (n||y?"":"又");
        if(h) time += cache[h] + "小时"                + (d||n||y?"":"又");
        if(m) time += cache[m] + "分"                + (h||d||n||y?"":"又");

        return time+cache[s]+"秒";
}

int chinese_to_number(mixed chinese)
{
        /*
        int i, len, num, idx;

        if( intp(chinese) ) return chinese;

        if( !stringp(chinese) )
                return 0;

        len = sizeof(chinese);

        num = 0;
        for(i=0;i<len;i+=2)
        {
                idx = member_array(chinese[i..i+1], c_num);

                if( idx == -1 )
                        idx = member_array(chinese[i..i+1], c_num2);

                if( idx == -1 )
                        continue;

                if( idx == 10 )
                {
                        if( i!=0 )
                                continue;
                        else if(i+2!=len)
                                idx = 1;
                }

                num = num*10 + idx;
        }
        if( chinese[len-2..] == "十" )
                num = num*10;
        else if( chinese[len-2..] == "百" )
                num = num*100;
        else if( chinese[len-2..] == "千" )
                num = num*1000;
        else if( chinese[len-2..] == "万" )
                num = num*10000;
        return num;
        */
        mixed arr = ({});
        mixed arr_shu = ({});
        mixed arr_wei = ({});
        string tmp;
        int i,j,k,sz;
        int tmpn;
        int num,num2;

        if( intp(chinese) ) return chinese;

        if( !stringp(chinese) )
                return 0;

        sz = strlen(chinese);
        for(i=0;i<sz;i+=2) {
                arr += ({chinese[i..i+1]});

        }
        if(arr[0] == ten) {
                arr = ({one}) + arr;
        }
        arr -= ({zero});
        sz = sizeof(arr);
        for(i=0;i<sz;i++) {
                tmp = arr[i];
                if(tmpn = is_shu(tmp)) {
                        arr_shu += ({tmpn});
                } else {
                        if(tmpn = is_wei(tmp)) {
//                              if(sizeof(arr_shu) > sizeof(arr_wei)) {
//                                      arr_wei += ({tmpn});
//                              } else {
                                        if(!sizeof(arr_wei)) {
                                                arr_wei += ({tmpn});
                                                continue;
                                        }

                                        for(j=sizeof(arr_wei)-1;j>=0;j--) {
                                                if(arr_wei[j]>tmpn)
                                                        break;
                                        }
                                        j = j+1;
                                        num2 = 0;
                                        for(k=j;k<sizeof(arr_shu);k++) {
                                                if(k<sizeof(arr_wei)) {
                                                        num2 += arr_shu[k]*arr_wei[k];
                                                } else {
                                                        num2 += arr_shu[k];
                                                }
                                        }
                                        for(k=j;k<sizeof(arr_shu);k++) {
                                                arr_shu[k] = 0;
                                        }
                                        arr_shu -= ({0});

                                        for(k=j;k<sizeof(arr_wei);k++) {
                                                arr_wei[k] = 0;
                                        }
                                        arr_wei -= ({0});
                                        if(tmpn == 10 && num2 == 0) {
                                                arr_shu += ({1});
                                                arr_wei += ({tmpn});
                                        } else {
                                                arr_shu += ({num2});
                                                arr_wei += ({tmpn});
                                        }
//                              }
                        }
                }
        }
        num = 0;
        sz = sizeof(arr_shu);
        for(i=0;i<sz;i++) {
                if(i<sizeof(arr_wei)) {
                        num += arr_shu[i]*arr_wei[i];
                } else {
                        num += arr_shu[i];
                }
        }
        return num;
}

string query_save_file()
{
        return E2C_DICTIONARY;
}

string chinese(string str)
{
        if (! undefinedp(dict[str]))
                return dict[str];
        else
                return str;
}

string to_chinese(string idx)
{
        return chinese(idx);
}

string find_skill(string value)
{
        string *english;
        string key;

        english = keys(dict);
        foreach (key in english)
        {
                if (dict[key] == value)
                        return key;
        }
        return 0;
}

void remove_translate(string key)
{
        map_delete(dict, key);
        save();
}

void add_translate(string key, string chn)
{
        dict[key] = chn;
        save();
}

void dump_translate()
{
        string *k;
        string str;
        int i;

        str = "";
        k = keys(dict);
        for (i = 0; i < sizeof(k); i++)
                str += sprintf("%-30s %s\n", k[i], dict[k[i]]);
        write_file("/CHINESE_DUMP", str);
}

string cctime(int date)
{
        int year;
        int mon;
        int mday;
        int wday;
        int hour;
        int min;
        int sec;

        mixed lt;
        lt = localtime(date);
        sec = lt[LT_SEC];
        min = lt[LT_MIN];
        hour = lt[LT_HOUR];
        mday = lt[LT_MDAY];
        wday = lt[LT_WDAY];
        mon = lt[LT_MON] + 1;
        year = lt[LT_YEAR];
        return sprintf("%d年%d月%d日 %d时%d分%d秒", year, mon, mday, hour, min, sec);
}

string chinese_date(int date)
{
        mixed *local;

        if (date <=0) date=1;
        local = localtime(date);

        return sprintf("%s%s年%s月%s日%s时%s刻",
                sym_tian[local[LT_YEAR] % 10], sym_di[local[LT_YEAR] % 12],
                chinese_number(local[LT_MON] + 1),
                chinese_number(local[LT_MDAY] + (local[LT_HOUR] > 23 ? 1 : 0)),
                sym_di[((local[LT_HOUR] + 1) % 24) / 2],
                chinese_number((local[LT_MIN]+1) % 2 * 2 +
                local[LT_MIN] / 30 + 1) );
}

//Used in natured.c to as a condition to judge which season should be
//to use different weather discription.
string chinese_month(int date)
{
        return chinese_number(NATURE_D->query_month());
}

string chinese_monthday(int date)
{
        mixed *local;
        local = NATURE_D->query_localtime(date);
        return sprintf("%s月%s日",
                       chinese_number(local[LT_MON] + 1),
                       chinese_number(local[LT_MDAY]));
}

//end of appendance
int check_control(string name)
{
        int i;
        if (! name) return 0;

        i = strlen(name);
        while(i--)
        {
                if (name[i] == ' ' || name[i] == '\n')
                        continue;

                if (name[i] < ' ')
                        return 1;
        }
        return 0;
}

int check_space(string name)
{
        int i;
        if (! name) return 0;

        i = strlen(name);
        while(i--)
        {
                if (name[i]== ' ')
                        return 1;
        }
        return 0;
}

int check_return(string name)
{
        int i;
        if (! name) return 0;

        i = strlen(name);
        while(i--)
        {
                if (name[i]== '\n')
                        return 1;
        }
        return 0;
}

int check_chinese(string name)
{
        return is_chinese(name);
}

int check_length(string str)
{
        if (! str) return 0;
        return strlen(filter_color(trans_color(str, 3), 1));
}

string itoa(int i)
{
        string str;

        if(!intp(i)) return "NULL";
        str=sprintf("%d",i);
        return str;
}

string chinese_time(int type,string get_time)
{
/* 不要使用localtime来传递get_time，使用ctime(time())就是正确的了！
在求当前时间时用localtime是无所谓，但是要转换一个时间还是ctime好点！*/

        string e_time, week, month, year;
        string c_week, c_year, c_month, c_time;
        int day, hour, minute, second;
        string *month_name = ({"Jan","Feb","Mar","Apr","May","Jun","Jul",
                "Aug","Sep","Oct","Nov","Dec"});
        string *week_name = ({"Mon","Tue","Wed","Thu","Fri","Sat","Sun"});

        if ( stringp(get_time) )
                e_time = get_time;
        else e_time = ctime(time());

        // e_time must is ctime(time string) like "Sun May  3 00:52:12 1998"
        sscanf(e_time,"%s %s %d %d:%d:%d %s", week, month, day, hour, minute, second, year);

        c_week  = chinese_number(member_array(week, week_name) + 1);
        c_month = chinese_number(member_array(month, month_name) + 1);

        c_year  = sprintf("%s%s%s%s",
                chinese_number(year[0]-48),
                chinese_number(year[1]-48),
                chinese_number(year[2]-48),
                chinese_number(year[3]-48));

        c_year =c_year +"年";
        c_month  = c_month + "月";
        if(c_week=="七")
        c_week="日";

        c_week = " 星期"+c_week;

        c_time = chinese_number(day) + "日";
        c_time += chinese_number(hour) + "点";
        c_time += chinese_number(minute) + "分";
        // maybe not need srcond to show
        // c_time += chinese_number(second) + "秒";

        if (type) {
                switch( type ) {
                        case 1: return c_year+c_month+c_time+c_week;
                        case 2: return c_year+c_month+c_time;
                        case 3: return c_month+c_time+c_week;
                        case 4: return c_month+c_time;
                        case 5: return year+"年"+(member_array(month, month_name) + 1)+
                                "月"+day+"日"+hour+"点"+minute+"分";
                        case 6: return (member_array(month, month_name) + 1)+
                                "月"+day+"日"+hour+"点"+minute+"分";
                        case 7: {
                                return sprintf("%s/%s/%s",year,
                                strlen(itoa(member_array(month, month_name) + 1))<=1?
                                ("0"+itoa(member_array(month, month_name)+1)):itoa(member_array(month, month_name) + 1),
                                strlen(itoa(day))<=1?"0"+itoa(day):itoa(day),);
                        }
                        case 8: {
                                return sprintf("%s/%s/%s",year[2..4],
                                strlen(itoa(member_array(month, month_name) + 1))<=1?
                                ("0"+itoa(member_array(month, month_name)+1)):itoa(member_array(month, month_name) + 1),
                                strlen(itoa(day))<=1?"0"+itoa(day):itoa(day),);
                        }
                        case 9: {
                                return sprintf("%s/%s/%s %s",year,
                                strlen(itoa(member_array(month, month_name) + 1))<=1?
                                ("0"+itoa(member_array(month, month_name)+1)):itoa(member_array(month, month_name) + 1),
                                strlen(itoa(day))<=1?"0"+itoa(day):itoa(day),e_time[11..15]);
                        }

                        default: return c_year+c_month+c_time+c_week;
                }
        }
        return c_year+c_month+c_time+c_week;
}
