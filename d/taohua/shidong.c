// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "石洞");
        set("long", @LONG
树丛之后是一块光秃秃的石壁，四周无花无树，与其他地方形成强烈
反差。石壁上有一个岩洞，岩洞里黑黝黝的，看不清楚到底有什么，但似
乎有人影晃动。
LONG );

         set("exits", ([
                "south" : __DIR__"shucong",
        ]));


        set("outdoors", "taohua");

        set("coor/x", 8980);
        set("coor/y", -2990);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}