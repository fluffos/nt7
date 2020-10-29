// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "小土丘");
        set("long", @LONG
走到这里，地势才略见起伏。土丘之上虽然没有什么高大树木，但碧
草茵茵，间杂着一些奇花异草，散发出阵阵沁人心肺的异香，令人精神为
之一振。居高临下朝北边望去似乎有一片小小竹林。
LONG );
         set("exits", ([
                "south" : __DIR__"xiaojing",
                "north" : __DIR__"zhulin",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 8990);
        set("coor/y", -2990);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}