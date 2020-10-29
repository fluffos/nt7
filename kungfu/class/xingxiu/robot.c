#include <ansi.h>
#include "numbers.h"

string make_msg(mapping num, string question);
void make_question(object user, object asker);
void get_question(object obj, object asker);
void no_answer(object user, object asker);
int do_anwser(string arg, object obj, object asker);

mapping colors = ([
        "红" : RED,
        "白" : WHT,
        "绿" : GRN,
        "蓝" : BLU,
        "靛" : CYN,
        "紫" : MAG,
        "黄" : YEL,
        ]);

void create()
{
        seteuid(getuid());
}

string make_msg(mapping num, string question)
{
        int q, q_size, i1 = random(2), i2 = random(2), i3 = random(2), i4 = random(2), i5 = random(2);
        int *i_num = ({i1, i2, i3, i4, i5});
        string msg = "看图回答问题：\n";
        while (sizeof(question)<14) {
                q_size = sizeof(question);
                q = random(8);
                question = question[0..q*2+1]+"　"+question[(q+1)*2..q_size];
                msg = msg[0..q*2+1]+"　"+msg[(q+1)*2..(sizeof(msg)-1)];
                if(random(3)==2) msg = "　" + msg;
                if(random(3)==0) msg = "　　" + msg;
        }
                msg = msg + "\n　　";
        for (int i =0; i < 8; i++) {
                for (int j = 1; j <= 5; j++ )
                {
                        msg += sprintf("%s%s%s", num["color"+j], numbers[atoi(num["num"+j])][i], (i_num[j-1])?"　":"");
                }
                msg += NOR + question[i*2..(i*2+1)] + "\n　　";
        }
        return msg;
}

void get_question(object user, object asker)
{
        make_question(user, asker);
}

void make_question(object user, object asker)
{
        int answer, i, j, k, q, p, z, color_num = sizeof(colors);
        string question, *color_name, *color, c_name, colorx;
        mapping num = ([]);
        if( stringp(query("robot_answer", user))){
                tell_object(user, "你还是回答刚才的问题再说吧。\n");
                return;
        }
        switch (random(6))
        {
        case 5: i = random(10), j = random(10), k = random(10), p = random(5), q = random(5), z = random(2);
                question = "出现最多的";
                while(j == i) j = random(10);
                while(k == i || k == j) k = random(10);
                while(q == p) q = random(5);
                num["num" + (p + 1)] = sprintf("%d", (z == 0 ? j : k));
                num["num" + (q + 1)] = sprintf("%d", (z == 1 ? j : k));
                for (int o = 1 ;o <= 5 ;o++ )
                {
                        if(o != (p+1) && o != (q+1)) num["num" + o] = "" + i;
                        num["color" + o] = NOR;
                }
                question = make_msg(num, question);
                answer = i;
                //set("num", num, this_object());
                set("num", num, user);
                break;
        case 1: i = random(10), j = random(10), p = random(5), q = random(5);
                question = "出现最多的";
               while(j == i) j = random(10);
                while(q == p) q = random(5);
                num["num" + (p + 1)] = "" + j;
                num["num" + (q + 1)] = "" + j;
                for (int o = 1 ;o <= 5 ;o++ )
                {
                        if(o != (p+1) && o != (q+1)) num["num" + o] = "" + i;
                        num["color" + o] = NOR;
                }
                question = make_msg(num, question);
                set("num", num, this_object());
                answer = i;
                break;
        case 2: i = random(10), j = random(10), p = random(5);
                question = "出现最多的";
                while(j == i) j = random(10);
                num["num" + (p + 1)] = "" + j;
                for (int o = 1 ;o <= 5 ;o++ )
                {
                        if(o != (p+1)) num["num" + o] = "" + i;
                        num["color" + o] = NOR;
                }
                question = make_msg(num, question);
                answer = i;
                break;
        case 0: i = random(10), j = random(10), p = random(5);
                question = "出现最少的";
                while(j == i) j = random(10);
                num["num" + (p + 1)] = "" + j;
                for (int o = 1 ;o <= 5 ;o++ )
                {
                        if(o != (p+1)) num["num" + o] = "" + i;
                        num["color" + o] = NOR;
                }
                question = make_msg(num, question);
                answer = j;
                break;
        case 4: i = random(10), j = random(10), p = random(5);
                question = "出现最少的";
                while(j == i) j = random(10);
                num["num" + (p + 1)] = "" + j;
                for (int o = 1 ;o <= 5 ;o++ )
                {
                        if(o != (p+1)) num["num" + o] = "" + i;
                        num["color" + o] = NOR;
                }
                question = make_msg(num, question);
                answer = j;
                break;
        case 3: i = random(10), p = random(5);
                color_name = keys(colors);
                color = values(colors);
                c_name = color_name[random(color_num)];
                num["num" + (p + 1)] = "" + i;
                num["color" + (p + 1)] = colors[c_name];
                question = c_name + "色的";
                for (int o = 1 ;o <=5 ;o++ )
                {
                        colorx = color[random(color_num)];
                        while(colorx == colors[c_name]) colorx = color[random(color_num)];
                        if(o != (p+1)) {
                                num["num" + o] = "" + random(10);
                                num["color" + o] = colorx;
                        }
                }
                question = make_msg(num, question);
                answer = i;
                break;
        }
        set("robot_answer", ""+answer, user);
        tell_object(user, question + "\n" + "你有三分钟回答这个问题，回答问题使用指令answer\n　　格式：answer [数字]\n");
        remove_call_out("no_answer");
        call_out("no_answer", 180, user, asker);
        return;
}

int do_answer(string arg, object user, object asker)
{
        int number;
        if( !stringp(query("robot_answer", user)))return 0;
        if(!arg || sscanf(arg, "%d", number) != 1) {
                tell_object(user, "格式：answer [数字]\n");
                return 1;
        }
        if( arg != query("robot_answer", user)){
                addn("be_robot", 1, user);
                tell_object(user,"回答错误！你已经错了"+chinese_number(query("be_robot", user))+"次了。\n");
                if( query("be_robot", user) >= 3){
                        tell_object(user, "你现在被怀疑可能为机器人。\n");
                delete("be_robot", user);
                delete("robot_answer", user);
                        return -1;
                }
                tell_object(user, "现在重新出题。\n");
                delete("robot_answer", user);
                make_question(user, asker);
                return 1;
        }
        tell_object(user, "回答正确。\n");
        user->move(query("left_place", user));
        remove_call_out("no_answer");
        delete("left_place", user);
        delete("robot_answer", user);
        delete("be_robot", user);
        return 2;
}

void no_answer(object user, object asker)
{
        asker->no_answer(user);
}

