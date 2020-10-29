// This program is a part of NITAN MudLIB
// /adm/daemons/x_pointd.c 点阵任务守护程序

#include <ansi.h>
#include <x_point.h>

#define is_GB1(x)       ((x)>=0xa1 && (x)<=0xf7)
#define is_GB2(x)       ((x)>=0xa1 && (x)<=0xfe)

public string make_msg(mapping num);                        //数字点阵
public string make_chn_msg(mapping num);                    //中文点阵
public mapping get_question();                              //点阵产生
public string *trouble(string *str_point);                  //点阵干扰
public string make_mask(string msg, string arg, int i);     //点阵遮罩
public string *Get_Point(string src);                       //点阵取值

//数字点阵
public string make_msg(mapping num)
{
    int x;
    int i1 = random(2);
    int i2 = random(2);
    int i3 = random(2);
    int i4 = random(2);
    int i5 = random(2);
//  int i6 = random(2);
    int *i_num = ({ i1, i2, i3, i4, i5 });
    string msg = "\n";
    string get_msg;

    x = random(2);
    reset_eval_cost();
    for(int i = 0; i < 7; i++)
    {
        for(int j = 1; j <= 5; j++)
        {
            get_msg = "";
            if(x == 1)
                get_msg += sprintf("%s", "BJ●"NOR);
            get_msg += sprintf("%s%s",
                       numbers[atoi(num["num"+j])][i],
                       (i_num[j-1]) ? "BJ●"NOR : "BJ●●"NOR);

            get_msg = replace_string(get_msg,"BJ", num["bjcolor"+j]);
            get_msg = replace_string(get_msg,"QJ", num["qjcolor"+j]);
            msg += get_msg;
        }
        msg += "\n";
    }

    msg = make_mask(msg, "●", 7*7*5);
    return msg;
}

//中文点阵
public string make_chn_msg(mapping num)
{
    int x, y;
    int i1 = random(2);
    int i2 = random(2);
    int *i_num = ({ i1, i2 });
    string *the_point1 = ({});
    string *the_point2 = ({});
    string msg = "\n";
    string get_msg1, get_msg2;

    the_point1 = Get_Point(num["num1"]);
    if(!the_point1)
        log_file("static/chn_num",
            sprintf("这个汉字没有取到点阵：%s，请仔细查看\n", num["num1"]));

    the_point2 = Get_Point(num["num2"]);
    if(!the_point2)
        log_file("static/chn_num",
            sprintf("这个汉字没有取到点阵：%s，请仔细查看\n", num["num2"]));

//    the_point1 = trouble(the_point1);
//    the_point2 = trouble(the_point2);

    x = random(2);
    y = random(2);
    reset_eval_cost();
    for(int i = 0 ; i < 16 ; i++)
    {
        the_point1[i] = replace_string(the_point1[i], "b", "BJ●"NOR);
        the_point1[i] = replace_string(the_point1[i], "q", "QJ●"NOR);
        the_point2[i] = replace_string(the_point2[i], "b", "BJ●"NOR);
        the_point2[i] = replace_string(the_point2[i], "q", "QJ●"NOR);

        get_msg1 = "";
        if(x == 0)
            get_msg1 += sprintf("%s", "BJ●"NOR);
        get_msg1 += sprintf("%s%s", the_point1[i], (i_num[0]) ? ""NOR : "BJ●"NOR);
        if(x == 1 && y == 1)
            get_msg1 += sprintf("%s", "BJ●"NOR);

        get_msg2 = "";
        if(y == 0)
            get_msg2 += sprintf("%s", "BJ●"NOR);
        get_msg2 += sprintf("%s%s", the_point2[i], (i_num[1]) ? ""NOR : "BJ●"NOR);
        if(y == 1)
            get_msg2 += sprintf("%s", "BJ●"NOR);
        get_msg2 += "\n";

        get_msg1 = replace_string(get_msg1, "BJ", num["bjcolor1"]);
        get_msg1 = replace_string(get_msg1, "QJ", num["qjcolor1"]);
        get_msg2 = replace_string(get_msg2, "BJ", num["bjcolor2"]);
        get_msg2 = replace_string(get_msg2, "QJ", num["qjcolor2"]);
        msg += get_msg1 + get_msg2;
    }

    msg = make_mask(msg, "●", 18*18*2);
    return msg;
}

public string make_mask(string msg, string arg, int i)
{
    string str;

    reset_eval_cost();
    while(i--)
    {
        str = hanzi[random(sizeof(hanzi))];
        str = str[(random(sizeof(str)) & 0xFFFE)..<1];
        str = str[0..1];
        msg = replace_string(msg, arg, str, 1);
    }

    return msg;
}

//点阵任务
public mapping get_question()
{
    int the_num, i, j;
    string answer, question, str, str1;
    mapping num = ([]);
    mapping quest;
    quest = allocate_mapping(2);
    answer = "";

    reset_eval_cost();
    if(random(10) == 1)
    {
        j = random(sizeof(the_color));
        for(i = 0; i < 5; i++)
        {
            the_num = random(10);
            num["num" + (i+1)] = "" + the_num;
            num["bjcolor" + (i+1)] = sprintf("%s%s%s",
                              NOR,the_color[j]["bj"],the_color[j]["bf"]);
            num["qjcolor" + (i+1)] = sprintf("%s%s%s",
                              NOR,the_color[j]["bj"],the_color[j]["qj"]);
            answer += "" + the_num;
        }
        question = make_msg(num);
    }
    else
    {
        str = hanzi[random(sizeof(hanzi))];
        str = str[(random(sizeof(str)) & 0xFFFE)..<1];
        str = str[0..1];
        j = random(sizeof(the_color));
        num["num1"] = str;
        num["bjcolor1"] = sprintf("%s%s%s", NOR, the_color[j]["bj"], the_color[j]["bf"]);
        num["qjcolor1"] = sprintf("%s%s%s", NOR, the_color[j]["bj"], the_color[j]["qj"]);
        answer += str;
        str1 = hanzi[random(sizeof(hanzi))];
        str1 = str1[(random(sizeof(str1)) & 0xFFFE)..<1];
        str1 = str1[0..1];
        num["num2"] = str1;
        num["bjcolor2"] = sprintf("%s%s%s", NOR, the_color[j]["bj"], the_color[j]["bf"]);
        num["qjcolor2"] = sprintf("%s%s%s", NOR, the_color[j]["bj"], the_color[j]["qj"]);
        answer += str1;
        question = make_chn_msg(num);
    }
    quest["question"] = question;
    quest["answer"] = answer;
    return quest;
}

//点阵干扰
public string *trouble(string *str_point)
{
    int i/*, j*/, random_col, random_line, get_it;
    string the_line;
    int *int_line = ({0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15});
    int *int_col = ({2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17});

    for(i = 0; i < 16; i ++)
        str_point[i] = "bb" + str_point[i] + "bb";

    get_it = 0;
    for(;;)
    {
        the_line = "";
        if(int_line == ({}) || get_it)
            break;
        random_line = int_line[random(sizeof(int_line))];
        the_line = (string)str_point[random_line];
        if(strsrch(the_line,"bbbbb") < 0)
        {
            int_line -= ({ random_line });
            continue;
        }
        for(;;)
        {
            if(int_col == ({}))
                break;
            random_col = int_col[random(sizeof(int_col))];
            if(the_line[random_col-2..random_col+2] != "bbbbb")
            {
                int_col -= ({ random_col });
                continue;
            }
            get_it = 1;
            the_line = the_line[0..random_col-1] + "q" + the_line[random_col+1..19];
            str_point[random_line] = the_line;
            break;
        }
    }

    for(i = 0; i < 16; i ++)
        str_point[i] = str_point[i][2..17];

    return str_point;
}

public string *Get_Point(string src)
{
    string str = src;
    string point_buf, point_buff;
    string *the_point = ({});
    string SHZK1616;
    int *mark = ({
        0x80,
        0x40,
        0x20,
        0x10,
        0x08,
        0x04,
        0x02,
        0x01,
    });
    int len = strlen(str);
    int i, j;
    string line = "";

    if(len != 2)
        return 0;
    if(is_GB1(str[0]) && is_GB2(str[1]))
    {
        i = ((str[0]-0xa1)*94 + (str[1]-0xa1))*32;
        SHZK1616 = all_ziti[random(sizeof(all_ziti))];
        point_buf = read_bytes(SHZK1616, i, 32);
        for(i = 0; i < 32; i++)
        {
            for(j = 0; j < 8; j++)
                if((point_buf[i] & mark[j]) == 0)
                    line += "b";
                else
                    line += "q";
            if((i%2) != 0)
            {
                the_point += ({line});
                line = "";
            }
        }
    }
    else
        return 0;

    return the_point;
}