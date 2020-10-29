// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include <room.h>

inherit ROOM;
// inherit HARBOR;

void create()
{
        set("short", "舟山");
        set("long", @LONG
这是舟山的一个渔港，边上有艘大船(chuan)，船上坐着几个渔夫打
扮的人，乘船可渡过大海到达传说中的桃花岛。西面是嘉兴城，东面是一
望无际的大海。
LONG );
        set("outdoors", "taohua");
        set("exits", ([
                "west" : "/d/jiaxing/nanhu1",
        ]));

        set("item_desc", ([
                "chuan" : "这是一艘海船，可载人渡海，但是船家在平时也用它来打鱼。\n",
        ]));

        set("navigate/locx", 0);
        set("navigate/locy", -200);

        set("cost", 2);

        setup();
}
