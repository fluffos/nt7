// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "小径");
        set("long", @LONG
这是一条由大青条石铺成的小路，虽不能说是一尘不染，但也整整洁
洁，看来经常有人打扫。东北面有一个小土丘，西面是一块草地，东面有
一座树林。
LONG );
        set("exits", ([
                "west"  : __DIR__"caodi",
                "east"  : __DIR__"shulin",
                "north" : __DIR__"tuqiu",
                "south" : __DIR__"haitan",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 9000);
        set("coor/y", -3000);
        set("coor/z", 0);
        setup();
}