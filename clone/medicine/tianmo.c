// This program is a part of NITAN MudLIB
// tianmo.c 天魔圣血膏

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(HIC "天魔圣血膏" NOR, ({"tianmo shengxuegao", "tianmo", "shengxuegao"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一包天魔圣血膏，天魔圣血膏是天下无双的救伤灵药。\n");
                set("base_unit", "包");
                set("base_value", 26000);
                set("base_weight", 80);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ 
                                    "dangui"   : 1,
                                    "lurong"   : 6,
                                    "honghua"  : 3,
                                    "taoxian"  : 1,
                                    "zzfen"    : 1,
                                    "heshouwu" : 6,
                                    "renshen"  : 9,
                                    "shengdi"  : 1 ]),
                        "neili" : 300,
                        "jing"  : 50,
                        "time"  : 5,
                        "min_level" : 120,
                        "medical" : 200,
                        "liandan-shu" : 1900,
                ]));
        }
        setup();
}

int do_effect(object me)
{
        mapping my; 
        int time = 900;

        my = me->query_entire_dbase(); 

        // vip的效果
        switch( me->query_viplevel() )
        {
        case 1:
                time = time - time / 10;
                break;
        case 2:
                time = time - time * 2 / 10;
                break;
        case 3:
                time = time - time * 3 / 10;
                break;
        case 4:
                time = time - time * 4 / 10;
                break;
        case 5:
                time = time - time * 5 / 10;
                break;
        case 6:
                time = time - time * 6 / 10;
                break;  
        case 7:
                time = time - time * 7 / 10;
                break;                  
        }
        if( time < 10 ) time = 10;

        if( time()-query_temp("last_eat/tianmo", me) < time )
        {
                write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n");
                return 1;
        }

        set_temp("last_eat/tianmo", time(), me);

        message_vision(YEL "$N" YEL "吃下一包" + name() +
                       YEL "，内息运行一小周天，感觉身体发生了一些变化。\n", me);

        my["jing"]     = my["max_jing"];
        my["qi"]       = my["max_qi"];
        my["eff_jing"] = my["max_jing"];
        my["eff_qi"]   = my["max_qi"];
        my["neili"]    = my["max_neili"];
        my["jingli"]   = my["max_jingli"];
        me->start_busy(3);

        add_amount(-1); 
        if (query_amount() < 1) 
                destruct(this_object()); 

        return 1;
}
