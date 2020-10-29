//数字|汉字 ASCⅡ点阵图   生成程序
//Smallfish@HUAXIA

#include <ansi.h>
#include "numbers.h"

string make_msg(mapping num);
mapping get_question();
string *trouble(string *str_point);

void create()
{
        seteuid(getuid());
}

//数字点阵图生成函数
string make_msg(mapping num)
{
        int q, q_size, i1 = random(2), i2 = random(2), i3 = random(2), i4 = random(2), i5 = random(2);
        int *i_num = ({i1, i2, i3, i4, i5});
        int beg;
        string msg = "\n";
        string get_msg,str;
        for (int i =0; i < 7; i++) {
                for (int j = 1; j <= 5; j++ )
                {
                        get_msg = sprintf("%s%s", 
                                          numbers[atoi(num["num"+j])][i],
                                          (i_num[j-1])?"BJ●"NOR:"BJ●●"NOR);
                        get_msg = replace_string(get_msg,"BJ",num["bjcolor"+j]);
                        get_msg = replace_string(get_msg,"QJ",num["qjcolor"+j]);
                        msg += get_msg;
                }
                msg += "\n";
        }
        msg += "\n";
        q_size = strlen(msg);
        while ((beg=strsrch(msg,"●"))>=0) 
        {
                str = chn_num[random(sizeof(chn_num))];
                str = str[(random(sizeof(str)) & 0xFFFE)..<1];
                str = str[0..1];
                msg = msg[0..beg-1] + str + msg[beg+2..q_size-1];
        }
        return msg;
}

//汉字点阵图生成函数
string make_chn_msg(mapping num)
{
        int q, q_size, i1 = random(2), i2 = random(2), i3 = random(2), i4 = random(2);
        int *i_num = ({i1, i2, i3, i4});
        string msg = "\n";
        string get_msg1,get_msg2;
        string *the_point1=({}),*the_point2=({});

        the_point1 = LANGUAGE_D->Get_Point(num["num1"],num["index1"]);
        if (!the_point1)
                log_file("static/chn_num",
                        sprintf("这个汉字没有取到点阵：%s，请仔细查看\n",num["num1"]));
        the_point2 = LANGUAGE_D->Get_Point(num["num2"],num["index2"]);
        if (!the_point2)
                log_file("static/chn_num",
                        sprintf("这个汉字没有取到点阵：%s，请仔细查看\n",num["num2"]));

        the_point1 = trouble(the_point1);
        the_point2 = trouble(the_point2);

        for (int i = 0 ; i < 16 ; i++) {
                the_point1[i] = replace_string(the_point1[i],"b","BJ●"NOR);
                the_point1[i] = replace_string(the_point1[i],"q","QJ●"NOR);
                the_point2[i] = replace_string(the_point2[i],"b","BJ●"NOR);
                the_point2[i] = replace_string(the_point2[i],"q","QJ●"NOR);

                get_msg1 = sprintf("%s%s%s", 
                                  (i_num[0])?""NOR:(random(16)==0)?"QJ●"NOR:"BJ●"NOR,
                                  the_point1[i],
                                  (i_num[1])?""NOR:(random(16)==0)?"QJ●"NOR:"BJ●"NOR);
                get_msg2 = sprintf("%s%s%s\n", 
                                  (i_num[2])?""NOR:(random(16)==0)?"QJ●"NOR:"BJ●"NOR,
                                  the_point2[i],
                                  (i_num[3])?""NOR:(random(16)==0)?"QJ●"NOR:"BJ●"NOR);
                get_msg1 = replace_string(get_msg1,"BJ",num["bjcolor1"]);
                get_msg1 = replace_string(get_msg1,"QJ",num["qjcolor1"]);
                get_msg2 = replace_string(get_msg2,"BJ",num["bjcolor2"]);
                get_msg2 = replace_string(get_msg2,"QJ",num["qjcolor2"]);
                msg += get_msg1+get_msg2;
        }
        msg += "\n";
        return msg;
}

//获取宗师whisper任务
mapping get_question()
{
        int the_num, i, j, chinese_num;
        string answer,question,str,*str1, the_zhiku;
        mapping num = ([]);
        mapping quest;
        quest = allocate_mapping(2);
        answer = "";
        reset_eval_cost(); 
        if (random(3)==1)
        {
                for (i = 0;i < 5;i ++)
                {
                        the_num = random(10);
                        j = random(sizeof(the_color));
                        num["num" + (i+1)] = "" + the_num;
                        num["bjcolor" + (i+1)] = sprintf("%s%s%s",
                                                          NOR,the_color[j]["bj"],the_color[j]["bf"]);
                        num["qjcolor" + (i+1)] = sprintf("%s%s%s",
                                                          NOR,the_color[j]["bj"],the_color[j]["qj"]);
                        answer += "" + the_num;
                }
                question = make_msg(num);
        } else
        {
                //两个汉字采用相同的前景和背景可能干扰效果更好一些:)
                //smallfish@huaxia
                j = random(sizeof(the_color));
                for (i = 0;i < 2;i ++)
                {
                        chinese_num = random(100);
                        the_zhiku = zhiku[random(sizeof(zhiku))];
                        str = LANGUAGE_D->Get_Point_Index(chinese_num,the_zhiku);
                        //j = random(sizeof(the_color));
                        num["num" + (i+1)] = chinese_num;
                        num["index" + (i+1)] = the_zhiku;
                        num["bjcolor" + (i+1)] = sprintf("%s%s%s",
                                                          NOR,the_color[j]["bj"],the_color[j]["bf"]);
                        num["qjcolor" + (i+1)] = sprintf("%s%s%s",
                                                          NOR,the_color[j]["bj"],the_color[j]["qj"]);
                        answer += str;
                }
//              return num;
                question = make_chn_msg(num);
        }
        quest["question"] = question;
        quest["answer"] = answer;
        return quest;
}

//汉字点阵图干扰象素添加函数
string *trouble(string *str_point)
{
        int i,j,random_col,random_line,get_it;
        string the_line;
        int *int_line = ({0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15});
        int *int_col = ({2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17});

        for (i = 0; i < 16; i ++)
                str_point[i] = "bb" + str_point[i] + "bb";

        get_it = 0;
        for (;;)
        {
                the_line = "";
                if (int_line == ({}) || get_it) break;
                random_line = int_line[random(sizeof(int_line))];
                the_line = (string)str_point[random_line];
                if (strsrch(the_line,"bbbbb") < 0)
                {
                        int_line -= ({ random_line });
                        continue;
                }
                for (;;)
                {
                        if (int_col == ({}) ) break;
                        random_col = int_col[random(sizeof(int_col))];
                        if (the_line[random_col-2..random_col+2] != "bbbbb") {
                                int_col -= ({ random_col });
                                continue;
                        }
                        get_it = 1;
                        the_line = the_line[0..random_col-1] + "q" + the_line[random_col+1..19];
                        str_point[random_line] = the_line;
                        break;
                }
        }

        for (i = 0; i < 16; i ++)
                str_point[i] = str_point[i][2..17];

        return str_point;
}

//下面这个函数没有实际作用，只是用于CALL检查汉字表是否有错误
void check_chn()
{
        int i,j;
        string line;

        for (i=0;i<sizeof(chn_num);i++)
        {
                line = chn_num[i];
                for (j=0;j<sizeof(line);)
                {
                        if (!LANGUAGE_D->Get_Point(line[j..j+1]))
                                log_file("static/chn_num",
                                          sprintf("这个汉字没有取到点阵：%s，请仔细查看\n",line[j..j+1]));
                        j+=2;
                }
        }
}
