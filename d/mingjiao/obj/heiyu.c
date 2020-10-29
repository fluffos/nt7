// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// heiyu.c

#include <ansi.h>
inherit ITEM;

void init()
{
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIW "黑玉断续膏" NOR, ({"heiyu duanxugao", "gao", "heiyu"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("unit", "盒");
                set("heiyu", 3);
                set("long", "一盒疗伤圣药黑玉断续膏，名虽黑玉，实则雪白。\n");
                set("value", 100000);
        }
        setup();
}

int do_eat(string arg)
{
        object me, ob;
      
        me = this_player();
        ob = this_object();

        if (! id(arg))
                return notify_fail("你要服什么？\n");
                
        if (this_player()->is_busy() || this_player()->is_fighting())
                return notify_fail("你正忙着呢。\n");
                
        if( query("eff_qi", this_player()) == 
            this_player(query("max_qi", )) )
                return notify_fail("你现在不需要用黑玉断续膏。\n");

        if( query("heiyu", ob)>0 )
        {      
                me->receive_curing("qi",query("max_qi", me));
                me->receive_curing("jing",query("max_jing", me)/2);
                addn("neili",query("max_neili",  me)/10, me);
                set("food", me->max_food_capacity(), me);
                set("water", me->max_water_capacity(), me);
                message_vision(HIW"$N把黑玉断续膏涂在伤口上，只觉伤势大为好转。\n"NOR, me);
                addn("heiyu", -1, ob);
                this_player()->start_busy(3);      
                return 1;
        }
        
        if( query("heiyu", ob)<1 )
        {
                write("盒中的黑玉断续膏已经所剩无几了。\n");
                set("long", "一个用来盛疗伤圣药黑玉断续膏的木盒。\n", ob);
                set("value", 5000, ob);
                return 1;
        }
}