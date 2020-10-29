// /adm/daemons/x_named.c 随机物品名称生成守护程序
// By Alf@Syzf, Last Update 2005.0208

#include <ansi.h>
#include "include/x_name.h"

#define RATE        10      //机率判断基准
#define RATE_A      30      //中缀出现机率
#define RATE_B      50      //前缀出现机率[色彩出现机率]
#define RATE_C      100     //单色出现机率（中、前缀齐全）
#define RATE_X      1000    //多色出现机率（中、前缀齐全）

varargs int x_name(object obj, string arg)
{
    int i, j;
    string x_id, x_id_a, x_id_b, *key;
    string x_name, x_name_a, x_name_b, x_color;
    mapping name;

    key = keys(weapon_file);
    if(!arg || arg == "" || member_array(arg, key) == -1)
        arg = key[random(sizeof(key))];

    i = random(RATE_A);
    if(i <= RATE)
    {
        key = keys(name_a);
        x_name_a = key[random(sizeof(key))];
        x_id_a   = name_a[x_name_a] + " ";

        i = random(RATE_B);
        if(i <= RATE)
        {
            key = keys(name_b);
            x_name_b = key[random(sizeof(key))];
            x_id_b   = name_b[x_name_b] + " ";
        }
        else
        {
            x_name_b = "";
            x_id_b   = "";
        }
    }
    else
    {
        x_name_a = "";
        x_id_a   = "";
    }

    if(x_name_a != "")
    {
        i = random(RATE_X);
        if(i <= RATE)
        {
            x_color  = all_color[random(sizeof(all_color))];
            x_name_a = x_color + x_name_a;
            if(x_name_b != "")
            {
                x_color  = all_color[random(sizeof(all_color))];
                x_name_b = x_color + x_name_b + "$NOR$";
                x_name   = x_name_b + x_name_a + obj->name(1)[2..] + "$NOR$";
                x_id     = x_id_b + x_id_a + obj->parse_command_id_list()[1];
            }
            else
            {
                x_name = x_name_a + obj->name(1)[2..] + "$NOR$";
                x_id   = x_id_a + obj->parse_command_id_list()[1];
            }
        }
        else
        {
            i = random(RATE_B);
            if(i <= RATE)
            {
                if(x_name_b != "")
                {
                    x_name = x_name_b + x_name_a + obj->name(1)[2..];
                    x_id   = x_id_b + x_id_a + obj->parse_command_id_list()[1];
                    i = random(RATE_C);
                    if(i <= RATE)
                    {
                        x_color = all_color[random(sizeof(all_color))];
                        x_name  = x_color + x_name + "$NOR$";
                    }
                }
                else
                {
                    x_name = x_name_a + obj->name(1)[2..];
                    x_id   = x_id_a + obj->parse_command_id_list()[1];
                    x_color = all_color[random(sizeof(all_color))];
                    x_name  = x_color + x_name + "$NOR$";
                }
            }
            else
            {
                if(x_name_b != "")
                {
                    x_name = x_name_b + x_name_a + obj->name(1)[2..];
                    x_id   = x_id_b + x_id_a + obj->parse_command_id_list()[1];
                }
                else
                {
                    x_name = x_name_a + obj->name(1)[2..];
                    x_id   = x_id_a + obj->parse_command_id_list()[1];
                }
            }
        }

        name = ([
                    "name" : trans_color(x_name, 2),
                    "id"   : ({ x_id, obj->parse_command_id_list()[1], }),
               ]);

        obj->set_name(name["name"], name["id"]);
        obj->set("long", "这是一" + obj->query("unit") + obj->short() + "。\n");
    }
    return 1;
}

