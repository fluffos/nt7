// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include <room.h>

inherit BUILD_ROOM;
string look_shu();

void create()
{
        set("short", HIY "名人堂" NOR);
        set("long", @LONG
这里就是泥潭的名人堂。在这里供奉的有大侠，也有魔头，也有
不是大侠不是魔头的玩家。无论是哪一位，都曾冠绝一时，都有一个
长长而惊心动魄的故事，每一个故事都曾很深远地影响了一代甚至两
三代玩家。虽然他们都曾经轰轰烈烈掀起满江湖的风雨，如今，他们
再也不会在江湖出现了。他们都已经退出江湖，但他们的侠影魔踪很
长时间以后仍是一个传说。
LONG );

        set("no_fight", "1");
        set("no_steal", "1");
        set("no_beg", "1");
        set("no_sleep_room", "1");
        set("no_clean_up", 0);
        set("max_room", 5);

        set("exits", ([
                "down" : __DIR__"wumiao2",
        ]));
        set("objects", ([
                __DIR__"npc/mingren/gzf" : 1,
                __DIR__"npc/mingren/icewind" : 1,
                __DIR__"npc/mingren/jicker" : 1,
                __DIR__"npc/mingren/feel" : 1,
                __DIR__"npc/mingren/coke" : 1,
                      __DIR__"npc/mingren/kuzhi" : 1, 
        ]));
	set("coor/x", -10);
	set("coor/y", 20);
	set("coor/z", 20);
	setup();
}
