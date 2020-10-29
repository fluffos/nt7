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
                "east"  : __DIR__"maze44",
                "south" : __DIR__"maze17",
                "west"  : __DIR__"maze10",
        ]));

        set("item_desc", ([
                "shibei" : "
  　无妄：元，亨，利，贞。 其匪正有眚，不利有攸往。
　　初九：无妄，往吉。
　　六二：不耕获，不□畲，则利有攸往。
　　六三：无妄之灾，或系之牛，行人之得，邑人之灾。
　　九四：可贞，无咎。
　　九五：无妄之疾，勿药有喜。
　　上九：无妄，行有眚，无攸利。
□  ＝  上 艹 下甾

\n",
        ]));
        
        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 25, me);
        check_count(me, 25);
        return;
}