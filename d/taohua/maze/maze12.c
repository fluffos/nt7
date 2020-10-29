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
                "east"  : __DIR__"maze33",
                "south" : __DIR__"maze45",
                "west"  : __DIR__"maze1",
        ]));

        set("item_desc", ([
                "shibei" : "
　　否：否之匪人，不利君子贞，大往小来。
　　初六：拔茅茹，以其夤，贞吉亨。
　　六二：包承。 小人吉，大人否亨。
　　六三：包羞。
　　九四：有命无咎，畴离祉。
　　九五：休否，大人吉。 其亡其亡，系于苞桑。
　　上九：倾否，先否后喜。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 12, me);
        check_count(me, 12);
        return;
}