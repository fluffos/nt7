// yuling.c  玉灵散  by sinb

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(CYN "玉灵散" NOR, ({"yuling san", "san"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", "这是一包玉灵散，用来恢复你的精力。\n");
                set("base_unit", "包");
                set("base_value", 20000);
                set("base_weight", 50);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ "xiongdan"  : 1,
                                    "honghua"  : 1,
                                    "renshen"   : 1,
                                    "tugou"   : 1,
                                    "heshouwu"   : 1,
                                    "duhuo"   : 1,
                                    "fangfeng"    : 1,
                                    "xuelian"  : 1, ]),
                        "neili" : 70,
                        "jing"  : 25,
                        "time"  : 1,
                        "min_level" : 100,
                        "medical" : 150,
                ]));
        }
        setup();
}

int do_effect(object me)
{
        mapping my;

        if( time()-query_temp("last_eat/yuling", me)<10 )
        {
                write("你刚服用过药，需药性发挥完效用以后才能继续服用。\n");
                return 1;
        }

        my = me->query_entire_dbase();
        if (my["eff_jing"] == my["max_jing"])
        {
                write("你现在并没有受伤，不必服用" + name() + "。\n");
                return 1;
        }

        set_temp("last_eat/yuling", time(), me);

        message_vision(CYN "$N" CYN "张开嘴，猛地吞下了" + name() +
                       CYN "，脸上露出一丝微笑。\n" NOR, me);

        set("eff_jing", my["max_jing"], me);
        set("jing", my["max_jing"], me);

        me->start_busy(1);

        add_amount(-1); 
        if (query_amount() < 1) 
                destruct(this_object()); 

        return 1;
}