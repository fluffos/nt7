// Copyright (C) 2003, by Slough1 group. All rights reserved.
// This software can not be used, copied, or modified in any
// form without the written permission from authors.

inherit ROOM;

#include "maze.h"

void create()
{
        set("short", "石阵");
        set("long", @LONG
这是一座由约莫两人多高的大石块构成的乱石阵，规模似乎不大，但
抬眼望去，四周尽是重重叠叠的嶙峋怪石，完全看不出有路通向石阵之外，
加之阵中常年雾气弥漫，更让人摸不清头绪。石块下有一块斜倒的石碑(s
hibei)，半埋在浮土中。
LONG );

        set("exits", ([
                "east"  : __DIR__"maze21",
                "south" : __DIR__"maze54",
                "west"  : __DIR__"maze56",
                "north" : __DIR__"maze58",
        ]));

        set("item_desc", ([
                "shibei" : "
　　睽：小事吉。
　　初九：悔亡，丧马勿逐，自复；见恶人无咎。
　　九二：遇主于巷，无咎。
　　六三：见舆曳，其牛掣，其人天且劓，无初有终。
　　九四：睽孤，遇元夫，交孚，厉无咎。
　　六五：悔亡，厥宗噬肤，往何咎。
　　上九：睽孤， 见豕负涂，载鬼一车， 先张之弧，后说之弧，匪寇婚
          媾，往遇雨则吉。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 38, me);
        check_count(me, 38);
        return;
}