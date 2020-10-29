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
你一走进桃林，看见东一簇桃花，西一丛桃树，顿时目眩神迷，迷失
了方向。你慌乱中刚想退出，回头一瞧，来路已在花丛中消失得无影无踪，
看来只有硬着头皮往前走了。
LONG );

        set("exits", ([
                "east"      : __DIR__"thzhen4",
                "south"     : __DIR__"thzhen4",
                "west"      : __DIR__"thzhen4",
                "north"     : __DIR__"thzhen4",
                "northeast" : __DIR__"thzhen6",
                "southeast" : __DIR__"thzhen6",
                "southwest" : __DIR__"thzhen6",
                "northwest" : __DIR__"thzhen6",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 9000);
        set("coor/y", -2800);
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
          int   count;
          mapping myfam;

        myfam=query("family", me);

          local = localtime(time()*60);
          count = ((local[LT_HOUR] + 1) % 24) / 2;

        if (dirs[count] == dir) 
        {
                me->move("/d/taohua/thzhen5");
                  me->start_busy(random(3));
                return 1;
        }
        return ::valid_leave(me, dir);
}

