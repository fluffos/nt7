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
这桃林似乎无穷无尽一般，其中小径更是纵横交错，匪夷所思。你拼
命想离开原地，但几个转折又回到了原地。一连几次，似乎只是在同一个
地方兜圈子。
LONG );

        set("exits", ([
                "east"      : __DIR__"thzhen5",
                "south"     : __DIR__"thzhen5",
                "west"      : __DIR__"thzhen5",
                "north"     : __DIR__"thzhen5",
                "northeast" : __DIR__"thzhen5",
                "southeast" : __DIR__"thzhen5",
                "southwest" : __DIR__"thzhen5",
                "northwest" : __DIR__"thzhen5",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 9000);
        set("coor/y", -2900);
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
                me->move("/d/taohua/thzhen6");
                me->start_busy(random(3));
                return 1;
        }
        return ::valid_leave(me, dir);
}

