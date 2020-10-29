// baoming.c

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(YEL "天王保命丹" NOR, ({"baoming dan", "dan"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", YEL "这是一颗淡黄的的药丸，是神龙岛的秘药，功效奇妙无比。\n" NOR);
                set("base_unit", "颗");
                set("base_value", 8000);
                set("base_weight", 80);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ "tianqi"   : 1,
                                    "xuejie"   : 1,
                                    "xuelian"  : 1,
                                    "lurong"   : 1,
                                    "xiefen"   : 1,
                                    "honghua"  : 1,
                                    "moyao"    : 1,
                                    "zzfen"    : 1,
                                    "heshouwu" : 1,
                                    "renshen"  : 1,
                                    "dangui"   : 1,
                                    "chenpi"   : 1 ]),
                        "neili" : 300,
                        "jing"  : 50,
                        "time"  : 5,
                        "min_level" : 140,
                        "shenlong-mixin" : 200,
                ]));
        }
        setup();
}

int do_effect(object me)
{
        mapping my;
        int time = 1800;

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

        if( time()-query_temp("last_eat/baoming", me) < time )
        {
                write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n");
                return 1;
        }

        set_temp("last_eat/baoming", time(), me);

        message_vision(HIG "$N" HIG "吃下一粒" + name() +
                       HIG "，眼睛直冒绿光！\n", me);
        tell_object(me, HIG "不一会儿你只觉得精神饱满，神气完足，内力充沛之极。\n" NOR);

        log_file("static/using", sprintf("%s(%s) eat 天王保命丹 at %s.\n",
                        me->name(1),query("id", me),ctime(time())));

        my = me->query_entire_dbase();
        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];
        if (my["jingli"] < my["max_jingli"])
                my["jingli"] = my["max_jingli"];
        if (my["neili"] < my["max_neili"])
                my["neili"] = my["max_neili"];

        me->start_busy(3);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}
