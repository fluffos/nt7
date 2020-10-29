// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "桃林");
        set("long", @LONG
这是一片灿若云霞的桃林，繁花似锦，五色缤纷，比起岛上其它地方
的桃林要茂盛许多，地下的泥土也十分新鲜，像有人刚刚整理过。
LONG );
        
        set("exits", ([
                "west" : __DIR__"mudi",
                "east" : __DIR__"jingshe",
        ]));
        
        set("objects", ([
                __DIR__"obj/taoshu" : 1,
        ]));
        
        set("outdoors", "taohua");

        set("coor/x", 8980);
        set("coor/y", -2950);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

/*
void init()
{
        object ob = this_player();
        if( query_temp("th_tomb_thief", ob)){
                tell_object(ob,CYN"你似乎觉得桃林中有点异样，但又说不上来。\n"NOR);
                delete("exits/east");
                set("exits/east", __DIR__"hyjuchu");
                    remove_call_out("close_door");
                    call_out("close_door",random(20),ob);

        }
}


void close_door()
{
        delete("exits/east");
        set("exits/east", __DIR__"jingshe");
}


int valid_leave(object me, string dir)
{
        if( query_temp("th_tomb_thief", me) && dir == "east"){
                me->move("/d/taohua/hyjuchu");
                 return 1;
        }

            return ::valid_leave(me, dir);
}
*/