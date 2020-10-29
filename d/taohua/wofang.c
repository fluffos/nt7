// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <room.h>
inherit ROOM;
void create()
{
        set("short", "卧房");
        set("long", @LONG
你走进了一间卧房。一股若有若无的甜香扑鼻而来。琴剑书画，挂在
墙上。锦笼纱罩，金彩珠光。小几上汝窑美人瓶内的桃花正自盛开。右首
一张床，床头放着五彩鸾纹被。
LONG );
        set("exits", ([
                "north" :__DIR__"hyjuchu",
        ]));
        set("objects", ([
                __DIR__"npc/binu" : 2,
        ]) );
        
        set("coor/x", 8970);
        set("coor/y", -2960);
        set("coor/z", 0);
        setup();
}
