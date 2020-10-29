// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit ROOM;
#include <localtime.h>

string* dirs = ({
        "east", "southeast", "southeast", "southwest", "northeast", "northeast",
        "west", "south", "south", "northwest", "north", "north",
});

void create()
{

        set("short", "桃花林");
        set("long", @LONG
你走了几步，忽然想到如果岛中有人，不如在原地静坐待变，如此乱
闯终究不是个了局。说也奇怪，开始你无论如何也离不开原地，现在想觅
路回去，却发现自己离原地好象越来越远了。
LONG );

        set("exits", ([
                "east" : __DIR__"thzhen6",
                "south" : __DIR__"thzhen6",
                "west" : __DIR__"thzhen6",
                "north" : __DIR__"thzhen6",
                "northeast" : __DIR__"thzhen6",
                "southeast" : __DIR__"thzhen6",
                "southwest" : __DIR__"thzhen6",
                "northwest" : __DIR__"thzhen6",
        ])); 
        
        set("outdoors", "taohua");

        set("coor/x", 9000);
        set("coor/y", -2950);
        set("coor/z", 0);
        setup();
     
}

void init()
{
        set_temp("die_reason", "误入桃花迷阵被桃花瓣射死", this_player());
        this_player()->receive_damage("qi", 15);
        this_player()->receive_wound("qi",  15);
        message_vision(HIR "突然一阵桃花瓣象雨点般疾射$N！\n" NOR, this_player());
}

int valid_leave(object me, string dir)
{
        mixed local;
        int count;
        mapping myfam;

        myfam=query("family", me);

        local = localtime(time() * 60);

        count = ((local[LT_HOUR] + 1) % 24) / 2;

        if (dirs[count] == dir) 
        {
                me->move("/d/taohua/shucong");
                me->start_busy(random(3));
                return 1;
        }
        return ::valid_leave(me, dir);
}