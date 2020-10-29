// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

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
                "south" : __DIR__"maze36",
                "west"  : __DIR__"maze4",
                "north" : __DIR__"maze63",
        ]));

        set("item_desc", ([
                "shibei" : "
　　贲：亨。 小利有所往。
　　初九：贲其趾，舍车而徒。
　　六二：贲其须。
　　九三：贲如濡如，永贞吉。
　　六四：贲如皤如，白马翰如，匪寇婚媾。
　　六五：贲于丘园，束帛戋戋，吝，终吉。
　　上九：白贲，无咎。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 22, me);
        check_count(me, 22);
        return;
}