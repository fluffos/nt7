// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "港湾");
        set("long", @LONG
这是一个不大的港湾，里面已大大小小的停泊着六七艘船。另有一艘
大船船尾高耸，形象华美，船身漆得金碧辉煌，象是新打造好的，但却远
远停在一旁，不知作什么用。这里有几个哑巴水手忙来忙去，都不愿理你。
LONG );

        set("outdoors", "taohua");

        set("exits", ([
                "east" : __DIR__"shucong",
                "north" : __DIR__"enter_m",
        ]));

        set("item_desc", ([
                "chuan" : "这是一艘海船，可载人渡海，但是船家在平时也用它来打鱼。\n",
        ]));

        set("coor/x", 8970);
        set("coor/y", -3000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}