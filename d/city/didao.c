// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;
#include <ansi.h>

void create()
{ 
       set("short","地道");
        set("long", @LONG
这里是在一条地道中。两旁的墙壁上挂着些油灯，有的已经熄灭
了。壁上和脚下的潮气让人很不舒服。东面的墙似乎可以(pull)。
LONG );
        set("exits", ([
                 "out" : "/d/city/xiaofang",
        ]));       

        set("no_clean_up", 0);
        set("open_count", 1);
        setup();

}

void init() 
{
        add_action("do_pull","pull"); 
}

int do_pull() 
{ 
        object ob, me = this_player(); 
        if (query("open_count") > 0) 
        { 
                message_vision(HIY  
                        "$N伸手在墙上拍了几下，不一会儿，东面的墙慢慢陷了下去，一只铁箱露了出来。\n" NOR, 
                        this_player()); 
                addn("open_count", -1); 
                ob = new("/d/city/obj/tiexiang"); 
                ob -> move(me); 
                return 1; 
        } 
        else 
                return notify_fail("这里已经被别人打开过了。\n"); 
} 