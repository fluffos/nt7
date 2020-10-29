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
                "east"  : __DIR__"maze52",
                "south" : __DIR__"maze2",
                "west"  : __DIR__"maze26",
                "north" : __DIR__"maze8",
        ]));

        set("item_desc", ([
                "shibei" : "
　　剥：不利有攸往。
　　初六：剥□以足，蔑贞凶。
　　六二：剥□以辨，蔑贞凶。
　　六三：剥之，无咎。
　　六四：剥□以肤，凶。
　　六五：贯鱼，以宫人宠，无不利。
　　上九：硕果不食，君子得舆，小人剥庐。
□  ＝ 爿 ＋ 木
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 23, me);
        check_count(me, 23);
        return;
}