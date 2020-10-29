// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name("铁箱", ({"tie xiang", "box"}));
        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long",
                              "这是只铁箱，好像能打开(open)\n");
                set("unit", "只");
                set("open_count", 1);
                set("weight", 1000);
        }
}

void init()
{
        add_action("do_open","open");
}

int do_open()
{
        object ob, me = this_player();
        
        if (query("open_count") > 0)
        {
                message_vision(
                        HIY "$N伸手打开铁箱，箱子里有一本书，上写《天魔诀》三字。\n" NOR, 
                        this_player());
                addn("open_count", -1);
                ob = new("/clone/book/tianmo-jue");
                ob -> move(me);
                return 1;
        }
        else 
                return notify_fail("铁盒已经被别人打开过了。\n");
}