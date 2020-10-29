// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "草地");
        set("long", @LONG
这是一块极普通的草地，地上只有一些寻常随处可见的小石子和小树
枝。东面有一条小径，西面是茂密的树林，北面则是一座松柏林，松柏林
中一条小路蜿蜒向北，不知所终。
LONG );
         set("exits", ([
                "west"  : __DIR__"shucong",
                "east"  : __DIR__"xiaojing",
                "north" : __DIR__"songlin",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 8990);
        set("coor/y", -3000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}