// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "民房");
        set("long", @LONG
这是一个非常简陋的房子，一床一几，床上挂了纱帐，墙上挂着
一副似是名家的画(picture)，此外别无他物。
LONG );
        set("exits", ([
                "north" : "/d/city/ximen",
        ]));

        set("objects", ([
                __DIR__"npc/guisan" : 1,
        ]));
        set("item_desc", ([
                "picture" : "下雨天的名画。\n",
        ]));

        set("no_clean_up", 0);

	set("coor/x", -40);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "enter") 
        {
                say (me->name() + "走进暗洞。鬼三又把暗门关起来。\n");
                set_temp("new_valid_dest", "/d/city/didao", me);
                me->move("/d/city/didao");
                delete("exits/enter");
                set_temp("search", 0, me);
        }
        return ::valid_leave(me, dir);
}